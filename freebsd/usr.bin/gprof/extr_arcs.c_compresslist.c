#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; struct TYPE_10__* next; TYPE_4__** list; } ;
typedef  TYPE_3__ cltype ;
struct TYPE_11__ {int arc_cyclecnt; int arc_flags; int arc_count; TYPE_2__* arc_childp; TYPE_1__* arc_parentp; struct TYPE_11__* arc_next; } ;
typedef  TYPE_4__ arctype ;
struct TYPE_9__ {int flags; int parentcnt; char* name; int /*<<< orphan*/  npropcall; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 int BREAKCYCLE ; 
 int DEADARC ; 
 int HASCYCLEXIT ; 
 int ONLIST ; 
 TYPE_4__* archead ; 
 int /*<<< orphan*/  cyclecnt ; 
 TYPE_3__* cyclehead ; 
 int debug ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,...) ; 

void
compresslist(void)
{
    cltype	*clp;
    cltype	**prev;
    arctype	**arcpp;
    arctype	**endlist;
    arctype	*arcp;
    arctype	*maxarcp;
    arctype	*maxexitarcp;
    arctype	*maxwithparentarcp;
    arctype	*maxnoparentarcp;
    int		maxexitcnt;
    int		maxwithparentcnt;
    int		maxnoparentcnt;
#   ifdef DEBUG
	const char	*type;
#   endif /* DEBUG */

    maxexitcnt = 0;
    maxwithparentcnt = 0;
    maxnoparentcnt = 0;
    for ( endlist = &archead , arcp = archead ; arcp ; ) {
	if ( arcp -> arc_cyclecnt == 0 ) {
	    arcp -> arc_flags &= ~ONLIST;
	    *endlist = arcp -> arc_next;
	    arcp -> arc_next = 0;
	    arcp = *endlist;
	    continue;
	}
	if ( arcp -> arc_childp -> flags & HASCYCLEXIT ) {
	    if ( arcp -> arc_cyclecnt > maxexitcnt ||
		( arcp -> arc_cyclecnt == maxexitcnt &&
		arcp -> arc_cyclecnt < maxexitarcp -> arc_count ) ) {
		maxexitcnt = arcp -> arc_cyclecnt;
		maxexitarcp = arcp;
	    }
	} else if ( arcp -> arc_childp -> parentcnt > 1 ) {
	    if ( arcp -> arc_cyclecnt > maxwithparentcnt ||
		( arcp -> arc_cyclecnt == maxwithparentcnt &&
		arcp -> arc_cyclecnt < maxwithparentarcp -> arc_count ) ) {
		maxwithparentcnt = arcp -> arc_cyclecnt;
		maxwithparentarcp = arcp;
	    }
	} else {
	    if ( arcp -> arc_cyclecnt > maxnoparentcnt ||
		( arcp -> arc_cyclecnt == maxnoparentcnt &&
		arcp -> arc_cyclecnt < maxnoparentarcp -> arc_count ) ) {
		maxnoparentcnt = arcp -> arc_cyclecnt;
		maxnoparentarcp = arcp;
	    }
	}
	endlist = &arcp -> arc_next;
	arcp = arcp -> arc_next;
    }
    if ( maxexitcnt > 0 ) {
	/*
	 *	first choice is edge leading to node with out-of-cycle parent
	 */
	maxarcp = maxexitarcp;
#	ifdef DEBUG
	    type = "exit";
#	endif /* DEBUG */
    } else if ( maxwithparentcnt > 0 ) {
	/*
	 *	second choice is edge leading to node with at least one
	 *	other in-cycle parent
	 */
	maxarcp = maxwithparentarcp;
#	ifdef DEBUG
	    type = "internal";
#	endif /* DEBUG */
    } else {
	/*
	 *	last choice is edge leading to node with only this arc as
	 *	a parent (as it will now be orphaned)
	 */
	maxarcp = maxnoparentarcp;
#	ifdef DEBUG
	    type = "orphan";
#	endif /* DEBUG */
    }
    maxarcp -> arc_flags |= DEADARC;
    maxarcp -> arc_childp -> parentcnt -= 1;
    maxarcp -> arc_childp -> npropcall -= maxarcp -> arc_count;
#   ifdef DEBUG
	if ( debug & BREAKCYCLE ) {
	    printf( "%s delete %s arc: %s (%ld) -> %s from %u cycle(s)\n" ,
		"[compresslist]" , type , maxarcp -> arc_parentp -> name ,
		maxarcp -> arc_count , maxarcp -> arc_childp -> name ,
		maxarcp -> arc_cyclecnt );
	}
#   endif /* DEBUG */
    printf( "\t%s to %s with %ld calls\n" , maxarcp -> arc_parentp -> name ,
	maxarcp -> arc_childp -> name , maxarcp -> arc_count );
    prev = &cyclehead;
    for ( clp = cyclehead ; clp ; ) {
	endlist = &clp -> list[ clp -> size ];
	for ( arcpp = clp -> list ; arcpp < endlist ; arcpp++ )
	    if ( (*arcpp) -> arc_flags & DEADARC )
		break;
	if ( arcpp == endlist ) {
	    prev = &clp -> next;
	    clp = clp -> next;
	    continue;
	}
	for ( arcpp = clp -> list ; arcpp < endlist ; arcpp++ )
	    (*arcpp) -> arc_cyclecnt--;
	cyclecnt--;
	*prev = clp -> next;
	clp = clp -> next;
	free( clp );
    }
}