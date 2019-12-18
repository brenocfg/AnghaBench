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
struct varent {struct varent* v_parent; struct varent* v_right; scalar_t__ vec; int /*<<< orphan*/  v_name; struct varent* v_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  pintr_push_enable (int*) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_pr (scalar_t__) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xputchar (char) ; 

__attribute__((used)) static void
tw_prlist(struct varent *p)
{
    struct varent *c;

    for (;;) {
	while (p->v_left)
	    p = p->v_left;
x:
	if (p->v_parent == 0)	/* is it the header? */
	    break;
	if (setintr) {
	    int old_pintr_disabled;

	    pintr_push_enable(&old_pintr_disabled);
	    cleanup_until(&old_pintr_disabled);
	}
	xprintf("%s\t", short2str(p->v_name));
	if (p->vec)
	    tw_pr(p->vec);
	xputchar('\n');
	if (p->v_right) {
	    p = p->v_right;
	    continue;
	}
	do {
	    c = p;
	    p = p->v_parent;
	} while (p->v_right == c);
	goto x;
    }
}