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
struct edns_option {scalar_t__ opt_code; scalar_t__ opt_len; int /*<<< orphan*/  opt_data; struct edns_option* next; } ;
struct edns_data {scalar_t__ udp_size; scalar_t__ bits; struct edns_option* opt_list; int /*<<< orphan*/  edns_version; int /*<<< orphan*/  ext_rcode; int /*<<< orphan*/  edns_present; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_OPT ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_read_u16_at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16_at (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
attach_edns_record(sldns_buffer* pkt, struct edns_data* edns)
{
	size_t len;
	size_t rdatapos;
	struct edns_option* opt;
	if(!edns || !edns->edns_present)
		return;
	/* inc additional count */
	sldns_buffer_write_u16_at(pkt, 10,
		sldns_buffer_read_u16_at(pkt, 10) + 1);
	len = sldns_buffer_limit(pkt);
	sldns_buffer_clear(pkt);
	sldns_buffer_set_position(pkt, len);
	/* write EDNS record */
	sldns_buffer_write_u8(pkt, 0); /* '.' label */
	sldns_buffer_write_u16(pkt, LDNS_RR_TYPE_OPT); /* type */
	sldns_buffer_write_u16(pkt, edns->udp_size); /* class */
	sldns_buffer_write_u8(pkt, edns->ext_rcode); /* ttl */
	sldns_buffer_write_u8(pkt, edns->edns_version);
	sldns_buffer_write_u16(pkt, edns->bits);
	rdatapos = sldns_buffer_position(pkt);
	sldns_buffer_write_u16(pkt, 0); /* rdatalen */
	/* write rdata */
	for(opt=edns->opt_list; opt; opt=opt->next) {
		sldns_buffer_write_u16(pkt, opt->opt_code);
		sldns_buffer_write_u16(pkt, opt->opt_len);
		if(opt->opt_len != 0)
			sldns_buffer_write(pkt, opt->opt_data, opt->opt_len);
	}
	if(edns->opt_list)
		sldns_buffer_write_u16_at(pkt, rdatapos, 
			sldns_buffer_position(pkt)-rdatapos-2);
	sldns_buffer_flip(pkt);
}