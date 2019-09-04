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
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_6__ {size_t planenum; struct TYPE_6__* parent; struct TYPE_6__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_WINDING_EPSILON ; 
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mapplanes ; 
 int /*<<< orphan*/  vec3_origin ; 

winding_t   *BaseWindingForNode( node_t *node ){
	winding_t   *w;
	node_t      *n;
	plane_t     *plane;
	vec3_t normal;
	vec_t dist;

	w = BaseWindingForPlane( mapplanes[node->planenum].normal
							 , mapplanes[node->planenum].dist );

	// clip by all the parents
	for ( n = node->parent ; n && w ; )
	{
		plane = &mapplanes[n->planenum];

		if ( n->children[0] == node ) { // take front
			ChopWindingInPlace( &w, plane->normal, plane->dist, BASE_WINDING_EPSILON );
		}
		else
		{   // take back
			VectorSubtract( vec3_origin, plane->normal, normal );
			dist = -plane->dist;
			ChopWindingInPlace( &w, normal, dist, BASE_WINDING_EPSILON );
		}
		node = n;
		n = n->parent;
	}

	return w;
}