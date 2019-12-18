#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceType_t ;
typedef  int srfVert_t ;
struct TYPE_12__ {int numIndexes; int* indexes; int numVerts; int* verts; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_2__ srfBspSurface_t ;
struct TYPE_11__ {int /*<<< orphan*/ * bounds; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {TYPE_8__* shader; TYPE_1__ cullinfo; int /*<<< orphan*/ * data; scalar_t__ fogIndex; } ;
typedef  TYPE_3__ msurface_t ;
typedef  int glIndex_t ;
struct TYPE_14__ {int fogNum; int numVerts; int numIndexes; int firstVert; int firstIndex; int /*<<< orphan*/  shaderNum; } ;
typedef  TYPE_4__ dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;
struct TYPE_18__ {int /*<<< orphan*/  name; int /*<<< orphan*/  isSky; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {int* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_15__ {TYPE_8__* defaultShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  CULLINFO_BOX ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  LIGHTMAP_BY_VERTEX ; 
 int LittleLong (int) ; 
 int /*<<< orphan*/  LoadDrawVertToSrfVert (int*,int /*<<< orphan*/ *,int,float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  R_CalcTangentVectors (int**) ; 
 int /*<<< orphan*/  SF_TRIANGLES ; 
 TYPE_8__* ShaderForShaderNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_7__* r_singleShader ; 
 TYPE_6__ ri ; 
 int* stub1 (int,int /*<<< orphan*/ ) ; 
 int* stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_5__ tr ; 

__attribute__((used)) static void ParseTriSurf( dsurface_t *ds, drawVert_t *verts, float *hdrVertColors, msurface_t *surf, int *indexes ) {
	srfBspSurface_t *cv;
	glIndex_t  *tri;
	int             i, j;
	int             numVerts, numIndexes, badTriangles;

	// get fog volume
	surf->fogIndex = LittleLong( ds->fogNum ) + 1;

	// get shader
	surf->shader = ShaderForShaderNum( ds->shaderNum, LIGHTMAP_BY_VERTEX );
	if ( r_singleShader->integer && !surf->shader->isSky ) {
		surf->shader = tr.defaultShader;
	}

	numVerts = LittleLong(ds->numVerts);
	numIndexes = LittleLong(ds->numIndexes);

	//cv = ri.Hunk_Alloc(sizeof(*cv), h_low);
	cv = (void *)surf->data;
	cv->surfaceType = SF_TRIANGLES;

	cv->numIndexes = numIndexes;
	cv->indexes = ri.Hunk_Alloc(numIndexes * sizeof(cv->indexes[0]), h_low);

	cv->numVerts = numVerts;
	cv->verts = ri.Hunk_Alloc(numVerts * sizeof(cv->verts[0]), h_low);

	surf->data = (surfaceType_t *) cv;

	// copy vertexes
	surf->cullinfo.type = CULLINFO_BOX;
	ClearBounds(surf->cullinfo.bounds[0], surf->cullinfo.bounds[1]);
	verts += LittleLong(ds->firstVert);
	for(i = 0; i < numVerts; i++)
		LoadDrawVertToSrfVert(&cv->verts[i], &verts[i], -1, hdrVertColors ? hdrVertColors + (ds->firstVert + i) * 3 : NULL, surf->cullinfo.bounds);

	// copy triangles
	badTriangles = 0;
	indexes += LittleLong(ds->firstIndex);
	for(i = 0, tri = cv->indexes; i < numIndexes; i += 3, tri += 3)
	{
		for(j = 0; j < 3; j++)
		{
			tri[j] = LittleLong(indexes[i + j]);

			if(tri[j] >= numVerts)
			{
				ri.Error(ERR_DROP, "Bad index in face surface");
			}
		}

		if ((tri[0] == tri[1]) || (tri[1] == tri[2]) || (tri[0] == tri[2]))
		{
			tri -= 3;
			badTriangles++;
		}
	}

	if (badTriangles)
	{
		ri.Printf(PRINT_WARNING, "Trisurf has bad triangles, originally shader %s %d tris %d verts, now %d tris\n", surf->shader->name, numIndexes / 3, numVerts, numIndexes / 3 - badTriangles);
		cv->numIndexes -= badTriangles * 3;
	}

	// Calculate tangent spaces
	{
		srfVert_t      *dv[3];

		for(i = 0, tri = cv->indexes; i < numIndexes; i += 3, tri += 3)
		{
			dv[0] = &cv->verts[tri[0]];
			dv[1] = &cv->verts[tri[1]];
			dv[2] = &cv->verts[tri[2]];

			R_CalcTangentVectors(dv);
		}
	}
}