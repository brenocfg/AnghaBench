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
 int INT_MAX ; 

__attribute__((used)) static Char *
c_number(Char *p, int *num, int dval)
{
    int i;
    int sign = 1;

    if (*++p == '^') {
	*num = 1;
	return(p);
    }
    if (*p == '$') {
	if (*++p != '-') {
	    *num = INT_MAX;	/* Handle $ */
	    return(--p);
	}
	sign = -1;		/* Handle $- */
	++p;
    }
    for (i = 0; *p >= '0' && *p <= '9'; i = 10 * i + *p++ - '0')
	continue;
    *num = (sign < 0 ? dval - i : i);
    return(--p);
}