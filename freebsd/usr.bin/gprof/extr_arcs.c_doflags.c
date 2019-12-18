#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int printflag; double propfraction; int propself; int time; int /*<<< orphan*/  name; struct TYPE_5__* cyclehead; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int /*<<< orphan*/  Elist ; 
 int FALSE ; 
 int /*<<< orphan*/  Fflag ; 
 int /*<<< orphan*/  Flist ; 
 int PROPDEBUG ; 
 int TRUE ; 
 int debug ; 
 int /*<<< orphan*/  elist ; 
 int /*<<< orphan*/  fflag ; 
 int /*<<< orphan*/  flist ; 
 int /*<<< orphan*/  inheritflags (TYPE_1__*) ; 
 int nname ; 
 scalar_t__ onlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 double printtime ; 
 TYPE_1__** topsortnlp ; 

void
doflags(void)
{
    int		index;
    nltype	*childp;
    nltype	*oldhead;

    oldhead = 0;
    for ( index = nname-1 ; index >= 0 ; index -= 1 ) {
	childp = topsortnlp[ index ];
	    /*
	     *	if we haven't done this function or cycle,
	     *	inherit things from parent.
	     *	this way, we are linear in the number of arcs
	     *	since we do all members of a cycle (and the cycle itself)
	     *	as we hit the first member of the cycle.
	     */
	if ( childp -> cyclehead != oldhead ) {
	    oldhead = childp -> cyclehead;
	    inheritflags( childp );
	}
#	ifdef DEBUG
	    if ( debug & PROPDEBUG ) {
		printf( "[doflags] " );
		printname( childp );
		printf( " inherits printflag %d and propfraction %f\n" ,
			childp -> printflag , childp -> propfraction );
	    }
#	endif /* DEBUG */
	if ( ! childp -> printflag ) {
		/*
		 *	printflag is off
		 *	it gets turned on by
		 *	being on -f list,
		 *	or there not being any -f list and not being on -e list.
		 */
	    if (   onlist( flist , childp -> name )
		|| ( !fflag && !onlist( elist , childp -> name ) ) ) {
		childp -> printflag = TRUE;
	    }
	} else {
		/*
		 *	this function has printing parents:
		 *	maybe someone wants to shut it up
		 *	by putting it on -e list.  (but favor -f over -e)
		 */
	    if (  ( !onlist( flist , childp -> name ) )
		&& onlist( elist , childp -> name ) ) {
		childp -> printflag = FALSE;
	    }
	}
	if ( childp -> propfraction == 0.0 ) {
		/*
		 *	no parents to pass time to.
		 *	collect time from children if
		 *	its on -F list,
		 *	or there isn't any -F list and its not on -E list.
		 */
	    if ( onlist( Flist , childp -> name )
		|| ( !Fflag && !onlist( Elist , childp -> name ) ) ) {
		    childp -> propfraction = 1.0;
	    }
	} else {
		/*
		 *	it has parents to pass time to,
		 *	but maybe someone wants to shut it up
		 *	by putting it on -E list.  (but favor -F over -E)
		 */
	    if (  !onlist( Flist , childp -> name )
		&& onlist( Elist , childp -> name ) ) {
		childp -> propfraction = 0.0;
	    }
	}
	childp -> propself = childp -> time * childp -> propfraction;
	printtime += childp -> propself;
#	ifdef DEBUG
	    if ( debug & PROPDEBUG ) {
		printf( "[doflags] " );
		printname( childp );
		printf( " ends up with printflag %d and propfraction %f\n" ,
			childp -> printflag , childp -> propfraction );
		printf( "time %f propself %f printtime %f\n" ,
			childp -> time , childp -> propself , printtime );
	    }
#	endif /* DEBUG */
    }
}