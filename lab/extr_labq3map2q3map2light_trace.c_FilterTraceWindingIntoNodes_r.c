#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec4_t ;
struct TYPE_12__ {int numVerts; int /*<<< orphan*/  plane; TYPE_1__* v; } ;
typedef  TYPE_2__ traceWinding_t ;
struct TYPE_13__ {scalar_t__ type; int* children; int /*<<< orphan*/  plane; } ;
typedef  TYPE_3__ traceNode_t ;
struct TYPE_11__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddItemToTraceNode (TYPE_3__*,int) ; 
 int AddTraceWinding (TYPE_2__*) ; 
 int /*<<< orphan*/  ClipTraceWinding (TYPE_2__*,scalar_t__*,TYPE_2__*,TYPE_2__*) ; 
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 int /*<<< orphan*/  PlaneFromPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector4Copy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 float fabs (scalar_t__) ; 
 int headNodeNum ; 
 int numTraceNodes ; 
 TYPE_3__* traceNodes ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void FilterTraceWindingIntoNodes_r( traceWinding_t *tw, int nodeNum ){
	int num;
	vec4_t plane1, plane2, reverse;
	traceNode_t     *node;
	traceWinding_t front, back;


	/* don't filter if passed a bogus node (solid, etc) */
	if ( nodeNum < 0 || nodeNum >= numTraceNodes ) {
		return;
	}

	/* get node */
	node = &traceNodes[ nodeNum ];

	/* is this a decision node? */
	if ( node->type >= 0 ) {
		/* create winding plane if necessary, filtering out bogus windings as well */
		if ( nodeNum == headNodeNum ) {
			if ( !PlaneFromPoints( tw->plane, tw->v[ 0 ].xyz, tw->v[ 1 ].xyz, tw->v[ 2 ].xyz ) ) {
				return;
			}
		}

		/* validate the node */
		if ( node->children[ 0 ] == 0 || node->children[ 1 ] == 0 ) {
			Error( "Invalid tracenode: %d", nodeNum );
		}

		/* get node plane */
		Vector4Copy( node->plane, plane1 );

		/* get winding plane */
		Vector4Copy( tw->plane, plane2 );

		/* invert surface plane */
		VectorSubtract( vec3_origin, plane2, reverse );
		reverse[ 3 ] = -plane2[ 3 ];

		/* front only */
		if ( DotProduct( plane1, plane2 ) > 0.999f && fabs( plane1[ 3 ] - plane2[ 3 ] ) < 0.001f ) {
			FilterTraceWindingIntoNodes_r( tw, node->children[ 0 ] );
			return;
		}

		/* back only */
		if ( DotProduct( plane1, reverse ) > 0.999f && fabs( plane1[ 3 ] - reverse[ 3 ] ) < 0.001f ) {
			FilterTraceWindingIntoNodes_r( tw, node->children[ 1 ] );
			return;
		}

		/* clip the winding by node plane */
		ClipTraceWinding( tw, plane1, &front, &back );

		/* filter by node plane */
		if ( front.numVerts >= 3 ) {
			FilterTraceWindingIntoNodes_r( &front, node->children[ 0 ] );
		}
		if ( back.numVerts >= 3 ) {
			FilterTraceWindingIntoNodes_r( &back, node->children[ 1 ] );
		}

		/* return to caller */
		return;
	}

	/* add winding to leaf node */
	num = AddTraceWinding( tw );
	AddItemToTraceNode( node, num );
}