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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ pkt_dname_len (int /*<<< orphan*/ *) ; 
 int sldns_buffer_position (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u8 (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nsec_at_apex(sldns_buffer* pkt)
{
	/* we are at ttl position in packet. */
	size_t pos = sldns_buffer_position(pkt);
	uint16_t rdatalen;
	if(sldns_buffer_remaining(pkt) < 7) /* ttl+len+root */
		return 0; /* eek! */
	sldns_buffer_skip(pkt, 4); /* ttl */;
	rdatalen = sldns_buffer_read_u16(pkt);
	if(sldns_buffer_remaining(pkt) < rdatalen) {
		sldns_buffer_set_position(pkt, pos);
		return 0; /* parse error happens later */
	}
	/* must validate the nsec next domain name format */
	if(pkt_dname_len(pkt) == 0) {
		sldns_buffer_set_position(pkt, pos);
		return 0; /* parse error */
	}

	/* see if SOA bit is set. */
	if(sldns_buffer_position(pkt) < pos+4+rdatalen) {
		/* nsec type bitmap contains items */
		uint8_t win, blen, bits;
		/* need: windownum, bitmap len, firstbyte */
		if(sldns_buffer_position(pkt)+3 > pos+4+rdatalen) {
			sldns_buffer_set_position(pkt, pos);
			return 0; /* malformed nsec */
		}
		win = sldns_buffer_read_u8(pkt);
		blen = sldns_buffer_read_u8(pkt);
		bits = sldns_buffer_read_u8(pkt);
		/* 0window always first window. bitlen >=1 or parse
		   error really. bit 0x2 is SOA. */
		if(win == 0 && blen >= 1 && (bits & 0x02)) {
			sldns_buffer_set_position(pkt, pos);
			return 1;
		}
	}

	sldns_buffer_set_position(pkt, pos);
	return 0;
}