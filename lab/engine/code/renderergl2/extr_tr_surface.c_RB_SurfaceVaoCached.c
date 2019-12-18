#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srfVert_t ;
typedef  void* qboolean ;
typedef  int /*<<< orphan*/  glIndex_t ;
struct TYPE_5__ {int /*<<< orphan*/  isPortal; int /*<<< orphan*/  isSky; } ;
struct TYPE_4__ {int dlightBits; int pshadowBits; int numIndexes; void* useCacheVao; void* useInternalVao; scalar_t__ numVertexes; int /*<<< orphan*/  cubemapIndex; int /*<<< orphan*/  fogNum; TYPE_2__* shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_BeginSurface (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  ShaderRequiresCPUDeforms (TYPE_2__*) ; 
 int /*<<< orphan*/  VaoCache_AddSurface (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VaoCache_BindVao () ; 
 int /*<<< orphan*/  VaoCache_CheckAdd (void**,void**,void**,int,int) ; 
 int /*<<< orphan*/  VaoCache_InitQueue () ; 
 int /*<<< orphan*/  VaoCache_RecycleIndexBuffer () ; 
 int /*<<< orphan*/  VaoCache_RecycleVertexBuffer () ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_1__ tess ; 

__attribute__((used)) static qboolean RB_SurfaceVaoCached(int numVerts, srfVert_t *verts, int numIndexes, glIndex_t *indexes, int dlightBits, int pshadowBits)
{
	qboolean recycleVertexBuffer = qfalse;
	qboolean recycleIndexBuffer = qfalse;
	qboolean endSurface = qfalse;

	if (!(!ShaderRequiresCPUDeforms(tess.shader) && !tess.shader->isSky && !tess.shader->isPortal))
		return qfalse;

	if (!numIndexes || !numVerts)
		return qfalse;

	VaoCache_BindVao();

	tess.dlightBits |= dlightBits;
	tess.pshadowBits |= pshadowBits;

	VaoCache_CheckAdd(&endSurface, &recycleVertexBuffer, &recycleIndexBuffer, numVerts, numIndexes);

	if (endSurface)
	{
		RB_EndSurface();
		RB_BeginSurface(tess.shader, tess.fogNum, tess.cubemapIndex);
	}

	if (recycleVertexBuffer)
		VaoCache_RecycleVertexBuffer();

	if (recycleIndexBuffer)
		VaoCache_RecycleIndexBuffer();

	if (!tess.numVertexes)
		VaoCache_InitQueue();

	VaoCache_AddSurface(verts, numVerts, indexes, numIndexes);

	tess.numIndexes += numIndexes;
	tess.numVertexes += numVerts;
	tess.useInternalVao = qfalse;
	tess.useCacheVao = qtrue;

	return qtrue;
}