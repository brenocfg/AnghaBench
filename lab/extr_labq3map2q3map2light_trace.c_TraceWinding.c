#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_7__ {size_t infoNum; int numVerts; TYPE_1__* v; } ;
typedef  TYPE_2__ traceWinding_t ;
struct TYPE_8__ {size_t infoNum; int /*<<< orphan*/  edge2; TYPE_1__* v; int /*<<< orphan*/  edge1; } ;
typedef  TYPE_3__ traceTriangle_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 scalar_t__ TraceTriangle (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/ * traceInfos ; 

qboolean TraceWinding( traceWinding_t *tw, trace_t *trace ){
	int i;
	traceTriangle_t tt;


	/* initial setup */
	tt.infoNum = tw->infoNum;
	tt.v[ 0 ] = tw->v[ 0 ];

	/* walk vertex list */
	for ( i = 1; i + 1 < tw->numVerts; i++ )
	{
		/* set verts */
		tt.v[ 1 ] = tw->v[ i ];
		tt.v[ 2 ] = tw->v[ i + 1 ];

		/* find vectors for two edges sharing the first vert */
		VectorSubtract( tt.v[ 1 ].xyz, tt.v[ 0 ].xyz, tt.edge1 );
		VectorSubtract( tt.v[ 2 ].xyz, tt.v[ 0 ].xyz, tt.edge2 );

		/* trace it */
		if ( TraceTriangle( &traceInfos[ tt.infoNum ], &tt, trace ) ) {
			return qtrue;
		}
	}

	/* done */
	return qfalse;
}