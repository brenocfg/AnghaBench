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
struct regional {int dummy; } ;
struct msg_parse {int qdcount; int ancount; int nscount; int arcount; scalar_t__ ar_rrsets; scalar_t__ ns_rrsets; scalar_t__ an_rrsets; scalar_t__ rrset_count; void* flags; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_HEADER_SIZE ; 
 int LDNS_RCODE_FORMERR ; 
 int /*<<< orphan*/  LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int parse_query_section (int /*<<< orphan*/ *,struct msg_parse*) ; 
 int parse_section (int /*<<< orphan*/ *,struct msg_parse*,struct regional*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  sldns_buffer_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 

int
parse_packet(sldns_buffer* pkt, struct msg_parse* msg, struct regional* region)
{
	int ret;
	if(sldns_buffer_remaining(pkt) < LDNS_HEADER_SIZE)
		return LDNS_RCODE_FORMERR;
	/* read the header */
	sldns_buffer_read(pkt, &msg->id, sizeof(uint16_t));
	msg->flags = sldns_buffer_read_u16(pkt);
	msg->qdcount = sldns_buffer_read_u16(pkt);
	msg->ancount = sldns_buffer_read_u16(pkt);
	msg->nscount = sldns_buffer_read_u16(pkt);
	msg->arcount = sldns_buffer_read_u16(pkt);
	if(msg->qdcount > 1)
		return LDNS_RCODE_FORMERR;
	if((ret = parse_query_section(pkt, msg)) != 0)
		return ret;
	if((ret = parse_section(pkt, msg, region, LDNS_SECTION_ANSWER,
		msg->ancount, &msg->an_rrsets)) != 0)
		return ret;
	if((ret = parse_section(pkt, msg, region, LDNS_SECTION_AUTHORITY,
		msg->nscount, &msg->ns_rrsets)) != 0)
		return ret;
	if(sldns_buffer_remaining(pkt) == 0 && msg->arcount == 1) {
		/* BIND accepts leniently that an EDNS record is missing.
		 * so, we do too. */
	} else if((ret = parse_section(pkt, msg, region,
		LDNS_SECTION_ADDITIONAL, msg->arcount, &msg->ar_rrsets)) != 0)
		return ret;
	/* if(sldns_buffer_remaining(pkt) > 0) { */
		/* there is spurious data at end of packet. ignore */
	/* } */
	msg->rrset_count = msg->an_rrsets + msg->ns_rrsets + msg->ar_rrsets;
	return 0;
}