#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cnext; double time; double childtime; double propfraction; double propself; double propchild; int cycleno; int /*<<< orphan*/  npropcall; scalar_t__ selfcalls; TYPE_2__* parents; struct TYPE_7__* cyclehead; scalar_t__ children; int /*<<< orphan*/  toporder; scalar_t__ index; int /*<<< orphan*/  printflag; scalar_t__ ncall; scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_8__ {scalar_t__ arc_count; TYPE_1__* arc_parentp; struct TYPE_8__* arc_parentlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int CYCLEDEBUG ; 
 int /*<<< orphan*/  DFN_NAN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__* cyclenl ; 
 int debug ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int ncycle ; 
 TYPE_1__* nl ; 
 TYPE_1__* npe ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 

void
cyclelink(void)
{
    register nltype	*nlp;
    register nltype	*cyclenlp;
    int			cycle;
    nltype		*memberp;
    arctype		*arcp;

	/*
	 *	Count the number of cycles, and initialize the cycle lists
	 */
    ncycle = 0;
    for ( nlp = nl ; nlp < npe ; nlp++ ) {
	    /*
	     *	this is how you find unattached cycles
	     */
	if ( nlp -> cyclehead == nlp && nlp -> cnext != 0 ) {
	    ncycle += 1;
	}
    }
	/*
	 *	cyclenl is indexed by cycle number:
	 *	i.e. it is origin 1, not origin 0.
	 */
    cyclenl = (nltype *) calloc( ncycle + 1 , sizeof( nltype ) );
    if ( cyclenl == NULL )
	errx( 1 , "no room for %zu bytes of cycle headers" ,
		   ( ncycle + 1 ) * sizeof( nltype ) );
	/*
	 *	now link cycles to true cycleheads,
	 *	number them, accumulate the data for the cycle
	 */
    cycle = 0;
    for ( nlp = nl ; nlp < npe ; nlp++ ) {
	if ( !( nlp -> cyclehead == nlp && nlp -> cnext != 0 ) ) {
	    continue;
	}
	cycle += 1;
	cyclenlp = &cyclenl[cycle];
        cyclenlp -> name = 0;		/* the name */
        cyclenlp -> value = 0;		/* the pc entry point */
        cyclenlp -> time = 0.0;		/* ticks in this routine */
        cyclenlp -> childtime = 0.0;	/* cumulative ticks in children */
	cyclenlp -> ncall = 0;		/* how many times called */
	cyclenlp -> selfcalls = 0;	/* how many calls to self */
	cyclenlp -> propfraction = 0.0;	/* what % of time propagates */
	cyclenlp -> propself = 0.0;	/* how much self time propagates */
	cyclenlp -> propchild = 0.0;	/* how much child time propagates */
	cyclenlp -> printflag = TRUE;	/* should this be printed? */
	cyclenlp -> index = 0;		/* index in the graph list */
	cyclenlp -> toporder = DFN_NAN;	/* graph call chain top-sort order */
	cyclenlp -> cycleno = cycle;	/* internal number of cycle on */
	cyclenlp -> cyclehead = cyclenlp;	/* pointer to head of cycle */
	cyclenlp -> cnext = nlp;	/* pointer to next member of cycle */
	cyclenlp -> parents = 0;	/* list of caller arcs */
	cyclenlp -> children = 0;	/* list of callee arcs */
#	ifdef DEBUG
	    if ( debug & CYCLEDEBUG ) {
		printf( "[cyclelink] " );
		printname( nlp );
		printf( " is the head of cycle %d\n" , cycle );
	    }
#	endif /* DEBUG */
	    /*
	     *	link members to cycle header
	     */
	for ( memberp = nlp ; memberp ; memberp = memberp -> cnext ) {
	    memberp -> cycleno = cycle;
	    memberp -> cyclehead = cyclenlp;
	}
	    /*
	     *	count calls from outside the cycle
	     *	and those among cycle members
	     */
	for ( memberp = nlp ; memberp ; memberp = memberp -> cnext ) {
	    for ( arcp=memberp->parents ; arcp ; arcp=arcp->arc_parentlist ) {
		if ( arcp -> arc_parentp == memberp ) {
		    continue;
		}
		if ( arcp -> arc_parentp -> cycleno == cycle ) {
		    cyclenlp -> selfcalls += arcp -> arc_count;
		} else {
		    cyclenlp -> npropcall += arcp -> arc_count;
		}
	    }
	}
    }
}