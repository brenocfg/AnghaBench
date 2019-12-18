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
typedef  int /*<<< orphan*/  uint16_t ;
struct msg_parse {int qdcount; void* qclass; void* qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int LDNS_RCODE_FORMERR ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_current (int /*<<< orphan*/ *) ; 
 void* sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_query_section(sldns_buffer* pkt, struct msg_parse* msg)
{
	if(msg->qdcount == 0)
		return 0;
	if(msg->qdcount > 1)
		return LDNS_RCODE_FORMERR;
	log_assert(msg->qdcount == 1);
	if(sldns_buffer_remaining(pkt) <= 0)
		return LDNS_RCODE_FORMERR;
	msg->qname = sldns_buffer_current(pkt);
	if((msg->qname_len = pkt_dname_len(pkt)) == 0)
		return LDNS_RCODE_FORMERR;
	if(sldns_buffer_remaining(pkt) < sizeof(uint16_t)*2)
		return LDNS_RCODE_FORMERR;
	msg->qtype = sldns_buffer_read_u16(pkt);
	msg->qclass = sldns_buffer_read_u16(pkt);
	return 0;
}