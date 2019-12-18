#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* parents; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_7__ {struct TYPE_7__* arc_parentlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 scalar_t__ GREATERTHAN ; 
 scalar_t__ arccmp (TYPE_2__*,TYPE_2__*) ; 

void
sortparents(nltype *childp)
{
    arctype	*arcp;
    arctype	*detachedp;
    arctype	sorted;
    arctype	*prevp;

	/*
	 *	unlink parents from child,
	 *	then insertion sort back on to sorted's parents.
	 *	    *arcp	the arc you have detached and are inserting.
	 *	    *detachedp	the rest of the arcs to be sorted.
	 *	    sorted	arc list onto which you insertion sort.
	 *	    *prevp	arc before the arc you are comparing.
	 */
    sorted.arc_parentlist = 0;
    for (  (arcp = childp -> parents)&&(detachedp = arcp -> arc_parentlist);
	    arcp ;
	   (arcp = detachedp)&&(detachedp = detachedp -> arc_parentlist)) {
	    /*
	     *	consider *arcp as disconnected
	     *	insert it into sorted
	     */
	for (   prevp = &sorted ;
		prevp -> arc_parentlist ;
		prevp = prevp -> arc_parentlist ) {
	    if ( arccmp( arcp , prevp -> arc_parentlist ) != GREATERTHAN ) {
		break;
	    }
	}
	arcp -> arc_parentlist = prevp -> arc_parentlist;
	prevp -> arc_parentlist = arcp;
    }
	/*
	 *	reattach sorted arcs to child
	 */
    childp -> parents = sorted.arc_parentlist;
}