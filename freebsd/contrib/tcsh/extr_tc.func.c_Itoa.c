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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  char Char ;

/* Variables and functions */
 int CHAR_BIT ; 
 char* xmalloc (int) ; 

Char *
Itoa(int n, size_t min_digits, Char attributes)
{
    /*
     * The array size here is derived from
     *	log8(UINT_MAX)
     * which is guaranteed to be enough for a decimal
     * representation.  We add 1 because integer divide
     * rounds down.
     */
#ifndef CHAR_BIT
# define CHAR_BIT 8
#endif
    Char buf[CHAR_BIT * sizeof(int) / 3 + 1], *res, *p, *s;
    unsigned int un;	/* handle most negative # too */
    int pad = (min_digits != 0);

    if (sizeof(buf) - 1 < min_digits)
	min_digits = sizeof(buf) - 1;

    un = n;
    if (n < 0)
	un = -n;

    p = buf;
    do {
	*p++ = un % 10 + '0';
	un /= 10;
    } while ((pad && (ssize_t)--min_digits > 0) || un != 0);

    res = xmalloc((p - buf + 2) * sizeof(*res));
    s = res;
    if (n < 0)
	*s++ = '-';
    while (p > buf)
	*s++ = *--p | attributes;

    *s = '\0';
    return res;
}