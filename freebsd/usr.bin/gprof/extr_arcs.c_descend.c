#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cycleno; int flags; TYPE_2__* children; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_9__ {int arc_flags; TYPE_1__* arc_childp; struct TYPE_9__* arc_childlist; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int CYCLEHEAD ; 
 int DEADARC ; 
 int FALSE ; 
 int TRUE ; 
 int VISITED ; 
 int addcycle (TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  viable ; 
 int /*<<< orphan*/  visited ; 

bool
descend(nltype *node, arctype **stkstart, arctype **stkp)
{
    arctype	*arcp;
    bool	ret;

    for ( arcp = node -> children ; arcp ; arcp = arcp -> arc_childlist ) {
#	ifdef DEBUG
	    visited++;
#	endif /* DEBUG */
	if ( arcp -> arc_childp -> cycleno != node -> cycleno
	    || ( arcp -> arc_childp -> flags & VISITED )
	    || ( arcp -> arc_flags & DEADARC ) )
	    continue;
#	ifdef DEBUG
	    viable++;
#	endif /* DEBUG */
	*stkp = arcp;
	if ( arcp -> arc_childp -> flags & CYCLEHEAD ) {
	    if ( addcycle( stkstart , stkp ) == FALSE )
		return( FALSE );
	    continue;
	}
	arcp -> arc_childp -> flags |= VISITED;
	ret = descend( arcp -> arc_childp , stkstart , stkp + 1 );
	arcp -> arc_childp -> flags &= ~VISITED;
	if ( ret == FALSE )
	    return( FALSE );
    }
    return( TRUE );
}