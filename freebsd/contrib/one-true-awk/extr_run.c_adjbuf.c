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

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ realloc (char*,int) ; 

int adjbuf(char **pbuf, int *psiz, int minlen, int quantum, char **pbptr,
	const char *whatrtn)
/* pbuf:    address of pointer to buffer being managed
 * psiz:    address of buffer size variable
 * minlen:  minimum length of buffer needed
 * quantum: buffer size quantum
 * pbptr:   address of movable pointer into buffer, or 0 if none
 * whatrtn: name of the calling routine if failure should cause fatal error
 *
 * return   0 for realloc failure, !=0 for success
 */
{
	if (minlen > *psiz) {
		char *tbuf;
		int rminlen = quantum ? minlen % quantum : 0;
		int boff = pbptr ? *pbptr - *pbuf : 0;
		/* round up to next multiple of quantum */
		if (rminlen)
			minlen += quantum - rminlen;
		tbuf = (char *) realloc(*pbuf, minlen);
		dprintf( ("adjbuf %s: %d %d (pbuf=%p, tbuf=%p)\n", whatrtn, *psiz, minlen, (void *) *pbuf, (void *) tbuf) );
		if (tbuf == NULL) {
			if (whatrtn)
				FATAL("out of memory in %s", whatrtn);
			return 0;
		}
		*pbuf = tbuf;
		*psiz = minlen;
		if (pbptr)
			*pbptr = tbuf + boff;
	}
	return 1;
}