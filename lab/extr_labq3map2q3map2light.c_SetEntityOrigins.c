#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  entity_t ;
struct TYPE_10__ {int numBSPSurfaces; int firstBSPSurface; } ;
typedef  TYPE_1__ bspModel_t ;
typedef  int /*<<< orphan*/  bspDrawVert_t ;
struct TYPE_11__ {int numVerts; int firstVert; } ;
typedef  TYPE_2__ bspDrawSurface_t ;
struct TYPE_13__ {int /*<<< orphan*/  xyz; } ;
struct TYPE_12__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetVectorForKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (char const*) ; 
 TYPE_2__* bspDrawSurfaces ; 
 TYPE_6__* bspDrawVerts ; 
 TYPE_1__* bspModels ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_6__*,int) ; 
 int numBSPDrawVerts ; 
 int numEntities ; 
 TYPE_3__* safe_malloc (int) ; 
 TYPE_3__* yDrawVerts ; 

void SetEntityOrigins( void ){
	int i, j, k, f;
	entity_t            *e;
	vec3_t origin;
	const char          *key;
	int modelnum;
	bspModel_t          *dm;
	bspDrawSurface_t    *ds;


	/* ydnar: copy drawverts into private storage for nefarious purposes */
	yDrawVerts = safe_malloc( numBSPDrawVerts * sizeof( bspDrawVert_t ) );
	memcpy( yDrawVerts, bspDrawVerts, numBSPDrawVerts * sizeof( bspDrawVert_t ) );

	/* set the entity origins */
	for ( i = 0; i < numEntities; i++ )
	{
		/* get entity and model */
		e = &entities[ i ];
		key = ValueForKey( e, "model" );
		if ( key[ 0 ] != '*' ) {
			continue;
		}
		modelnum = atoi( key + 1 );
		dm = &bspModels[ modelnum ];

		/* get entity origin */
		key = ValueForKey( e, "origin" );
		if ( key[ 0 ] == '\0' ) {
			continue;
		}
		GetVectorForKey( e, "origin", origin );

		/* set origin for all surfaces for this model */
		for ( j = 0; j < dm->numBSPSurfaces; j++ )
		{
			/* get drawsurf */
			ds = &bspDrawSurfaces[ dm->firstBSPSurface + j ];

			/* set its verts */
			for ( k = 0; k < ds->numVerts; k++ )
			{
				f = ds->firstVert + k;
				VectorAdd( origin, bspDrawVerts[ f ].xyz, yDrawVerts[ f ].xyz );
			}
		}
	}
}