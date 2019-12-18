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
typedef  int uint16_t ;
struct auth_chunk {size_t len; int /*<<< orphan*/  data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 size_t LDNS_HEADER_SIZE ; 
 size_t LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_init_frm_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read_u32 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
chunk_rrlist_get_current(struct auth_chunk* rr_chunk, int rr_num,
	size_t rr_pos, uint8_t** rr_dname, uint16_t* rr_type,
	uint16_t* rr_class, uint32_t* rr_ttl, uint16_t* rr_rdlen,
	uint8_t** rr_rdata, size_t* rr_nextpos)
{
	sldns_buffer pkt;
	/* integrity checks on position */
	if(!rr_chunk) return 0;
	if(rr_chunk->len < LDNS_HEADER_SIZE) return 0;
	if(rr_num >= (int)LDNS_ANCOUNT(rr_chunk->data)) return 0;
	if(rr_pos >= rr_chunk->len) return 0;

	/* fetch rr information */
	sldns_buffer_init_frm_data(&pkt, rr_chunk->data, rr_chunk->len);
	if(rr_pos == 0) {
		size_t i;
		/* skip question section */
		sldns_buffer_set_position(&pkt, LDNS_HEADER_SIZE);
		for(i=0; i<LDNS_QDCOUNT(rr_chunk->data); i++) {
			if(pkt_dname_len(&pkt) == 0) return 0;
			if(sldns_buffer_remaining(&pkt) < 4) return 0;
			sldns_buffer_skip(&pkt, 4); /* type and class */
		}
	} else	{
		sldns_buffer_set_position(&pkt, rr_pos);
	}
	*rr_dname = sldns_buffer_current(&pkt);
	if(pkt_dname_len(&pkt) == 0) return 0;
	if(sldns_buffer_remaining(&pkt) < 10) return 0;
	*rr_type = sldns_buffer_read_u16(&pkt);
	*rr_class = sldns_buffer_read_u16(&pkt);
	*rr_ttl = sldns_buffer_read_u32(&pkt);
	*rr_rdlen = sldns_buffer_read_u16(&pkt);
	if(sldns_buffer_remaining(&pkt) < (*rr_rdlen)) return 0;
	*rr_rdata = sldns_buffer_current(&pkt);
	sldns_buffer_skip(&pkt, (ssize_t)(*rr_rdlen));
	*rr_nextpos = sldns_buffer_position(&pkt);
	return 1;
}