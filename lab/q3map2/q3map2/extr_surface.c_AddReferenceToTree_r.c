#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_9__ {scalar_t__ planenum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  sky; struct TYPE_9__** children; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_10__ {int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_8__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AddReferenceToLeaf (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ PLANENUM_LEAF ; 

int AddReferenceToTree_r( mapDrawSurface_t *ds, node_t *node, qboolean skybox ){
	int i, refs = 0;


	/* dummy check */
	if ( node == NULL ) {
		return 0;
	}

	/* is this a decision node? */
	if ( node->planenum != PLANENUM_LEAF ) {
		/* add to child nodes and return */
		refs += AddReferenceToTree_r( ds, node->children[ 0 ], skybox );
		refs += AddReferenceToTree_r( ds, node->children[ 1 ], skybox );
		return refs;
	}

	/* ydnar */
	if ( skybox ) {
		/* skybox surfaces only get added to sky leaves */
		if ( !node->sky ) {
			return 0;
		}

		/* increase the leaf bounds */
		for ( i = 0; i < ds->numVerts; i++ )
			AddPointToBounds( ds->verts[ i ].xyz, node->mins, node->maxs );
	}

	/* add a reference */
	return AddReferenceToLeaf( ds, node );
}