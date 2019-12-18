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
struct srch {int* s_name; int s_value; } ;
typedef  int Char ;

/* Variables and functions */
 int Strcmp (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ inheredoc ; 
 int nsrchn ; 
 struct srch* srchn ; 
 int /*<<< orphan*/  str2short (int*) ; 

int
srchx(Char *cp)
{
    struct srch *sp, *sp1, *sp2;
    int i;

    /*
     * Ignore keywords inside heredocs
     */
    if (inheredoc)
	return -1;

    /*
     * Binary search Sp1 is the beginning of the current search range. Sp2 is
     * one past the end.
     */
    for (sp1 = srchn, sp2 = srchn + nsrchn; sp1 < sp2;) {
	sp = sp1 + ((sp2 - sp1) >> 1);
	if ((i = *cp - *sp->s_name) == 0 &&
	    (i = Strcmp(cp, str2short(sp->s_name))) == 0)
	    return sp->s_value;
	if (i < 0)
	    sp2 = sp;
	else
	    sp1 = sp + 1;
    }
    return (-1);
}