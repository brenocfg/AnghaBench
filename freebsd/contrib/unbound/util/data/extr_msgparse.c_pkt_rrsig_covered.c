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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pkt_rrsig_covered(sldns_buffer* pkt, uint8_t* here, uint16_t* type)
{
	size_t pos = sldns_buffer_position(pkt);
	sldns_buffer_set_position(pkt, (size_t)(here-sldns_buffer_begin(pkt)));
	/* ttl + len + size of small rrsig(rootlabel, no signature) */
	if(sldns_buffer_remaining(pkt) < 4+2+19)
		return 0;
	sldns_buffer_skip(pkt, 4); /* ttl */
	if(sldns_buffer_read_u16(pkt) < 19) /* too short */ {
		sldns_buffer_set_position(pkt, pos);
		return 0;
	}
	*type = sldns_buffer_read_u16(pkt);
	sldns_buffer_set_position(pkt, pos);
	return 1;
}