#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* cyclehead; struct TYPE_6__* cnext; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_7__ {TYPE_1__* nlentryp; } ;

/* Variables and functions */
 int DFNDEBUG ; 
 int debug ; 
 int dfn_depth ; 
 int /*<<< orphan*/  dfn_self_cycle (TYPE_1__*) ; 
 TYPE_3__* dfn_stack ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

void
dfn_findcycle(nltype *childp)
{
    int		cycletop;
    nltype	*cycleheadp;
    nltype	*tailp;
    int		index;

    for ( cycletop = dfn_depth ; cycletop > 0 ; cycletop -= 1 ) {
	cycleheadp = dfn_stack[ cycletop ].nlentryp;
	if ( childp == cycleheadp ) {
	    break;
	}
	if ( childp -> cyclehead != childp &&
	    childp -> cyclehead == cycleheadp ) {
	    break;
	}
    }
    if ( cycletop <= 0 )
	errx( 1 , "[dfn_findcycle] couldn't find head of cycle" );
#   ifdef DEBUG
	if ( debug & DFNDEBUG ) {
	    printf( "[dfn_findcycle] dfn_depth %d cycletop %d " ,
		    dfn_depth , cycletop  );
	    printname( cycleheadp );
	    printf( "\n" );
	}
#   endif /* DEBUG */
    if ( cycletop == dfn_depth ) {
	    /*
	     *	this is previous function, e.g. this calls itself
	     *	sort of boring
	     */
	dfn_self_cycle( childp );
    } else {
	    /*
	     *	glom intervening functions that aren't already
	     *	glommed into this cycle.
	     *	things have been glommed when their cyclehead field
	     *	points to the head of the cycle they are glommed into.
	     */
	for ( tailp = cycleheadp ; tailp -> cnext ; tailp = tailp -> cnext ) {
	    /* void: chase down to tail of things already glommed */
#	    ifdef DEBUG
		if ( debug & DFNDEBUG ) {
		    printf( "[dfn_findcycle] tail " );
		    printname( tailp );
		    printf( "\n" );
		}
#	    endif /* DEBUG */
	}
	    /*
	     *	if what we think is the top of the cycle
	     *	has a cyclehead field, then it's not really the
	     *	head of the cycle, which is really what we want
	     */
	if ( cycleheadp -> cyclehead != cycleheadp ) {
	    cycleheadp = cycleheadp -> cyclehead;
#	    ifdef DEBUG
		if ( debug & DFNDEBUG ) {
		    printf( "[dfn_findcycle] new cyclehead " );
		    printname( cycleheadp );
		    printf( "\n" );
		}
#	    endif /* DEBUG */
	}
	for ( index = cycletop + 1 ; index <= dfn_depth ; index += 1 ) {
	    childp = dfn_stack[ index ].nlentryp;
	    if ( childp -> cyclehead == childp ) {
		    /*
		     *	not yet glommed anywhere, glom it
		     *	and fix any children it has glommed
		     */
		tailp -> cnext = childp;
		childp -> cyclehead = cycleheadp;
#		ifdef DEBUG
		    if ( debug & DFNDEBUG ) {
			printf( "[dfn_findcycle] glomming " );
			printname( childp );
			printf( " onto " );
			printname( cycleheadp );
			printf( "\n" );
		    }
#		endif /* DEBUG */
		for ( tailp = childp ; tailp->cnext ; tailp = tailp->cnext ) {
		    tailp -> cnext -> cyclehead = cycleheadp;
#		    ifdef DEBUG
			if ( debug & DFNDEBUG ) {
			    printf( "[dfn_findcycle] and its tail " );
			    printname( tailp -> cnext );
			    printf( " onto " );
			    printname( cycleheadp );
			    printf( "\n" );
			}
#		    endif /* DEBUG */
		}
	    } else if ( childp -> cyclehead != cycleheadp /* firewall */ ) {
		fprintf( stderr ,
			"[dfn_busy] glommed, but not to cyclehead\n" );
	    }
	}
    }
}