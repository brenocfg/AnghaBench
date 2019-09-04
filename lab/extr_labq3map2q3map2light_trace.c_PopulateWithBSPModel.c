#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tw ;
struct TYPE_27__ {int numVerts; TYPE_1__* v; int /*<<< orphan*/  infoNum; } ;
typedef  TYPE_3__ traceWinding_t ;
struct TYPE_28__ {scalar_t__ surfaceNum; scalar_t__ castShadows; TYPE_2__* si; } ;
typedef  TYPE_4__ traceInfo_t ;
struct TYPE_29__ {scalar_t__ parentSurfaceNum; int /*<<< orphan*/  patchIterations; TYPE_2__* si; scalar_t__ castShadows; } ;
typedef  TYPE_5__ surfaceInfo_t ;
struct TYPE_30__ {int width; int /*<<< orphan*/  height; TYPE_8__* verts; } ;
typedef  TYPE_6__ mesh_t ;
typedef  int /*<<< orphan*/ * m4x4_t ;
struct TYPE_31__ {int numBSPSurfaces; int firstBSPSurface; scalar_t__ firstBSPBrush; } ;
typedef  TYPE_7__ bspModel_t ;
struct TYPE_32__ {int /*<<< orphan*/  st; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_8__ bspDrawVert_t ;
struct TYPE_33__ {int surfaceType; size_t shaderNum; int patchWidth; size_t firstVert; size_t firstIndex; int numIndexes; int /*<<< orphan*/  patchHeight; } ;
typedef  TYPE_9__ bspDrawSurface_t ;
struct TYPE_26__ {int compileFlags; } ;
struct TYPE_25__ {int /*<<< orphan*/  xyz; int /*<<< orphan*/  st; } ;
struct TYPE_24__ {int contentFlags; int surfaceFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddTraceInfo (TYPE_4__*) ; 
 int C_ALPHASHADOW ; 
 int C_LIGHTFILTER ; 
 int C_NODRAW ; 
 int C_SKY ; 
 int C_TRANSLUCENT ; 
 int /*<<< orphan*/  FilterTraceWindingIntoNodes_r (TYPE_3__*,int) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_6__*) ; 
#define  MST_PATCH 130 
#define  MST_PLANAR 129 
#define  MST_TRIANGLE_SOUP 128 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_6__) ; 
 TYPE_6__* RemoveLinearMeshColumnsRows (TYPE_6__*) ; 
 TYPE_6__* SubdivideMesh2 (TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector2Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* bspDrawIndexes ; 
 TYPE_9__* bspDrawSurfaces ; 
 TYPE_8__* bspDrawVerts ; 
 TYPE_12__* bspShaders ; 
 int headNodeNum ; 
 int /*<<< orphan*/  m4x4_transform_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int noDrawContentFlags ; 
 int noDrawSurfaceFlags ; 
 scalar_t__ patchShadows ; 
 scalar_t__ qfalse ; 
 int skyboxNodeNum ; 
 TYPE_5__* surfaceInfos ; 

__attribute__((used)) static void PopulateWithBSPModel( bspModel_t *model, m4x4_t transform ){
	int i, j, x, y, pw[ 5 ], r, nodeNum;
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;
	bspDrawVert_t       *verts;
	int                 *indexes;
	mesh_t srcMesh, *mesh, *subdivided;
	traceInfo_t ti;
	traceWinding_t tw;


	/* dummy check */
	if ( model == NULL || transform == NULL ) {
		return;
	}

	/* walk the list of surfaces in this model and fill out the info structs */
	for ( i = 0; i < model->numBSPSurfaces; i++ )
	{
		/* get surface and info */
		ds = &bspDrawSurfaces[ model->firstBSPSurface + i ];
		info = &surfaceInfos[ model->firstBSPSurface + i ];
		if ( info->si == NULL ) {
			continue;
		}

		/* no shadows */
		if ( !info->castShadows ) {
			continue;
		}

		/* patchshadows? */
		if ( ds->surfaceType == MST_PATCH && patchShadows == qfalse ) {
			continue;
		}

		/* some surfaces in the bsp might have been tagged as nodraw, with a bogus shader */
		if ( ( bspShaders[ ds->shaderNum ].contentFlags & noDrawContentFlags ) ||
			 ( bspShaders[ ds->shaderNum ].surfaceFlags & noDrawSurfaceFlags ) ) {
			continue;
		}

		/* translucent surfaces that are neither alphashadow or lightfilter don't cast shadows */
		if ( ( info->si->compileFlags & C_NODRAW ) ) {
			continue;
		}
		if ( ( info->si->compileFlags & C_TRANSLUCENT ) &&
			 !( info->si->compileFlags & C_ALPHASHADOW ) &&
			 !( info->si->compileFlags & C_LIGHTFILTER ) ) {
			continue;
		}

		/* setup trace info */
		ti.si = info->si;
		ti.castShadows = info->castShadows;
		ti.surfaceNum = model->firstBSPBrush + i;

		/* choose which node (normal or skybox) */
		if ( info->parentSurfaceNum >= 0 ) {
			nodeNum = skyboxNodeNum;

			/* sky surfaces in portal skies are ignored */
			if ( info->si->compileFlags & C_SKY ) {
				continue;
			}
		}
		else{
			nodeNum = headNodeNum;
		}

		/* setup trace winding */
		memset( &tw, 0, sizeof( tw ) );
		tw.infoNum = AddTraceInfo( &ti );
		tw.numVerts = 3;

		/* switch on type */
		switch ( ds->surfaceType )
		{
		/* handle patches */
		case MST_PATCH:
			/* subdivide the surface */
			srcMesh.width = ds->patchWidth;
			srcMesh.height = ds->patchHeight;
			srcMesh.verts = &bspDrawVerts[ ds->firstVert ];
			//%	subdivided = SubdivideMesh( srcMesh, 8, 512 );
			subdivided = SubdivideMesh2( srcMesh, info->patchIterations );

			/* fit it to the curve and remove colinear verts on rows/columns */
			PutMeshOnCurve( *subdivided );
			mesh = RemoveLinearMeshColumnsRows( subdivided );
			FreeMesh( subdivided );

			/* set verts */
			verts = mesh->verts;

			/* subdivide each quad to place the models */
			for ( y = 0; y < ( mesh->height - 1 ); y++ )
			{
				for ( x = 0; x < ( mesh->width - 1 ); x++ )
				{
					/* set indexes */
					pw[ 0 ] = x + ( y * mesh->width );
					pw[ 1 ] = x + ( ( y + 1 ) * mesh->width );
					pw[ 2 ] = x + 1 + ( ( y + 1 ) * mesh->width );
					pw[ 3 ] = x + 1 + ( y * mesh->width );
					pw[ 4 ] = x + ( y * mesh->width );      /* same as pw[ 0 ] */

					/* set radix */
					r = ( x + y ) & 1;

					/* make first triangle */
					VectorCopy( verts[ pw[ r + 0 ] ].xyz, tw.v[ 0 ].xyz );
					Vector2Copy( verts[ pw[ r + 0 ] ].st, tw.v[ 0 ].st );
					VectorCopy( verts[ pw[ r + 1 ] ].xyz, tw.v[ 1 ].xyz );
					Vector2Copy( verts[ pw[ r + 1 ] ].st, tw.v[ 1 ].st );
					VectorCopy( verts[ pw[ r + 2 ] ].xyz, tw.v[ 2 ].xyz );
					Vector2Copy( verts[ pw[ r + 2 ] ].st, tw.v[ 2 ].st );
					m4x4_transform_point( transform, tw.v[ 0 ].xyz );
					m4x4_transform_point( transform, tw.v[ 1 ].xyz );
					m4x4_transform_point( transform, tw.v[ 2 ].xyz );
					FilterTraceWindingIntoNodes_r( &tw, nodeNum );

					/* make second triangle */
					VectorCopy( verts[ pw[ r + 0 ] ].xyz, tw.v[ 0 ].xyz );
					Vector2Copy( verts[ pw[ r + 0 ] ].st, tw.v[ 0 ].st );
					VectorCopy( verts[ pw[ r + 2 ] ].xyz, tw.v[ 1 ].xyz );
					Vector2Copy( verts[ pw[ r + 2 ] ].st, tw.v[ 1 ].st );
					VectorCopy( verts[ pw[ r + 3 ] ].xyz, tw.v[ 2 ].xyz );
					Vector2Copy( verts[ pw[ r + 3 ] ].st, tw.v[ 2 ].st );
					m4x4_transform_point( transform, tw.v[ 0 ].xyz );
					m4x4_transform_point( transform, tw.v[ 1 ].xyz );
					m4x4_transform_point( transform, tw.v[ 2 ].xyz );
					FilterTraceWindingIntoNodes_r( &tw, nodeNum );
				}
			}

			/* free the subdivided mesh */
			FreeMesh( mesh );
			break;

		/* handle triangle surfaces */
		case MST_TRIANGLE_SOUP:
		case MST_PLANAR:
			/* set verts and indexes */
			verts = &bspDrawVerts[ ds->firstVert ];
			indexes = &bspDrawIndexes[ ds->firstIndex ];

			/* walk the triangle list */
			for ( j = 0; j < ds->numIndexes; j += 3 )
			{
				VectorCopy( verts[ indexes[ j ] ].xyz, tw.v[ 0 ].xyz );
				Vector2Copy( verts[ indexes[ j ] ].st, tw.v[ 0 ].st );
				VectorCopy( verts[ indexes[ j + 1 ] ].xyz, tw.v[ 1 ].xyz );
				Vector2Copy( verts[ indexes[ j + 1 ] ].st, tw.v[ 1 ].st );
				VectorCopy( verts[ indexes[ j + 2 ] ].xyz, tw.v[ 2 ].xyz );
				Vector2Copy( verts[ indexes[ j + 2 ] ].st, tw.v[ 2 ].st );
				m4x4_transform_point( transform, tw.v[ 0 ].xyz );
				m4x4_transform_point( transform, tw.v[ 1 ].xyz );
				m4x4_transform_point( transform, tw.v[ 2 ].xyz );
				FilterTraceWindingIntoNodes_r( &tw, nodeNum );
			}
			break;

		/* other surface types do not cast shadows */
		default:
			break;
		}
	}
}