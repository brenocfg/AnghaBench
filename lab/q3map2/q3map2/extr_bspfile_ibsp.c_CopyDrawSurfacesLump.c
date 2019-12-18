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
typedef  int /*<<< orphan*/  ibspHeader_t ;
struct TYPE_5__ {int lightmapNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  lightmapHeight; int /*<<< orphan*/  lightmapWidth; scalar_t__ lightmapY; scalar_t__ lightmapX; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  firstIndex; int /*<<< orphan*/  numVerts; int /*<<< orphan*/  firstVert; int /*<<< orphan*/  surfaceType; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shaderNum; } ;
typedef  TYPE_1__ ibspDrawSurface_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
struct TYPE_6__ {int* lightmapNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  lightmapHeight; int /*<<< orphan*/  lightmapWidth; scalar_t__* lightmapY; scalar_t__* lightmapX; void** vertexStyles; void** lightmapStyles; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  firstIndex; int /*<<< orphan*/  numVerts; int /*<<< orphan*/  firstVert; int /*<<< orphan*/  surfaceType; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shaderNum; } ;
typedef  TYPE_2__ bspDrawSurface_t ;

/* Variables and functions */
 TYPE_1__* GetLump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLumpElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* LS_NONE ; 
 void* LS_NORMAL ; 
 int /*<<< orphan*/  LUMP_SURFACES ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  SetDrawSurfaces (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bspDrawSurfaces ; 
 int numBSPDrawSurfaces ; 

__attribute__((used)) static void CopyDrawSurfacesLump( ibspHeader_t *header ){
	int i, j;
	ibspDrawSurface_t   *in;
	bspDrawSurface_t    *out;


	/* get count */
	numBSPDrawSurfaces = GetLumpElements( (bspHeader_t*) header, LUMP_SURFACES, sizeof( *in ) );
	SetDrawSurfaces( numBSPDrawSurfaces );

	/* copy */
	in = GetLump( (bspHeader_t*) header, LUMP_SURFACES );
	out = bspDrawSurfaces;
	for ( i = 0; i < numBSPDrawSurfaces; i++ )
	{
		out->shaderNum = in->shaderNum;
		out->fogNum = in->fogNum;
		out->surfaceType = in->surfaceType;
		out->firstVert = in->firstVert;
		out->numVerts = in->numVerts;
		out->firstIndex = in->firstIndex;
		out->numIndexes = in->numIndexes;

		out->lightmapStyles[ 0 ] = LS_NORMAL;
		out->vertexStyles[ 0 ] = LS_NORMAL;
		out->lightmapNum[ 0 ] = in->lightmapNum;
		out->lightmapX[ 0 ] = in->lightmapX;
		out->lightmapY[ 0 ] = in->lightmapY;

		for ( j = 1; j < MAX_LIGHTMAPS; j++ )
		{
			out->lightmapStyles[ j ] = LS_NONE;
			out->vertexStyles[ j ] = LS_NONE;
			out->lightmapNum[ j ] = -3;
			out->lightmapX[ j ] = 0;
			out->lightmapY[ j ] = 0;
		}

		out->lightmapWidth = in->lightmapWidth;
		out->lightmapHeight = in->lightmapHeight;

		VectorCopy( in->lightmapOrigin, out->lightmapOrigin );
		VectorCopy( in->lightmapVecs[ 0 ], out->lightmapVecs[ 0 ] );
		VectorCopy( in->lightmapVecs[ 1 ], out->lightmapVecs[ 1 ] );
		VectorCopy( in->lightmapVecs[ 2 ], out->lightmapVecs[ 2 ] );

		out->patchWidth = in->patchWidth;
		out->patchHeight = in->patchHeight;

		in++;
		out++;
	}
}