#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ numVerts; int type; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_12__ {int firstDrawSurf; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_10__ {scalar_t__ forceMeta; scalar_t__ autosprite; } ;

/* Variables and functions */
 int I_FloatTime () ; 
#define  SURFACE_DECAL 133 
#define  SURFACE_FACE 132 
#define  SURFACE_FORCED_META 131 
#define  SURFACE_META 130 
#define  SURFACE_PATCH 129 
#define  SURFACE_TRIANGLES 128 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  StripFaceSurface (TYPE_2__*) ; 
 int /*<<< orphan*/  SurfaceToMetaTriangles (TYPE_2__*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TidyEntitySurfaces (TYPE_3__*) ; 
 int /*<<< orphan*/  TriangulatePatchSurface (TYPE_2__*) ; 
 TYPE_2__* mapDrawSurfs ; 
 scalar_t__ meta ; 
 int numFanSurfaces ; 
 int numMapDrawSurfs ; 
 int numMetaSurfaces ; 
 int numMetaTriangles ; 
 int numMetaVerts ; 
 int numPatchMetaSurfaces ; 
 int numStripSurfaces ; 
 scalar_t__ qfalse ; 

void MakeEntityMetaTriangles( entity_t *e ){
	int i, f, fOld, start;
	mapDrawSurface_t    *ds;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- MakeEntityMetaTriangles ---\n" );

	/* init pacifier */
	fOld = -1;
	start = I_FloatTime();

	/* walk the list of surfaces in the entity */
	for ( i = e->firstDrawSurf; i < numMapDrawSurfs; i++ )
	{
		/* print pacifier */
		f = 10 * ( i - e->firstDrawSurf ) / ( numMapDrawSurfs - e->firstDrawSurf );
		if ( f != fOld ) {
			fOld = f;
			Sys_FPrintf( SYS_VRB, "%d...", f );
		}

		/* get surface */
		ds = &mapDrawSurfs[ i ];
		if ( ds->numVerts <= 0 ) {
			continue;
		}

		/* ignore autosprite surfaces */
		if ( ds->shaderInfo->autosprite ) {
			continue;
		}

		/* meta this surface? */
		if ( meta == qfalse && ds->shaderInfo->forceMeta == qfalse ) {
			continue;
		}

		/* switch on type */
		switch ( ds->type )
		{
		case SURFACE_FACE:
		case SURFACE_DECAL:
			StripFaceSurface( ds );
			SurfaceToMetaTriangles( ds );
			break;

		case SURFACE_PATCH:
			TriangulatePatchSurface( ds );
			break;

		case SURFACE_TRIANGLES:
			break;

		case SURFACE_FORCED_META:
		case SURFACE_META:
			SurfaceToMetaTriangles( ds );
			break;

		default:
			break;
		}
	}

	/* print time */
	if ( ( numMapDrawSurfs - e->firstDrawSurf ) ) {
		Sys_FPrintf( SYS_VRB, " (%d)\n", (int) ( I_FloatTime() - start ) );
	}

	/* emit some stats */
	Sys_FPrintf( SYS_VRB, "%9d total meta surfaces\n", numMetaSurfaces );
	Sys_FPrintf( SYS_VRB, "%9d stripped surfaces\n", numStripSurfaces );
	Sys_FPrintf( SYS_VRB, "%9d fanned surfaces\n", numFanSurfaces );
	Sys_FPrintf( SYS_VRB, "%9d patch meta surfaces\n", numPatchMetaSurfaces );
	Sys_FPrintf( SYS_VRB, "%9d meta verts\n", numMetaVerts );
	Sys_FPrintf( SYS_VRB, "%9d meta triangles\n", numMetaTriangles );

	/* tidy things up */
	TidyEntitySurfaces( e );
}