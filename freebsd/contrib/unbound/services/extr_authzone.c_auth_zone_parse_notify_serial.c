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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct query_info {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  q ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  memset (struct query_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_info_parse (struct query_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read_u32 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

int
auth_zone_parse_notify_serial(sldns_buffer* pkt, uint32_t *serial)
{
	struct query_info q;
	uint16_t rdlen;
	memset(&q, 0, sizeof(q));
	sldns_buffer_set_position(pkt, 0);
	if(!query_info_parse(&q, pkt)) return 0;
	if(LDNS_ANCOUNT(sldns_buffer_begin(pkt)) == 0) return 0;
	/* skip name of RR in answer section */
	if(sldns_buffer_remaining(pkt) < 1) return 0;
	if(pkt_dname_len(pkt) == 0) return 0;
	/* check type */
	if(sldns_buffer_remaining(pkt) < 10 /* type,class,ttl,rdatalen*/)
		return 0;
	if(sldns_buffer_read_u16(pkt) != LDNS_RR_TYPE_SOA) return 0;
	sldns_buffer_skip(pkt, 2); /* class */
	sldns_buffer_skip(pkt, 4); /* ttl */
	rdlen = sldns_buffer_read_u16(pkt); /* rdatalen */
	if(sldns_buffer_remaining(pkt) < rdlen) return 0;
	if(rdlen < 22) return 0; /* bad soa length */
	sldns_buffer_skip(pkt, (ssize_t)(rdlen-20));
	*serial = sldns_buffer_read_u32(pkt);
	/* return true when has serial in answer section */
	return 1;
}