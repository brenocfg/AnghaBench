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
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  reprintf (char*,int,...) ; 
 int /*<<< orphan*/  short2str (char*) ; 

__attribute__((used)) static void
str_insert(Char *d, int dat, int dlen, Char *s, int num)
{
    Char *a, *b;

    if (num <= 0)
	return;
    if (num > dlen - dat)
	num = dlen - dat;

#ifdef DEBUG_REFRESH
    reprintf("str_insert() starting: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, short2str(d));
    reprintf("s == \"%s\"n", short2str(s));
#endif /* DEBUG_REFRESH */

    /* open up the space for num chars */
    if (num > 0) {
	b = d + dlen - 1;
	a = b - num;
	while (a >= &d[dat])
	    *b-- = *a--;
	d[dlen] = '\0';		/* just in case */
    }
#ifdef DEBUG_REFRESH
    reprintf("str_insert() after insert: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, short2str(d));
    reprintf("s == \"%s\"n", short2str(s));
#endif /* DEBUG_REFRESH */

    /* copy the characters */
    for (a = d + dat; (a < d + dlen) && (num > 0); num--)
	*a++ = *s++;

#ifdef DEBUG_REFRESH
    reprintf("str_insert() after copy: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, d, short2str(s));
    reprintf("s == \"%s\"n", short2str(s));
#endif /* DEBUG_REFRESH */
}