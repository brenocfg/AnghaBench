#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_15__ {struct TYPE_15__* next; int /*<<< orphan*/  shaderInfo; int /*<<< orphan*/  mesh; int /*<<< orphan*/  longestCurve; int /*<<< orphan*/  eMaxs; int /*<<< orphan*/  eMins; } ;
typedef  TYPE_1__ parseMesh_t ;
struct TYPE_16__ {int width; int height; TYPE_4__* verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_17__ {TYPE_1__* patches; int /*<<< orphan*/  origin; int /*<<< orphan*/ * epairs; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_18__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_4__ bspDrawVert_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,float*) ; 
 TYPE_3__* FindTargetEntity (char const*) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_2__*) ; 
 int IterationsForCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDecalProjector (int /*<<< orphan*/ ,float*,float,int,TYPE_4__**) ; 
 scalar_t__ PLANAR_EPSILON ; 
 scalar_t__ PlaneFromPoints (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_2__) ; 
 scalar_t__ Q_stricmp (char const*,char*) ; 
 TYPE_2__* RemoveLinearMeshColumnsRows (TYPE_2__*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 TYPE_2__* SubdivideMesh2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 char* ValueForKey (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorNormalize (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* entities ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int numEntities ; 
 int /*<<< orphan*/  numProjectors ; 
 int /*<<< orphan*/  patchSubdivisions ; 
 int /*<<< orphan*/  vec3_origin ; 

void ProcessDecals( void ){
	int i, j, x, y, pw[ 5 ], r, iterations;
	float distance;
	vec4_t projection, plane;
	vec3_t origin, target, delta;
	entity_t            *e, *e2;
	parseMesh_t         *p;
	mesh_t              *mesh, *subdivided;
	bspDrawVert_t       *dv[ 4 ];
	const char          *value;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- ProcessDecals ---\n" );

	/* walk entity list */
	for ( i = 0; i < numEntities; i++ )
	{
		/* get entity */
		e = &entities[ i ];
		value = ValueForKey( e, "classname" );
		if ( Q_stricmp( value, "_decal" ) ) {
			continue;
		}

		/* any patches? */
		if ( e->patches == NULL ) {
			Sys_FPrintf( SYS_WRN, "WARNING: Decal entity without any patch meshes, ignoring.\n" );
			e->epairs = NULL;   /* fixme: leak! */
			continue;
		}

		/* find target */
		value = ValueForKey( e, "target" );
		e2 = FindTargetEntity( value );

		/* no target? */
		if ( e2 == NULL ) {
			Sys_FPrintf( SYS_WRN, "WARNING: Decal entity without a valid target, ignoring.\n" );
			continue;
		}

		/* walk entity patches */
		for ( p = e->patches; p != NULL; p = e->patches )
		{
			/* setup projector */
			if ( VectorCompare( e->origin, vec3_origin ) ) {
				VectorAdd( p->eMins, p->eMaxs, origin );
				VectorScale( origin, 0.5f, origin );
			}
			else{
				VectorCopy( e->origin, origin );
			}

			VectorCopy( e2->origin, target );
			VectorSubtract( target, origin, delta );

			/* setup projection plane */
			distance = VectorNormalize( delta, projection );
			projection[ 3 ] = DotProduct( origin, projection );

			/* create projectors */
			if ( distance > 0.125f ) {
				/* tesselate the patch */
				iterations = IterationsForCurve( p->longestCurve, patchSubdivisions );
				subdivided = SubdivideMesh2( p->mesh, iterations );

				/* fit it to the curve and remove colinear verts on rows/columns */
				PutMeshOnCurve( *subdivided );
				mesh = RemoveLinearMeshColumnsRows( subdivided );
				FreeMesh( subdivided );

				/* offset by projector origin */
				for ( j = 0; j < ( mesh->width * mesh->height ); j++ )
					VectorAdd( mesh->verts[ j ].xyz, e->origin, mesh->verts[ j ].xyz );

				/* iterate through the mesh quads */
				for ( y = 0; y < ( mesh->height - 1 ); y++ )
				{
					for ( x = 0; x < ( mesh->width - 1 ); x++ )
					{
						/* set indexes */
						pw[ 0 ] = x + ( y * mesh->width );
						pw[ 1 ] = x + ( ( y + 1 ) * mesh->width );
						pw[ 2 ] = x + 1 + ( ( y + 1 ) * mesh->width );
						pw[ 3 ] = x + 1 + ( y * mesh->width );
						pw[ 4 ] = x + ( y * mesh->width );    /* same as pw[ 0 ] */

						/* set radix */
						r = ( x + y ) & 1;

						/* get drawverts */
						dv[ 0 ] = &mesh->verts[ pw[ r + 0 ] ];
						dv[ 1 ] = &mesh->verts[ pw[ r + 1 ] ];
						dv[ 2 ] = &mesh->verts[ pw[ r + 2 ] ];
						dv[ 3 ] = &mesh->verts[ pw[ r + 3 ] ];

						/* planar? (nuking this optimization as it doesn't work on non-rectangular quads) */
						plane[ 0 ] = 0.0f;  /* stupid msvc */
						if ( 0 && PlaneFromPoints( plane, dv[ 0 ]->xyz, dv[ 1 ]->xyz, dv[ 2 ]->xyz ) &&
							 fabs( DotProduct( dv[ 1 ]->xyz, plane ) - plane[ 3 ] ) <= PLANAR_EPSILON ) {
							/* make a quad projector */
							MakeDecalProjector( p->shaderInfo, projection, distance, 4, dv );
						}
						else
						{
							/* make first triangle */
							MakeDecalProjector( p->shaderInfo, projection, distance, 3, dv );

							/* make second triangle */
							dv[ 1 ] = dv[ 2 ];
							dv[ 2 ] = dv[ 3 ];
							MakeDecalProjector( p->shaderInfo, projection, distance, 3, dv );
						}
					}
				}

				/* clean up */
				free( mesh );
			}

			/* remove patch from entity (fixme: leak!) */
			e->patches = p->next;

			/* push patch to worldspawn (enable this to debug projectors) */
			#if 0
			p->next = entities[ 0 ].patches;
			entities[ 0 ].patches = p;
			#endif
		}
	}

	/* emit some stats */
	Sys_FPrintf( SYS_VRB, "%9d decal projectors\n", numProjectors );
}