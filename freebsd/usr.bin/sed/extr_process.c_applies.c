#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s_command {scalar_t__ startline; scalar_t__ nonsel; TYPE_2__* a1; TYPE_2__* a2; } ;
struct TYPE_3__ {scalar_t__ l; } ;
struct TYPE_4__ {int type; TYPE_1__ u; } ;

/* Variables and functions */
 int AT_LINE ; 
#define  AT_RELLINE 128 
 int MATCH (TYPE_2__*) ; 
 int lastaddr ; 
 scalar_t__ linenum ; 

__attribute__((used)) static inline int
applies(struct s_command *cp)
{
	int r;

	lastaddr = 0;
	if (cp->a1 == NULL && cp->a2 == NULL)
		r = 1;
	else if (cp->a2)
		if (cp->startline > 0) {
                        switch (cp->a2->type) {
                        case AT_RELLINE:
                                if (linenum - cp->startline <= cp->a2->u.l)
                                        r = 1;
                                else {
				        cp->startline = 0;
				        r = 0;
                                }
                                break;
                        default:
                                if (MATCH(cp->a2)) {
                                        cp->startline = 0;
                                        lastaddr = 1;
                                        r = 1;
                                } else if (cp->a2->type == AT_LINE &&
                                            linenum > cp->a2->u.l) {
                                        /*
                                         * We missed the 2nd address due to a
                                         * branch, so just close the range and
                                         * return false.
                                         */
                                        cp->startline = 0;
                                        r = 0;
                                } else
                                        r = 1;
                        }
		} else if (cp->a1 && MATCH(cp->a1)) {
			/*
			 * If the second address is a number less than or
			 * equal to the line number first selected, only
			 * one line shall be selected.
			 *	-- POSIX 1003.2
			 * Likewise if the relative second line address is zero.
			 */
			if ((cp->a2->type == AT_LINE &&
			    linenum >= cp->a2->u.l) ||
			    (cp->a2->type == AT_RELLINE && cp->a2->u.l == 0))
				lastaddr = 1;
			else {
				cp->startline = linenum;
			}
			r = 1;
		} else
			r = 0;
	else
		r = MATCH(cp->a1);
	return (cp->nonsel ? ! r : r);
}