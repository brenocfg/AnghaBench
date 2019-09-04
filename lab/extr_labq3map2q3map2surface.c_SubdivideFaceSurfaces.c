#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  tree_t ;
struct TYPE_15__ {TYPE_3__* shaderInfo; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_16__ {int compileFlags; float subdivisions; } ;
typedef  TYPE_3__ shaderInfo_t ;
struct TYPE_17__ {scalar_t__ type; float* texRange; float* maxs; float* mins; int fogNum; TYPE_1__* sideRef; int /*<<< orphan*/ * mapBrush; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_18__ {int firstDrawSurf; } ;
typedef  TYPE_5__ entity_t ;
typedef  int /*<<< orphan*/  brush_t ;
struct TYPE_14__ {TYPE_2__* side; } ;

/* Variables and functions */
 int C_SKY ; 
 scalar_t__ CalcSurfaceTextureRange (TYPE_4__*) ; 
 int /*<<< orphan*/  ClassifySurfaces (int,TYPE_4__*) ; 
 int /*<<< orphan*/  ClearSurface (TYPE_4__*) ; 
 scalar_t__ SURFACE_FACE ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SubdivideFace_r (TYPE_5__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int,float) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * WindingFromDrawSurf (TYPE_4__*) ; 
 int ceil (float) ; 
 double fabs (float) ; 
 TYPE_4__* mapDrawSurfs ; 
 int numMapDrawSurfs ; 
 scalar_t__ qfalse ; 
 float texRange ; 

void SubdivideFaceSurfaces( entity_t *e, tree_t *tree ){
	int i, j, numBaseDrawSurfs, fogNum;
	mapDrawSurface_t    *ds;
	brush_t             *brush;
	side_t              *side;
	shaderInfo_t        *si;
	winding_t           *w;
	float range, size, subdivisions, s2;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- SubdivideFaceSurfaces ---\n" );

	/* walk the list of surfaces */
	numBaseDrawSurfs = numMapDrawSurfs;
	for ( i = e->firstDrawSurf; i < numBaseDrawSurfs; i++ )
	{
		/* get surface */
		ds = &mapDrawSurfs[ i ];

		/* only subdivide brush sides */
		if ( ds->type != SURFACE_FACE || ds->mapBrush == NULL || ds->sideRef == NULL || ds->sideRef->side == NULL ) {
			continue;
		}

		/* get bits */
		brush = ds->mapBrush;
		side = ds->sideRef->side;

		/* check subdivision for shader */
		si = side->shaderInfo;
		if ( si == NULL ) {
			continue;
		}

		/* ydnar: don't subdivide sky surfaces */
		if ( si->compileFlags & C_SKY ) {
			continue;
		}

		/* do texture coordinate range check */
		ClassifySurfaces( 1, ds );
		if ( CalcSurfaceTextureRange( ds ) == qfalse ) {
			/* calculate subdivisions texture range (this code is shit) */
			range = ( ds->texRange[ 0 ] > ds->texRange[ 1 ] ? ds->texRange[ 0 ] : ds->texRange[ 1 ] );
			size = ds->maxs[ 0 ] - ds->mins[ 0 ];
			for ( j = 1; j < 3; j++ )
				if ( ( ds->maxs[ j ] - ds->mins[ j ] ) > size ) {
					size = ds->maxs[ j ] - ds->mins[ j ];
				}
			subdivisions = ( size / range ) * texRange;
			subdivisions = ceil( subdivisions / 2 ) * 2;
			for ( j = 1; j < 8; j++ )
			{
				s2 = ceil( (float) texRange / j );
				if ( fabs( subdivisions - s2 ) <= 4.0 ) {
					subdivisions = s2;
					break;
				}
			}
		}
		else{
			subdivisions = si->subdivisions;
		}

		/* get subdivisions from shader */
		if ( si->subdivisions > 0 && si->subdivisions < subdivisions ) {
			subdivisions = si->subdivisions;
		}
		if ( subdivisions < 1.0f ) {
			continue;
		}

		/* preserve fog num */
		fogNum = ds->fogNum;

		/* make a winding and free the surface */
		w = WindingFromDrawSurf( ds );
		ClearSurface( ds );

		/* subdivide it */
		SubdivideFace_r( e, brush, side, w, fogNum, subdivisions );
	}
}