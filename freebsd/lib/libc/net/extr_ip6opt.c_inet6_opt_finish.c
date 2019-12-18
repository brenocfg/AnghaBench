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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP6OPT_PAD1 ; 
 int /*<<< orphan*/  IP6OPT_PADN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
inet6_opt_finish(void *extbuf, socklen_t extlen, int offset)
{
	int updatelen = offset > 0 ? (1 + ((offset - 1) | 7)) : 0;

	if (extbuf) {
		u_int8_t *padp;
		int padlen = updatelen - offset;

		if (updatelen > extlen)
			return(-1);

		padp = (u_int8_t *)extbuf + offset;
		if (padlen == 1)
			*padp = IP6OPT_PAD1;
		else if (padlen > 0) {
			*padp++ = IP6OPT_PADN;
			*padp++ = (padlen - 2);
			memset(padp, 0, padlen - 2);
		}
	}

	return(updatelen);
}