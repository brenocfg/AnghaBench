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

/* Variables and functions */
 size_t sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 int sldns_str_print (char**,size_t*,char*,int) ; 

__attribute__((used)) static int rr_comment_rrsig(char** s, size_t* slen, uint8_t* rr,
	size_t rrlen, size_t dname_off)
{
	size_t rdlen;
	uint8_t* rdata;
	if(rrlen < dname_off + 10) return 0;
	rdlen = sldns_read_uint16(rr+dname_off+8);
	if(rrlen < dname_off + 10 + rdlen) return 0;
	rdata = rr + dname_off + 10;
	if(rdlen < 18) return 0;
	return sldns_str_print(s, slen, " ;{id = %d}",
		(int)sldns_read_uint16(rdata+16));
}