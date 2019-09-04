#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ bspPlane_t ;
struct TYPE_8__ {size_t planeNum; int* children; } ;
typedef  TYPE_2__ bspNode_t ;
struct TYPE_10__ {int cluster; } ;
struct TYPE_9__ {size_t* children; int /*<<< orphan*/  type; int /*<<< orphan*/ * plane; } ;

/* Variables and functions */
 void* AllocTraceNode () ; 
 int /*<<< orphan*/  PlaneTypeForNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_LEAF_SOLID ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* bspLeafs ; 
 TYPE_2__* bspNodes ; 
 TYPE_1__* bspPlanes ; 
 TYPE_3__* traceNodes ; 

__attribute__((used)) static int SetupTraceNodes_r( int bspNodeNum ){
	int i, nodeNum, bspLeafNum;
	bspPlane_t      *plane;
	bspNode_t       *bspNode;


	/* get bsp node and plane */
	bspNode = &bspNodes[ bspNodeNum ];
	plane = &bspPlanes[ bspNode->planeNum ];

	/* allocate a new trace node */
	nodeNum = AllocTraceNode();

	/* setup trace node */
	traceNodes[ nodeNum ].type = PlaneTypeForNormal( plane->normal );
	VectorCopy( plane->normal, traceNodes[ nodeNum ].plane );
	traceNodes[ nodeNum ].plane[ 3 ] = plane->dist;

	/* setup children */
	for ( i = 0; i < 2; i++ )
	{
		/* leafnode */
		if ( bspNode->children[ i ] < 0 ) {
			bspLeafNum = -bspNode->children[ i ] - 1;

			/* new code */
			traceNodes[ nodeNum ].children[ i ] = AllocTraceNode();
			if ( bspLeafs[ bspLeafNum ].cluster == -1 ) {
				traceNodes[ traceNodes[ nodeNum ].children[ i ] ].type = TRACE_LEAF_SOLID;
			}
		}

		/* normal node */
		else{
			traceNodes[ nodeNum ].children[ i ] = SetupTraceNodes_r( bspNode->children[ i ] );
		}
	}

	/* return node number */
	return nodeNum;
}