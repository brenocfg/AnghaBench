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
struct varent {int v_bal; struct varent* v_right; struct varent* v_left; void** v_link; struct varent* v_parent; } ;

/* Variables and functions */
 void* rleft (struct varent*) ; 
 void* rright (struct varent*) ; 

__attribute__((used)) static void
balance(struct varent *p, int f, int d)
{
    struct varent *pp;

#ifndef lint
    struct varent *t;	/* used by the rotate macros */
#endif /* !lint */
    int ff;
#ifdef lint
    ff = 0;	/* Sun's lint is dumb! */
#endif

    /*
     * Ok, from here on, p is the node we're operating on; pp is it's parent; f
     * is the branch of p from which we have come; ff is the branch of pp which
     * is p.
     */
    for (; (pp = p->v_parent) != 0; p = pp, f = ff) {
	ff = pp->v_right == p;
	if (f ^ d) {		/* right heavy */
	    switch (p->v_bal) {
	    case -1:		/* was left heavy */
		p->v_bal = 0;
		break;
	    case 0:		/* was balanced */
		p->v_bal = 1;
		break;
	    case 1:		/* was already right heavy */
		switch (p->v_right->v_bal) {
		case 1:	/* single rotate */
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal = 0;
		    p->v_bal = 0;
		    break;
		case 0:	/* single rotate */
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal = 1;
		    p->v_bal = -1;
		    break;
		case -1:	/* double rotate */
		    (void) rright(p->v_right);
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal =
			p->v_bal < 1 ? 0 : -1;
		    p->v_right->v_bal =
			p->v_bal > -1 ? 0 : 1;
		    p->v_bal = 0;
		    break;
		default:
		    break;
		}
		break;
	    default:
		break;
	    }
	}
	else {			/* left heavy */
	    switch (p->v_bal) {
	    case 1:		/* was right heavy */
		p->v_bal = 0;
		break;
	    case 0:		/* was balanced */
		p->v_bal = -1;
		break;
	    case -1:		/* was already left heavy */
		switch (p->v_left->v_bal) {
		case -1:	/* single rotate */
		    pp->v_link[ff] = rright(p);
		    p->v_right->v_bal = 0;
		    p->v_bal = 0;
		    break;
		case 0:	/* single rotate */
		    pp->v_link[ff] = rright(p);
		    p->v_right->v_bal = -1;
		    p->v_bal = 1;
		    break;
		case 1:	/* double rotate */
		    (void) rleft(p->v_left);
		    pp->v_link[ff] = rright(p);
		    p->v_left->v_bal =
			p->v_bal < 1 ? 0 : -1;
		    p->v_right->v_bal =
			p->v_bal > -1 ? 0 : 1;
		    p->v_bal = 0;
		    break;
		default:
		    break;
		}
		break;
	    default:
		break;
	    }
	}
	/*
	 * If from insert, then we terminate when p is balanced. If from
	 * delete, then we terminate when p is unbalanced.
	 */
	if ((p->v_bal == 0) ^ d)
	    break;
    }
}