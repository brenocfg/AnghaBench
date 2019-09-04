#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srfVert_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  glIndex_t ;
struct TYPE_6__ {scalar_t__ vertexOffset; scalar_t__ indexOffset; scalar_t__ numSurfaces; scalar_t__ numBatches; TYPE_1__* vao; } ;
struct TYPE_5__ {int vertexCommitSize; int indexCommitSize; scalar_t__ numSurfaces; } ;
struct TYPE_4__ {scalar_t__ vertexesSize; scalar_t__ indexesSize; } ;

/* Variables and functions */
 scalar_t__ VAOCACHE_MAX_BATCHES ; 
 scalar_t__ VAOCACHE_MAX_SURFACES ; 
 int VAOCACHE_QUEUE_MAX_INDEXES ; 
 scalar_t__ VAOCACHE_QUEUE_MAX_SURFACES ; 
 int VAOCACHE_QUEUE_MAX_VERTEXES ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ vc ; 
 TYPE_2__ vcq ; 

void VaoCache_CheckAdd(qboolean *endSurface, qboolean *recycleVertexBuffer, qboolean *recycleIndexBuffer, int numVerts, int numIndexes)
{
	int vertexesSize = sizeof(srfVert_t) * numVerts;
	int indexesSize = sizeof(glIndex_t) * numIndexes;

	if (vc.vao->vertexesSize < vc.vertexOffset + vcq.vertexCommitSize + vertexesSize)
	{
		//ri.Printf(PRINT_ALL, "out of space in vertex cache: %d < %d + %d + %d\n", vc.vao->vertexesSize, vc.vertexOffset, vcq.vertexCommitSize, vertexesSize);
		*recycleVertexBuffer = qtrue;
		*recycleIndexBuffer = qtrue;
		*endSurface = qtrue;
	}

	if (vc.vao->indexesSize < vc.indexOffset + vcq.indexCommitSize + indexesSize)
	{
		//ri.Printf(PRINT_ALL, "out of space in index cache\n");
		*recycleIndexBuffer = qtrue;
		*endSurface = qtrue;
	}

	if (vc.numSurfaces + vcq.numSurfaces >= VAOCACHE_MAX_SURFACES)
	{
		//ri.Printf(PRINT_ALL, "out of surfaces in index cache\n");
		*recycleIndexBuffer = qtrue;
		*endSurface = qtrue;
	}

	if (vc.numBatches >= VAOCACHE_MAX_BATCHES)
	{
		//ri.Printf(PRINT_ALL, "out of batches in index cache\n");
		*recycleIndexBuffer = qtrue;
		*endSurface = qtrue;
	}

	if (vcq.numSurfaces >= VAOCACHE_QUEUE_MAX_SURFACES)
	{
		//ri.Printf(PRINT_ALL, "out of queued surfaces\n");
		*endSurface = qtrue;
	}

	if (VAOCACHE_QUEUE_MAX_VERTEXES * sizeof(srfVert_t) < vcq.vertexCommitSize + vertexesSize)
	{
		//ri.Printf(PRINT_ALL, "out of queued vertexes\n");
		*endSurface = qtrue;
	}

	if (VAOCACHE_QUEUE_MAX_INDEXES * sizeof(glIndex_t) < vcq.indexCommitSize + indexesSize)
	{
		//ri.Printf(PRINT_ALL, "out of queued indexes\n");
		*endSurface = qtrue;
	}
}