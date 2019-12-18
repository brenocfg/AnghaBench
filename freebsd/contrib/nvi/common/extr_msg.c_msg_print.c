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
struct TYPE_2__ {int /*<<< orphan*/  ibcw; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,char*,size_t) ; 
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE_SPACE (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_GOTOC (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  ISPRINT (char) ; 
 char* KEY_NAME (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strlen (char const*) ; 

char *
msg_print(
	SCR *sp,
	const char *s,
	int *needfree)
{
	size_t blen, nlen;
	char *bp, *ep, *p, *t;
	CHAR_T *wp, *cp;
	size_t wlen;

	*needfree = 0;

	/* XXX Not good for debugging ex_read & ex_filter.*/
	CHAR2INT5(sp, EXP(sp)->ibcw, (char *)s, strlen(s) + 1, wp, wlen);
	for (cp = wp; *cp != '\0'; ++cp)
		if (!ISPRINT(*cp))
			break;
	if (*cp == '\0')
		return ((char *)s);	/* SAFE: needfree set to 0. */

	nlen = 0;
	if (0) {
retry:		if (sp == NULL)
			free(bp);
		else
			FREE_SPACE(sp, bp, blen);
		*needfree = 0;
	}
	nlen += 256;
	if (sp == NULL) {
		if ((bp = malloc(nlen)) == NULL)
			goto alloc_err;
	} else
		GET_SPACE_GOTOC(sp, bp, blen, nlen);
	if (0) {
alloc_err:	return ("");
	}
	*needfree = 1;

	for (p = bp, ep = (bp + blen) - 1; *wp != '\0' && p < ep; ++wp)
		for (t = KEY_NAME(sp, *wp); *t != '\0' && p < ep; *p++ = *t++);
	if (p == ep)
		goto retry;
	*p = '\0';
	return (bp);
}