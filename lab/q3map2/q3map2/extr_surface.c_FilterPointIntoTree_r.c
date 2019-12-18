#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_7__ {size_t planenum; struct TYPE_7__** children; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  mapDrawSurface_t ;

/* Variables and functions */
 int AddReferenceToLeaf (int /*<<< orphan*/ *,TYPE_2__*) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float ON_EPSILON ; 
 size_t PLANENUM_LEAF ; 
 TYPE_1__* mapplanes ; 

int FilterPointIntoTree_r( vec3_t point, mapDrawSurface_t *ds, node_t *node ){
	float d;
	plane_t         *plane;
	int refs = 0;


	/* is this a decision node? */
	if ( node->planenum != PLANENUM_LEAF ) {
		/* classify the point in relation to the plane */
		plane = &mapplanes[ node->planenum ];
		d = DotProduct( point, plane->normal ) - plane->dist;

		/* filter by this plane */
		refs = 0;
		if ( d >= -ON_EPSILON ) {
			refs += FilterPointIntoTree_r( point, ds, node->children[ 0 ] );
		}
		if ( d <= ON_EPSILON ) {
			refs += FilterPointIntoTree_r( point, ds, node->children[ 1 ] );
		}

		/* return */
		return refs;
	}

	/* add a reference */
	return AddReferenceToLeaf( ds, node );
}