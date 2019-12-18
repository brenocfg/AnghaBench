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
struct regional {int dummy; } ;
struct edns_data {int udp_size; int edns_present; int /*<<< orphan*/ * opt_list; void* bits; void* edns_version; void* ext_rcode; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 int LDNS_ARCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_NSCOUNT (int /*<<< orphan*/ ) ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 int LDNS_RCODE_FORMERR ; 
 int LDNS_RCODE_SERVFAIL ; 
 void* LDNS_RR_TYPE_OPT ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memset (struct edns_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_edns_options (int /*<<< orphan*/ *,size_t,struct edns_data*,struct regional*) ; 
 int pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_pkt_rrs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ *) ; 
 void* sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 void* sldns_buffer_read_u8 (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 

int 
parse_edns_from_pkt(sldns_buffer* pkt, struct edns_data* edns,
	struct regional* region)
{
	size_t rdata_len;
	uint8_t* rdata_ptr;
	log_assert(LDNS_QDCOUNT(sldns_buffer_begin(pkt)) == 1);
	if(LDNS_ANCOUNT(sldns_buffer_begin(pkt)) != 0 ||
		LDNS_NSCOUNT(sldns_buffer_begin(pkt)) != 0) {
		if(!skip_pkt_rrs(pkt, ((int)LDNS_ANCOUNT(sldns_buffer_begin(pkt)))+
			((int)LDNS_NSCOUNT(sldns_buffer_begin(pkt)))))
			return 0;
	}
	/* check edns section is present */
	if(LDNS_ARCOUNT(sldns_buffer_begin(pkt)) > 1) {
		return LDNS_RCODE_FORMERR;
	}
	if(LDNS_ARCOUNT(sldns_buffer_begin(pkt)) == 0) {
		memset(edns, 0, sizeof(*edns));
		edns->udp_size = 512;
		return 0;
	}
	/* domain name must be the root of length 1. */
	if(pkt_dname_len(pkt) != 1)
		return LDNS_RCODE_FORMERR;
	if(sldns_buffer_remaining(pkt) < 10) /* type, class, ttl, rdatalen */
		return LDNS_RCODE_FORMERR;
	if(sldns_buffer_read_u16(pkt) != LDNS_RR_TYPE_OPT)
		return LDNS_RCODE_FORMERR;
	edns->edns_present = 1;
	edns->udp_size = sldns_buffer_read_u16(pkt); /* class is udp size */
	edns->ext_rcode = sldns_buffer_read_u8(pkt); /* ttl used for bits */
	edns->edns_version = sldns_buffer_read_u8(pkt);
	edns->bits = sldns_buffer_read_u16(pkt);
	edns->opt_list = NULL;

	/* take the options */
	rdata_len = sldns_buffer_read_u16(pkt);
	if(sldns_buffer_remaining(pkt) < rdata_len)
		return LDNS_RCODE_FORMERR;
	rdata_ptr = sldns_buffer_current(pkt);
	if(!parse_edns_options(rdata_ptr, rdata_len, edns, region))
		return LDNS_RCODE_SERVFAIL;

	/* ignore rrsigs */

	return 0;
}