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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LABEL_IS_PTR (int) ; 
 size_t LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  MAX_COMPRESS_PTRS ; 
 scalar_t__ PTR_OFFSET (int,int) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_read_u8 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
pkt_dname_len(sldns_buffer* pkt)
{
	size_t len = 0;
	int ptrcount = 0;
	uint8_t labellen;
	size_t endpos = 0;

	/* read dname and determine length */
	/* check compression pointers, loops, out of bounds */
	while(1) {
		/* read next label */
		if(sldns_buffer_remaining(pkt) < 1)
			return 0;
		labellen = sldns_buffer_read_u8(pkt);
		if(LABEL_IS_PTR(labellen)) {
			/* compression ptr */
			uint16_t ptr;
			if(sldns_buffer_remaining(pkt) < 1)
				return 0;
			ptr = PTR_OFFSET(labellen, sldns_buffer_read_u8(pkt));
			if(ptrcount++ > MAX_COMPRESS_PTRS)
				return 0; /* loop! */
			if(sldns_buffer_limit(pkt) <= ptr)
				return 0; /* out of bounds! */
			if(!endpos)
				endpos = sldns_buffer_position(pkt);
			sldns_buffer_set_position(pkt, ptr);
		} else {
			/* label contents */
			if(labellen > 0x3f)
				return 0; /* label too long */
			len += 1 + labellen;
			if(len > LDNS_MAX_DOMAINLEN)
				return 0;
			if(labellen == 0) {
				/* end of dname */
				break;
			}
			if(sldns_buffer_remaining(pkt) < labellen)
				return 0;
			sldns_buffer_skip(pkt, (ssize_t)labellen);
		}
	}
	if(endpos)
		sldns_buffer_set_position(pkt, endpos);

	return len;
}