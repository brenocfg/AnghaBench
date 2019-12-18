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
struct varent {scalar_t__ v_name; struct varent* v_parent; struct varent* v_right; struct varent* v_left; } ;
typedef  int Strbuf ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (int*,scalar_t__) ; 
 int /*<<< orphan*/  USE (int*) ; 
 struct varent* tw_vptr ; 

int
tw_shvar_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    struct varent *p;
    struct varent *c;

    USE(flags);
    USE(dir);
    if ((p = tw_vptr) == NULL)
	return 0;		/* just in case */

    Strbuf_append(res, p->v_name); /* we know that this name is here now */

    /* now find the next one */
    for (;;) {
	if (p->v_right) {	/* if we can go right */
	    p = p->v_right;
	    while (p->v_left)
		p = p->v_left;
	}
	else {			/* else go up */
	    do {
		c = p;
		p = p->v_parent;
	    } while (p->v_right == c);
	}
	if (p->v_parent == 0) {	/* is it the header? */
	    tw_vptr = NULL;
	    return 1;
	}
	if (p->v_name) {
	    tw_vptr = p;	/* save state for the next call */
	    return 1;
	}
    }
}