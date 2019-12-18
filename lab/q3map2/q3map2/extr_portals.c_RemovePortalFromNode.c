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
struct TYPE_5__ {TYPE_2__** nodes; struct TYPE_5__** next; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_6__ {TYPE_1__* portals; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 

void RemovePortalFromNode( portal_t *portal, node_t *l ){
	portal_t    **pp, *t;

// remove reference to the current portal
	pp = &l->portals;
	while ( 1 )
	{
		t = *pp;
		if ( !t ) {
			Error( "RemovePortalFromNode: portal not in leaf" );
		}

		if ( t == portal ) {
			break;
		}

		if ( t->nodes[0] == l ) {
			pp = &t->next[0];
		}
		else if ( t->nodes[1] == l ) {
			pp = &t->next[1];
		}
		else{
			Error( "RemovePortalFromNode: portal not bounding leaf" );
		}
	}

	if ( portal->nodes[0] == l ) {
		*pp = portal->next[0];
		portal->nodes[0] = NULL;
	}
	else if ( portal->nodes[1] == l ) {
		*pp = portal->next[1];
		portal->nodes[1] = NULL;
	}
}