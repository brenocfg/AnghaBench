#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {void** edge; int kingpin; void* kingpinLength; void** plane; void* length; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ edge_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,void**,void**) ; 
 void* DotProduct (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (void**,void**) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ fabs (void*) ; 

void CreateEdge( vec4_t plane, vec3_t a, vec3_t b, edge_t *edge ){
	/* copy edge origin */
	VectorCopy( a, edge->origin );

	/* create vector aligned with winding direction of edge */
	VectorSubtract( b, a, edge->edge );

	if ( fabs( edge->edge[ 0 ] ) > fabs( edge->edge[ 1 ] ) && fabs( edge->edge[ 0 ] ) > fabs( edge->edge[ 2 ] ) ) {
		edge->kingpin = 0;
	}
	else if ( fabs( edge->edge[ 1 ] ) > fabs( edge->edge[ 0 ] ) && fabs( edge->edge[ 1 ] ) > fabs( edge->edge[ 2 ] ) ) {
		edge->kingpin = 1;
	}
	else{
		edge->kingpin = 2;
	}
	edge->kingpinLength = edge->edge[ edge->kingpin ];

	VectorNormalize( edge->edge, edge->edge );
	edge->edge[ 3 ] = DotProduct( a, edge->edge );
	edge->length = DotProduct( b, edge->edge ) - edge->edge[ 3 ];

	/* create perpendicular plane that edge lies in */
	CrossProduct( plane, edge->edge, edge->plane );
	edge->plane[ 3 ] = DotProduct( a, edge->plane );
}