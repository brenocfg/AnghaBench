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
struct varent {struct varent* v_parent; struct varent* v_right; scalar_t__ v_name; struct varent* v_left; } ;

/* Variables and functions */
 struct varent* tw_vptr ; 

__attribute__((used)) static void
tw_vptr_start(struct varent *c)
{
    tw_vptr = c;		/* start at beginning of variable list */

    for (;;) {
	while (tw_vptr->v_left)
	    tw_vptr = tw_vptr->v_left;
x:
	if (tw_vptr->v_parent == 0) {	/* is it the header? */
	    tw_vptr = NULL;
	    return;
	}
	if (tw_vptr->v_name)
	    return;		/* found first one */
	if (tw_vptr->v_right) {
	    tw_vptr = tw_vptr->v_right;
	    continue;
	}
	do {
	    c = tw_vptr;
	    tw_vptr = tw_vptr->v_parent;
	} while (tw_vptr->v_right == c);
	goto x;
    }
}