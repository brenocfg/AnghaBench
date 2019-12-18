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
 size_t dname_valid (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
rrsig_get_signer(uint8_t* data, size_t len, uint8_t** sname, size_t* slen)
{
	/* RRSIG rdata is not allowed to be compressed, it is stored
	 * uncompressed in memory as well, so return a ptr to the name */
	if(len < 21) {
		/* too short RRSig:
		 * short, byte, byte, long, long, long, short, "." is
		 * 2	1	1	4	4  4	2	1 = 19
		 * 			and a skip of 18 bytes to the name.
		 * +2 for the rdatalen is 21 bytes len for root label */
		*sname = NULL;
		*slen = 0;
		return;
	}
	data += 20; /* skip the fixed size bits */
	len -= 20;
	*slen = dname_valid(data, len);
	if(!*slen) {
		/* bad dname in this rrsig. */
		*sname = NULL;
		return;
	}
	*sname = data;
}