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
struct varent {int v_flags; struct varent* v_parent; struct varent* v_right; int /*<<< orphan*/  vec; int /*<<< orphan*/  v_name; struct varent* v_left; } ;

/* Variables and functions */
 int blklen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkpr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  pintr_push_enable (int*) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
plist(struct varent *p, int what)
{
    struct varent *c;
    int len;

    for (;;) {
	while (p->v_left)
	    p = p->v_left;
x:
	if (p->v_parent == 0)	/* is it the header? */
	    break;
	if ((p->v_flags & what) != 0) {
	    if (setintr) {
		int old_pintr_disabled;

		pintr_push_enable(&old_pintr_disabled);
		cleanup_until(&old_pintr_disabled);
	    }
	    len = blklen(p->vec);
	    xprintf("%S\t", p->v_name);
	    if (len != 1)
		xputchar('(');
	    blkpr(p->vec);
	    if (len != 1)
		xputchar(')');
	    xputchar('\n');
	}
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