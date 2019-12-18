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
typedef  int u_int8_t ;
typedef  int socklen_t ;

/* Variables and functions */
 int IP6OPT_PAD1 ; 
 int /*<<< orphan*/  IP6OPT_PADN ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int
inet6_opt_append(void *extbuf, socklen_t extlen, int offset, u_int8_t type,
		 socklen_t len, u_int8_t align, void **databufp)
{
	int currentlen = offset, padlen = 0;

	/*
	 * The option type must have a value from 2 to 255, inclusive.
	 * (0 and 1 are reserved for the Pad1 and PadN options, respectively.)
	 */
	if (type < 2)
		return(-1);

	/*
	 * The option data length must have a value between 0 and 255,
	 * inclusive, and is the length of the option data that follows.
	 */
	if (len > 255 || len < 0 )
		return(-1);

	/*
	 * The align parameter must have a value of 1, 2, 4, or 8.
	 * The align value can not exceed the value of len.
	 */
	if (align != 1 && align != 2 && align != 4 && align != 8)
		return(-1);
	if (align > len)
		return(-1);

	/* Calculate the padding length. */
	currentlen += 2 + len;	/* 2 means "type + len" */
	if (currentlen % align)
		padlen = align - (currentlen % align);

	/* The option must fit in the extension header buffer. */
	currentlen += padlen;
	if (extlen &&		/* XXX: right? */
	    currentlen > extlen)
		return(-1);

	if (extbuf) {
		u_int8_t *optp = (u_int8_t *)extbuf + offset;

		if (padlen == 1) {
			/* insert a Pad1 option */
			*optp = IP6OPT_PAD1;
			optp++;
		}
		else if (padlen > 0) {
			/* insert a PadN option for alignment */
			*optp++ = IP6OPT_PADN;
			*optp++ = padlen - 2;
			memset(optp, 0, padlen - 2);
			optp += (padlen - 2);
		}

		*optp++ = type;
		*optp++ = len;

		*databufp = optp;
	}

	return(currentlen);
}