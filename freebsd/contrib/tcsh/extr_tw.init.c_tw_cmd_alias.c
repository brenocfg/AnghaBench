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
 struct varent aliases ; 
 int /*<<< orphan*/  tw_cmd_add (scalar_t__) ; 

__attribute__((used)) static void
tw_cmd_alias(void)
{
    struct varent *p;
    struct varent *c;

    p = &aliases;
    for (;;) {
	while (p->v_left)
	    p = p->v_left;
x:
	if (p->v_parent == 0) /* is it the header? */
	    return;
	if (p->v_name)
	    tw_cmd_add(p->v_name);
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