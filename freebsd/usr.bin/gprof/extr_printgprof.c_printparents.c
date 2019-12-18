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
struct TYPE_6__ {scalar_t__ cycleno; int /*<<< orphan*/  npropcall; TYPE_2__* parents; struct TYPE_6__* cyclehead; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_7__ {int arc_flags; double arc_time; double arc_childtime; int /*<<< orphan*/  arc_count; TYPE_1__* arc_parentp; struct TYPE_7__* arc_parentlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int DEADARC ; 
 double hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 int /*<<< orphan*/  sortparents (TYPE_1__*) ; 

void
printparents(nltype *childp)
{
    nltype	*parentp;
    arctype	*arcp;
    nltype	*cycleheadp;

    if ( childp -> cyclehead != 0 ) {
	cycleheadp = childp -> cyclehead;
    } else {
	cycleheadp = childp;
    }
    if ( childp -> parents == 0 ) {
	printf( "%6.6s %5.5s %7.7s %11.11s %7.7s %7.7s     <spontaneous>\n" ,
		"" , "" , "" , "" , "" , "" );
	return;
    }
    sortparents( childp );
    for ( arcp = childp -> parents ; arcp ; arcp = arcp -> arc_parentlist ) {
	parentp = arcp -> arc_parentp;
	if ( childp == parentp || ( arcp -> arc_flags & DEADARC ) ||
	     ( childp->cycleno != 0 && parentp->cycleno == childp->cycleno ) ) {
		/*
		 *	selfcall or call among siblings
		 */
	    printf( "%6.6s %5.5s %7.7s %11.11s %7ld %7.7s     " ,
		    "" , "" , "" , "" ,
		    arcp -> arc_count , "" );
	    printname( parentp );
	    printf( "\n" );
	} else {
		/*
		 *	regular parent of child
		 */
	    printf( "%6.6s %5.5s %7.2f %11.2f %7ld/%-7ld     " ,
		    "" , "" ,
		    arcp -> arc_time / hz , arcp -> arc_childtime / hz ,
		    arcp -> arc_count , cycleheadp -> npropcall );
	    printname( parentp );
	    printf( "\n" );
	}
    }
}