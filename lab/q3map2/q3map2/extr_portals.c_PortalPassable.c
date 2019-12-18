#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_5__ {int compileFlags; TYPE_1__** nodes; int /*<<< orphan*/  onnode; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_4__ {scalar_t__ planenum; scalar_t__ opaque; } ;

/* Variables and functions */
 int C_ANTIPORTAL ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

qboolean PortalPassable( portal_t *p ){
	/* is this to global outside leaf? */
	if ( !p->onnode ) {
		return qfalse;
	}

	/* this should never happen */
	if ( p->nodes[ 0 ]->planenum != PLANENUM_LEAF ||
		 p->nodes[ 1 ]->planenum != PLANENUM_LEAF ) {
		Error( "Portal_EntityFlood: not a leaf" );
	}

	/* ydnar: added antiportal to supress portal generation for visibility blocking */
	if ( p->compileFlags & C_ANTIPORTAL ) {
		return qfalse;
	}

	/* both leaves on either side of the portal must be passable */
	if ( p->nodes[ 0 ]->opaque == qfalse && p->nodes[ 1 ]->opaque == qfalse ) {
		return qtrue;
	}

	/* otherwise this isn't a passable portal */
	return qfalse;
}