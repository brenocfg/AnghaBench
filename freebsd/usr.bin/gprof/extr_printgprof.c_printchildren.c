#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cycleno; TYPE_1__* cyclehead; TYPE_3__* children; } ;
typedef  TYPE_2__ nltype ;
struct TYPE_9__ {int arc_flags; double arc_time; double arc_childtime; int /*<<< orphan*/  arc_count; TYPE_2__* arc_childp; struct TYPE_9__* arc_childlist; } ;
typedef  TYPE_3__ arctype ;
struct TYPE_7__ {int /*<<< orphan*/  npropcall; } ;

/* Variables and functions */
 int DEADARC ; 
 double hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_2__*) ; 
 int /*<<< orphan*/  sortchildren (TYPE_2__*) ; 

void
printchildren(nltype *parentp)
{
    nltype	*childp;
    arctype	*arcp;

    sortchildren( parentp );
    arcp = parentp -> children;
    for ( arcp = parentp -> children ; arcp ; arcp = arcp -> arc_childlist ) {
	childp = arcp -> arc_childp;
	if ( childp == parentp || ( arcp -> arc_flags & DEADARC ) ||
	    ( childp->cycleno != 0 && childp->cycleno == parentp->cycleno ) ) {
		/*
		 *	self call or call to sibling
		 */
	    printf( "%6.6s %5.5s %7.7s %11.11s %7ld %7.7s     " ,
		    "" , "" , "" , "" , arcp -> arc_count , "" );
	    printname( childp );
	    printf( "\n" );
	} else {
		/*
		 *	regular child of parent
		 */
	    printf( "%6.6s %5.5s %7.2f %11.2f %7ld/%-7ld     " ,
		    "" , "" ,
		    arcp -> arc_time / hz , arcp -> arc_childtime / hz ,
		    arcp -> arc_count , childp -> cyclehead -> npropcall );
	    printname( childp );
	    printf( "\n" );
	}
    }
}