#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* children; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_11__ {int arc_flags; TYPE_1__* arc_childp; struct TYPE_11__* arc_childlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int DEADARC ; 
 int DFNDEBUG ; 
 int debug ; 
 scalar_t__ dfn_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  dfn_findcycle (TYPE_1__*) ; 
 scalar_t__ dfn_numbered (TYPE_1__*) ; 
 int /*<<< orphan*/  dfn_post_visit (TYPE_1__*) ; 
 int /*<<< orphan*/  dfn_pre_visit (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 

void
dfn(nltype *parentp)
{
    arctype	*arcp;

#   ifdef DEBUG
	if ( debug & DFNDEBUG ) {
	    printf( "[dfn] dfn(" );
	    printname( parentp );
	    printf( ")\n" );
	}
#   endif /* DEBUG */
	/*
	 *	if we're already numbered, no need to look any further.
	 */
    if ( dfn_numbered( parentp ) ) {
	return;
    }
	/*
	 *	if we're already busy, must be a cycle
	 */
    if ( dfn_busy( parentp ) ) {
	dfn_findcycle( parentp );
	return;
    }
	/*
	 *	visit yourself before your children
	 */
    dfn_pre_visit( parentp );
	/*
	 *	visit children
	 */
    for ( arcp = parentp -> children ; arcp ; arcp = arcp -> arc_childlist ) {
	    if ( arcp -> arc_flags & DEADARC )
		continue;
	    dfn( arcp -> arc_childp );
    }
	/*
	 *	visit yourself after your children
	 */
    dfn_post_visit( parentp );
}