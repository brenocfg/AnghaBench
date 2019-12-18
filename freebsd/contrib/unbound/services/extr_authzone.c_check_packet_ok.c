#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct auth_xfer {int namelen; scalar_t__ dclass; int /*<<< orphan*/  name; TYPE_1__* task_probe; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_ID_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_PACKET_QUERY ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_QR_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ dname_pkt_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_dname_len (int /*<<< orphan*/ *) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_current (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read_u32 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
check_packet_ok(sldns_buffer* pkt, uint16_t qtype, struct auth_xfer* xfr,
	uint32_t* serial)
{
	/* parse to see if packet worked, valid reply */

	/* check serial number of SOA */
	if(sldns_buffer_limit(pkt) < LDNS_HEADER_SIZE)
		return 0;

	/* check ID */
	if(LDNS_ID_WIRE(sldns_buffer_begin(pkt)) != xfr->task_probe->id)
		return 0;

	/* check flag bits and rcode */
	if(!LDNS_QR_WIRE(sldns_buffer_begin(pkt)))
		return 0;
	if(LDNS_OPCODE_WIRE(sldns_buffer_begin(pkt)) != LDNS_PACKET_QUERY)
		return 0;
	if(LDNS_RCODE_WIRE(sldns_buffer_begin(pkt)) != LDNS_RCODE_NOERROR)
		return 0;

	/* check qname */
	if(LDNS_QDCOUNT(sldns_buffer_begin(pkt)) != 1)
		return 0;
	sldns_buffer_skip(pkt, LDNS_HEADER_SIZE);
	if(sldns_buffer_remaining(pkt) < xfr->namelen)
		return 0;
	if(query_dname_compare(sldns_buffer_current(pkt), xfr->name) != 0)
		return 0;
	sldns_buffer_skip(pkt, (ssize_t)xfr->namelen);

	/* check qtype, qclass */
	if(sldns_buffer_remaining(pkt) < 4)
		return 0;
	if(sldns_buffer_read_u16(pkt) != qtype)
		return 0;
	if(sldns_buffer_read_u16(pkt) != xfr->dclass)
		return 0;

	if(serial) {
		uint16_t rdlen;
		/* read serial number, from answer section SOA */
		if(LDNS_ANCOUNT(sldns_buffer_begin(pkt)) == 0)
			return 0;
		/* read from first record SOA record */
		if(sldns_buffer_remaining(pkt) < 1)
			return 0;
		if(dname_pkt_compare(pkt, sldns_buffer_current(pkt),
			xfr->name) != 0)
			return 0;
		if(!pkt_dname_len(pkt))
			return 0;
		/* type, class, ttl, rdatalen */
		if(sldns_buffer_remaining(pkt) < 4+4+2)
			return 0;
		if(sldns_buffer_read_u16(pkt) != qtype)
			return 0;
		if(sldns_buffer_read_u16(pkt) != xfr->dclass)
			return 0;
		sldns_buffer_skip(pkt, 4); /* ttl */
		rdlen = sldns_buffer_read_u16(pkt);
		if(sldns_buffer_remaining(pkt) < rdlen)
			return 0;
		if(sldns_buffer_remaining(pkt) < 1)
			return 0;
		if(!pkt_dname_len(pkt)) /* soa name */
			return 0;
		if(sldns_buffer_remaining(pkt) < 1)
			return 0;
		if(!pkt_dname_len(pkt)) /* soa name */
			return 0;
		if(sldns_buffer_remaining(pkt) < 20)
			return 0;
		*serial = sldns_buffer_read_u32(pkt);
	}
	return 1;
}