#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int compileFlags; int numTestNodes; float distance; scalar_t__ numSurfaces; size_t* surfaces; size_t* testNodes; int /*<<< orphan*/  end; int /*<<< orphan*/  origin; scalar_t__ testAll; void* opaque; void* passSolid; int /*<<< orphan*/  testOcclusion; int /*<<< orphan*/  recvShadows; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_12__ {size_t infoNum; } ;
typedef  TYPE_2__ traceTriangle_t ;
struct TYPE_13__ {int numItems; size_t* items; } ;
typedef  TYPE_3__ traceNode_t ;
typedef  int /*<<< orphan*/  traceInfo_t ;
struct TYPE_14__ {scalar_t__ childSurfaceNum; } ;

/* Variables and functions */
 int C_SKY ; 
 int MAX_TRACE_TEST_NODES ; 
 int /*<<< orphan*/  TraceLine_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ TraceTriangle (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  headNodeNum ; 
 scalar_t__ noSurfaces ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  skyboxNodeNum ; 
 TYPE_6__* surfaceInfos ; 
 int /*<<< orphan*/ * traceInfos ; 
 TYPE_3__* traceNodes ; 
 TYPE_2__* traceTriangles ; 

void TraceLine( trace_t *trace ){
	int i, j;
	traceNode_t     *node;
	traceTriangle_t *tt;
	traceInfo_t     *ti;


	/* setup output (note: this code assumes the input data is completely filled out) */
	trace->passSolid = qfalse;
	trace->opaque = qfalse;
	trace->compileFlags = 0;
	trace->numTestNodes = 0;

	/* early outs */
	if ( !trace->recvShadows || !trace->testOcclusion || trace->distance <= 0.00001f ) {
		return;
	}

	/* trace through nodes */
	TraceLine_r( headNodeNum, trace->origin, trace->end, trace );
	if ( trace->passSolid && !trace->testAll ) {
		trace->opaque = qtrue;
		return;
	}

	/* skip surfaces? */
	if ( noSurfaces ) {
		return;
	}

	/* testall means trace through sky */
	if ( trace->testAll && trace->numTestNodes < MAX_TRACE_TEST_NODES &&
		 trace->compileFlags & C_SKY &&
		 ( trace->numSurfaces == 0 || surfaceInfos[ trace->surfaces[ 0 ] ].childSurfaceNum < 0 ) ) {
		//%	trace->testNodes[ trace->numTestNodes++ ] = skyboxNodeNum;
		TraceLine_r( skyboxNodeNum, trace->origin, trace->end, trace );
	}

	/* walk node list */
	for ( i = 0; i < trace->numTestNodes; i++ )
	{
		/* get node */
		node = &traceNodes[ trace->testNodes[ i ] ];

		/* walk node item list */
		for ( j = 0; j < node->numItems; j++ )
		{
			tt = &traceTriangles[ node->items[ j ] ];
			ti = &traceInfos[ tt->infoNum ];
			if ( TraceTriangle( ti, tt, trace ) ) {
				return;
			}
			//%	if( TraceWinding( &traceWindings[ node->items[ j ] ], trace ) )
			//%		return;
		}
	}
}