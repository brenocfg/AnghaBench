#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct sldns_buffer {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  data; } ;
struct auth_xfer {int have_zone; int /*<<< orphan*/  serial; } ;
struct auth_chunk {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  auth_data_cmp ; 
 int /*<<< orphan*/  auth_data_del ; 
 int /*<<< orphan*/  az_insert_rr_decompress (struct auth_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sldns_buffer*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunk_rrlist_end (struct auth_chunk*,int) ; 
 int /*<<< orphan*/  chunk_rrlist_get_current (struct auth_chunk*,int,size_t,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  chunk_rrlist_gonext (struct auth_chunk**,int*,size_t*,size_t) ; 
 int /*<<< orphan*/  chunk_rrlist_start (struct auth_xfer*,struct auth_chunk**,int*,size_t*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_rrlist_position (char*,struct auth_chunk*,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_read_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int verbosity ; 

__attribute__((used)) static int
apply_axfr(struct auth_xfer* xfr, struct auth_zone* z,
	struct sldns_buffer* scratch_buffer)
{
	struct auth_chunk* rr_chunk;
	int rr_num;
	size_t rr_pos;
	uint8_t* rr_dname, *rr_rdata;
	uint16_t rr_type, rr_class, rr_rdlen;
	uint32_t rr_ttl;
	uint32_t serial = 0;
	size_t rr_nextpos;
	size_t rr_counter = 0;
	int have_end_soa = 0;

	/* clear the data tree */
	traverse_postorder(&z->data, auth_data_del, NULL);
	rbtree_init(&z->data, &auth_data_cmp);
	xfr->have_zone = 0;
	xfr->serial = 0;

	/* insert all RRs in to the zone */
	/* insert the SOA only once, skip the last one */
	/* start RR iterator over chunklist of packets */
	chunk_rrlist_start(xfr, &rr_chunk, &rr_num, &rr_pos);
	while(!chunk_rrlist_end(rr_chunk, rr_num)) {
		if(!chunk_rrlist_get_current(rr_chunk, rr_num, rr_pos,
			&rr_dname, &rr_type, &rr_class, &rr_ttl, &rr_rdlen,
			&rr_rdata, &rr_nextpos)) {
			/* failed to parse RR */
			return 0;
		}
		if(verbosity>=7) log_rrlist_position("apply_axfr",
			rr_chunk, rr_dname, rr_type, rr_counter);
		if(rr_type == LDNS_RR_TYPE_SOA) {
			if(rr_counter != 0) {
				/* end of the axfr */
				have_end_soa = 1;
				break;
			}
			if(rr_rdlen < 22) return 0; /* bad SOA rdlen */
			serial = sldns_read_uint32(rr_rdata+rr_rdlen-20);
		}

		/* add this RR */
		if(!az_insert_rr_decompress(z, rr_chunk->data, rr_chunk->len,
			scratch_buffer, rr_dname, rr_type, rr_class, rr_ttl,
			rr_rdata, rr_rdlen, NULL)) {
			/* failed, malloc error or so */
			return 0;
		}

		rr_counter++;
		chunk_rrlist_gonext(&rr_chunk, &rr_num, &rr_pos, rr_nextpos);
	}
	if(!have_end_soa) {
		log_err("no end SOA record for AXFR");
		return 0;
	}

	xfr->serial = serial;
	xfr->have_zone = 1;
	return 1;
}