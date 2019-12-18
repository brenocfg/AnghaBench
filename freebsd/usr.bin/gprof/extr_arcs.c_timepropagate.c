#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double propfraction; scalar_t__ cycleno; scalar_t__ toporder; scalar_t__ npropcall; double time; double childtime; double propchild; struct TYPE_5__* cyclehead; TYPE_2__* children; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_6__ {int arc_flags; scalar_t__ arc_count; double arc_time; double arc_childtime; TYPE_1__* arc_childp; struct TYPE_6__* arc_childlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int DEADARC ; 
 int PROPDEBUG ; 
 int debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

void
timepropagate(nltype *parentp)
{
    arctype	*arcp;
    nltype	*childp;
    double	share;
    double	propshare;

    if ( parentp -> propfraction == 0.0 ) {
	return;
    }
	/*
	 *	gather time from children of this parent.
	 */
    for ( arcp = parentp -> children ; arcp ; arcp = arcp -> arc_childlist ) {
	childp = arcp -> arc_childp;
	if ( arcp -> arc_flags & DEADARC ) {
	    continue;
	}
	if ( arcp -> arc_count == 0 ) {
	    continue;
	}
	if ( childp == parentp ) {
	    continue;
	}
	if ( childp -> propfraction == 0.0 ) {
	    continue;
	}
	if ( childp -> cyclehead != childp ) {
	    if ( parentp -> cycleno == childp -> cycleno ) {
		continue;
	    }
	    if ( parentp -> toporder <= childp -> toporder ) {
		fprintf( stderr , "[propagate] toporder botches\n" );
	    }
	    childp = childp -> cyclehead;
	} else {
	    if ( parentp -> toporder <= childp -> toporder ) {
		fprintf( stderr , "[propagate] toporder botches\n" );
		continue;
	    }
	}
	if ( childp -> npropcall == 0 ) {
	    continue;
	}
	    /*
	     *	distribute time for this arc
	     */
	arcp -> arc_time = childp -> time
			        * ( ( (double) arcp -> arc_count ) /
				    ( (double) childp -> npropcall ) );
	arcp -> arc_childtime = childp -> childtime
			        * ( ( (double) arcp -> arc_count ) /
				    ( (double) childp -> npropcall ) );
	share = arcp -> arc_time + arcp -> arc_childtime;
	parentp -> childtime += share;
	    /*
	     *	( 1 - propfraction ) gets lost along the way
	     */
	propshare = parentp -> propfraction * share;
	    /*
	     *	fix things for printing
	     */
	parentp -> propchild += propshare;
	arcp -> arc_time *= parentp -> propfraction;
	arcp -> arc_childtime *= parentp -> propfraction;
	    /*
	     *	add this share to the parent's cycle header, if any.
	     */
	if ( parentp -> cyclehead != parentp ) {
	    parentp -> cyclehead -> childtime += share;
	    parentp -> cyclehead -> propchild += propshare;
	}
#	ifdef DEBUG
	    if ( debug & PROPDEBUG ) {
		printf( "[dotime] child \t" );
		printname( childp );
		printf( " with %f %f %ld/%ld\n" ,
			childp -> time , childp -> childtime ,
			arcp -> arc_count , childp -> npropcall );
		printf( "[dotime] parent\t" );
		printname( parentp );
		printf( "\n[dotime] share %f\n" , share );
	    }
#	endif /* DEBUG */
    }
}