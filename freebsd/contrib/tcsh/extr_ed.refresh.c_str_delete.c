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
 int /*<<< orphan*/  reprintf (char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (char*) ; 

__attribute__((used)) static void
str_delete(Char *d, int dat, int dlen, int num)
{
    Char *a, *b;

    if (num <= 0)
	return;
    if (dat + num >= dlen) {
	d[dat] = '\0';
	return;
    }

#ifdef DEBUG_REFRESH
    reprintf("str_delete() starting: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, short2str(d));
#endif /* DEBUG_REFRESH */

    /* open up the space for num chars */
    if (num > 0) {
	b = d + dat;
	a = b + num;
	while (a < &d[dlen])
	    *b++ = *a++;
	d[dlen] = '\0';		/* just in case */
    }
#ifdef DEBUG_REFRESH
    reprintf("str_delete() after delete: %d at %d max %d, d == \"%s\"\n",
	    num, dat, dlen, short2str(d));
#endif /* DEBUG_REFRESH */
}