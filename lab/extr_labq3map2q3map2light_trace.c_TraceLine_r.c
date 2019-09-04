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
typedef  float* vec3_t ;
struct TYPE_5__ {scalar_t__ numTestNodes; int* testNodes; scalar_t__ testAll; void* passSolid; int /*<<< orphan*/  hit; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_6__ {int type; scalar_t__ numItems; float* plane; int* children; } ;
typedef  TYPE_2__ traceNode_t ;
typedef  void* qboolean ;

/* Variables and functions */
 float DotProduct (float*,float*) ; 
 scalar_t__ MAX_TRACE_TEST_NODES ; 
#define  PLANE_X 130 
#define  PLANE_Y 129 
#define  PLANE_Z 128 
 int TRACE_LEAF_SOLID ; 
 float TRACE_ON_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_2__* traceNodes ; 

__attribute__((used)) static qboolean TraceLine_r( int nodeNum, vec3_t origin, vec3_t end, trace_t *trace ){
	traceNode_t     *node;
	int side;
	float front, back, frac;
	vec3_t mid;
	qboolean r;


	/* bogus node number means solid, end tracing unless testing all */
	if ( nodeNum < 0 ) {
		VectorCopy( origin, trace->hit );
		trace->passSolid = qtrue;
		return qtrue;
	}

	/* get node */
	node = &traceNodes[ nodeNum ];

	/* solid? */
	if ( node->type == TRACE_LEAF_SOLID ) {
		VectorCopy( origin, trace->hit );
		trace->passSolid = qtrue;
		return qtrue;
	}

	/* leafnode? */
	if ( node->type < 0 ) {
		/* note leaf and return */
		if ( node->numItems > 0 && trace->numTestNodes < MAX_TRACE_TEST_NODES ) {
			trace->testNodes[ trace->numTestNodes++ ] = nodeNum;
		}
		return qfalse;
	}

	/* ydnar 2003-09-07: don't test branches of the bsp with nothing in them when testall is enabled */
	if ( trace->testAll && node->numItems == 0 ) {
		return qfalse;
	}

	/* classify beginning and end points */
	switch ( node->type )
	{
	case PLANE_X:
		front = origin[ 0 ] - node->plane[ 3 ];
		back = end[ 0 ] - node->plane[ 3 ];
		break;

	case PLANE_Y:
		front = origin[ 1 ] - node->plane[ 3 ];
		back = end[ 1 ] - node->plane[ 3 ];
		break;

	case PLANE_Z:
		front = origin[ 2 ] - node->plane[ 3 ];
		back = end[ 2 ] - node->plane[ 3 ];
		break;

	default:
		front = DotProduct( origin, node->plane ) - node->plane[ 3 ];
		back = DotProduct( end, node->plane ) - node->plane[ 3 ];
		break;
	}

	/* entirely in front side? */
	if ( front >= -TRACE_ON_EPSILON && back >= -TRACE_ON_EPSILON ) {
		return TraceLine_r( node->children[ 0 ], origin, end, trace );
	}

	/* entirely on back side? */
	if ( front < TRACE_ON_EPSILON && back < TRACE_ON_EPSILON ) {
		return TraceLine_r( node->children[ 1 ], origin, end, trace );
	}

	/* select side */
	side = front < 0;

	/* calculate intercept point */
	frac = front / ( front - back );
	mid[ 0 ] = origin[ 0 ] + ( end[ 0 ] - origin[ 0 ] ) * frac;
	mid[ 1 ] = origin[ 1 ] + ( end[ 1 ] - origin[ 1 ] ) * frac;
	mid[ 2 ] = origin[ 2 ] + ( end[ 2 ] - origin[ 2 ] ) * frac;

	/* fixme: check inhibit radius, then solid nodes and ignore */

	/* set trace hit here */
	//%	VectorCopy( mid, trace->hit );

	/* trace first side */
	r = TraceLine_r( node->children[ side ], origin, mid, trace );
	if ( r ) {
		return r;
	}

	/* trace other side */
	return TraceLine_r( node->children[ !side ], mid, end, trace );
}