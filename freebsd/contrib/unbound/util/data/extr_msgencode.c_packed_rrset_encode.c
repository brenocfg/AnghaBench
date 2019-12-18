#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  scalar_t__ time_t ;
struct TYPE_4__ {size_t type; int flags; size_t rrset_class; int /*<<< orphan*/  dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {size_t count; scalar_t__* rr_ttl; size_t** rr_data; int* rr_len; size_t rrsig_count; } ;
struct compress_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_rr_descriptor ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int PACKED_RRSET_FIXEDTTL ; 
 int RETVAL_OK ; 
 int RETVAL_TRUNC ; 
 int compress_any_dname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct regional*,struct compress_tree_node**) ; 
 int compress_owner (struct ub_packed_rrset_key*,int /*<<< orphan*/ *,struct regional*,struct compress_tree_node**,size_t,size_t*,int) ; 
 int compress_rdata (int /*<<< orphan*/ *,size_t*,int,struct regional*,struct compress_tree_node**,int /*<<< orphan*/  const*) ; 
 int dname_count_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (size_t) ; 
 int /*<<< orphan*/  rrset_belongs_in_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_u32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * type_rdata_compressable (struct ub_packed_rrset_key*) ; 

__attribute__((used)) static int
packed_rrset_encode(struct ub_packed_rrset_key* key, sldns_buffer* pkt, 
	uint16_t* num_rrs, time_t timenow, struct regional* region,
	int do_data, int do_sig, struct compress_tree_node** tree,
	sldns_pkt_section s, uint16_t qtype, int dnssec, size_t rr_offset)
{
	size_t i, j, owner_pos;
	int r, owner_labs;
	uint16_t owner_ptr = 0;
	struct packed_rrset_data* data = (struct packed_rrset_data*)
		key->entry.data;
	
	/* does this RR type belong in the answer? */
	if(!rrset_belongs_in_reply(s, ntohs(key->rk.type), qtype, dnssec))
		return RETVAL_OK;

	owner_labs = dname_count_labels(key->rk.dname);
	owner_pos = sldns_buffer_position(pkt);

	/* For an rrset with a fixed TTL, use the rrset's TTL as given */
	if((key->rk.flags & PACKED_RRSET_FIXEDTTL) != 0)
		timenow = 0;

	if(do_data) {
		const sldns_rr_descriptor* c = type_rdata_compressable(key);
		for(i=0; i<data->count; i++) {
			/* rrset roundrobin */
			j = (i + rr_offset) % data->count;
			if((r=compress_owner(key, pkt, region, tree, 
				owner_pos, &owner_ptr, owner_labs))
				!= RETVAL_OK)
				return r;
			sldns_buffer_write(pkt, &key->rk.type, 2);
			sldns_buffer_write(pkt, &key->rk.rrset_class, 2);
			if(data->rr_ttl[j] < timenow)
				sldns_buffer_write_u32(pkt, 0);
			else 	sldns_buffer_write_u32(pkt, 
					data->rr_ttl[j]-timenow);
			if(c) {
				if((r=compress_rdata(pkt, data->rr_data[j],
					data->rr_len[j], region, tree, c))
					!= RETVAL_OK)
					return r;
			} else {
				if(sldns_buffer_remaining(pkt) < data->rr_len[j])
					return RETVAL_TRUNC;
				sldns_buffer_write(pkt, data->rr_data[j],
					data->rr_len[j]);
			}
		}
	}
	/* insert rrsigs */
	if(do_sig && dnssec) {
		size_t total = data->count+data->rrsig_count;
		for(i=data->count; i<total; i++) {
			if(owner_ptr && owner_labs != 1) {
				if(sldns_buffer_remaining(pkt) <
					2+4+4+data->rr_len[i]) 
					return RETVAL_TRUNC;
				sldns_buffer_write(pkt, &owner_ptr, 2);
			} else {
				if((r=compress_any_dname(key->rk.dname, 
					pkt, owner_labs, region, tree))
					!= RETVAL_OK)
					return r;
				if(sldns_buffer_remaining(pkt) < 
					4+4+data->rr_len[i])
					return RETVAL_TRUNC;
			}
			sldns_buffer_write_u16(pkt, LDNS_RR_TYPE_RRSIG);
			sldns_buffer_write(pkt, &key->rk.rrset_class, 2);
			if(data->rr_ttl[i] < timenow)
				sldns_buffer_write_u32(pkt, 0);
			else 	sldns_buffer_write_u32(pkt, 
					data->rr_ttl[i]-timenow);
			/* rrsig rdata cannot be compressed, perform 100+ byte
			 * memcopy. */
			sldns_buffer_write(pkt, data->rr_data[i],
				data->rr_len[i]);
		}
	}
	/* change rrnum only after we are sure it fits */
	if(do_data)
		*num_rrs += data->count;
	if(do_sig && dnssec)
		*num_rrs += data->rrsig_count;

	return RETVAL_OK;
}