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
typedef  int uint16_t ;
struct worker {int /*<<< orphan*/  scratchpad; int /*<<< orphan*/  env; } ;
struct edns_data {int /*<<< orphan*/ * opt_list; int /*<<< orphan*/  bits; int /*<<< orphan*/  udp_size; int /*<<< orphan*/  edns_version; } ;
struct comm_reply {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int BIT_QR ; 
 int BIT_RA ; 
 int /*<<< orphan*/  EDNS_ADVERTISED_SIZE ; 
 int /*<<< orphan*/  EDNS_ADVERTISED_VERSION ; 
 int /*<<< orphan*/  EDNS_DO ; 
 int /*<<< orphan*/  LDNS_CD_SET (int /*<<< orphan*/ ) ; 
 unsigned int LDNS_CD_WIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RD_SET (int /*<<< orphan*/ ) ; 
 unsigned int LDNS_RD_WIRE (int /*<<< orphan*/ ) ; 
 int LDNS_RR_CLASS_CH ; 
 int LDNS_RR_TYPE_TXT ; 
 int /*<<< orphan*/  attach_edns_record (int /*<<< orphan*/ *,struct edns_data*) ; 
 scalar_t__ calc_edns_field_size (struct edns_data*) ; 
 int /*<<< orphan*/  inplace_cb_reply_local_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct edns_data*,struct comm_reply*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
chaos_replystr(sldns_buffer* pkt, char** str, int num, struct edns_data* edns,
	struct worker* worker, struct comm_reply* repinfo)
{
	int i;
	unsigned int rd = LDNS_RD_WIRE(sldns_buffer_begin(pkt));
	unsigned int cd = LDNS_CD_WIRE(sldns_buffer_begin(pkt));
	sldns_buffer_clear(pkt);
	sldns_buffer_skip(pkt, (ssize_t)sizeof(uint16_t)); /* skip id */
	sldns_buffer_write_u16(pkt, (uint16_t)(BIT_QR|BIT_RA));
	if(rd) LDNS_RD_SET(sldns_buffer_begin(pkt));
	if(cd) LDNS_CD_SET(sldns_buffer_begin(pkt));
	sldns_buffer_write_u16(pkt, 1); /* qdcount */
	sldns_buffer_write_u16(pkt, (uint16_t)num); /* ancount */
	sldns_buffer_write_u16(pkt, 0); /* nscount */
	sldns_buffer_write_u16(pkt, 0); /* arcount */
	(void)query_dname_len(pkt); /* skip qname */
	sldns_buffer_skip(pkt, (ssize_t)sizeof(uint16_t)); /* skip qtype */
	sldns_buffer_skip(pkt, (ssize_t)sizeof(uint16_t)); /* skip qclass */
	for(i=0; i<num; i++) {
		size_t len = strlen(str[i]);
		if(len>255) len=255; /* cap size of TXT record */
		sldns_buffer_write_u16(pkt, 0xc00c); /* compr ptr to query */
		sldns_buffer_write_u16(pkt, LDNS_RR_TYPE_TXT);
		sldns_buffer_write_u16(pkt, LDNS_RR_CLASS_CH);
		sldns_buffer_write_u32(pkt, 0); /* TTL */
		sldns_buffer_write_u16(pkt, sizeof(uint8_t) + len);
		sldns_buffer_write_u8(pkt, len);
		sldns_buffer_write(pkt, str[i], len);
	}
	sldns_buffer_flip(pkt);
	edns->edns_version = EDNS_ADVERTISED_VERSION;
	edns->udp_size = EDNS_ADVERTISED_SIZE;
	edns->bits &= EDNS_DO;
	if(!inplace_cb_reply_local_call(&worker->env, NULL, NULL, NULL,
		LDNS_RCODE_NOERROR, edns, repinfo, worker->scratchpad))
			edns->opt_list = NULL;
	if(sldns_buffer_capacity(pkt) >=
		sldns_buffer_limit(pkt)+calc_edns_field_size(edns))
		attach_edns_record(pkt, edns);
}