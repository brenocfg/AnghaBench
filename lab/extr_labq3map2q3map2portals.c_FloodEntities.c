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
typedef  int* vec3_t ;
struct TYPE_10__ {scalar_t__ occupied; } ;
struct TYPE_11__ {TYPE_1__ outside_node; int /*<<< orphan*/ * headnode; } ;
typedef  TYPE_2__ tree_t ;
typedef  void* qboolean ;
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_12__ {int /*<<< orphan*/  mapEntityNum; } ;
typedef  TYPE_3__ entity_t ;

/* Variables and functions */
 int FloatForKey (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  GetVectorForKey (TYPE_3__*,char*,int*) ; 
 void* PlaceOccupant (int /*<<< orphan*/ *,int*,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  Q_stricmp (char const*,char*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 char* ValueForKey (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 scalar_t__ VectorCompare (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int*,float,int*) ; 
 int /*<<< orphan*/  VectorSet (int*,float,float,float) ; 
 scalar_t__ c_floodedleafs ; 
 int /*<<< orphan*/  eXYZ ; 
 TYPE_3__* entities ; 
 int /*<<< orphan*/  m4x4_identity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m4x4_pivoted_transform_by_vec3 (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int*,int*) ; 
 int numEntities ; 
 void* qfalse ; 
 void* qtrue ; 
 void* skyboxPresent ; 
 int /*<<< orphan*/  skyboxTransform ; 
 int sscanf (char const*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  vec3_origin ; 
 int /*<<< orphan*/  xml_Select (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

qboolean FloodEntities( tree_t *tree ){
	int i, s;
	vec3_t origin, offset, scale, angles;
	qboolean r, inside, tripped, skybox;
	node_t      *headnode;
	entity_t    *e;
	const char  *value;


	headnode = tree->headnode;
	Sys_FPrintf( SYS_VRB,"--- FloodEntities ---\n" );
	inside = qfalse;
	tree->outside_node.occupied = 0;

	tripped = qfalse;
	c_floodedleafs = 0;
	for ( i = 1; i < numEntities; i++ )
	{
		/* get entity */
		e = &entities[ i ];

		/* get origin */
		GetVectorForKey( e, "origin", origin );
		if ( VectorCompare( origin, vec3_origin ) ) {
			continue;
		}

		/* handle skybox entities */
		value = ValueForKey( e, "classname" );
		if ( !Q_stricmp( value, "_skybox" ) ) {
			skybox = qtrue;
			skyboxPresent = qtrue;

			/* invert origin */
			VectorScale( origin, -1.0f, offset );

			/* get scale */
			VectorSet( scale, 64.0f, 64.0f, 64.0f );
			value = ValueForKey( e, "_scale" );
			if ( value[ 0 ] != '\0' ) {
				s = sscanf( value, "%f %f %f", &scale[ 0 ], &scale[ 1 ], &scale[ 2 ] );
				if ( s == 1 ) {
					scale[ 1 ] = scale[ 0 ];
					scale[ 2 ] = scale[ 0 ];
				}
			}

			/* get "angle" (yaw) or "angles" (pitch yaw roll) */
			VectorClear( angles );
			angles[ 2 ] = FloatForKey( e, "angle" );
			value = ValueForKey( e, "angles" );
			if ( value[ 0 ] != '\0' ) {
				sscanf( value, "%f %f %f", &angles[ 1 ], &angles[ 2 ], &angles[ 0 ] );
			}

			/* set transform matrix (thanks spog) */
			m4x4_identity( skyboxTransform );
			m4x4_pivoted_transform_by_vec3( skyboxTransform, offset, angles, eXYZ, scale, origin );
		}
		else{
			skybox = qfalse;
		}

		/* nudge off floor */
		origin[ 2 ] += 1;

		/* debugging code */
		//%	if( i == 1 )
		//%		origin[ 2 ] += 4096;

		/* find leaf */
		r = PlaceOccupant( headnode, origin, e, skybox );
		if ( r ) {
			inside = qtrue;
		}
		if ( ( !r || tree->outside_node.occupied ) && !tripped ) {
			xml_Select( "Entity leaked", e->mapEntityNum, 0, qfalse );
			tripped = qtrue;
		}
	}

	Sys_FPrintf( SYS_VRB, "%9d flooded leafs\n", c_floodedleafs );

	if ( !inside ) {
		Sys_FPrintf( SYS_VRB, "no entities in open -- no filling\n" );
	}
	else if ( tree->outside_node.occupied ) {
		Sys_FPrintf( SYS_VRB, "entity reached from outside -- no filling\n" );
	}

	return (qboolean) ( inside && !tree->outside_node.occupied );
}