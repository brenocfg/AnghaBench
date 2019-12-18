#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tw ;
struct TYPE_9__ {int numVerts; TYPE_1__* v; int /*<<< orphan*/  infoNum; } ;
typedef  TYPE_2__ traceWinding_t ;
struct TYPE_10__ {int castShadows; int surfaceNum; TYPE_5__* si; } ;
typedef  TYPE_3__ traceInfo_t ;
typedef  int /*<<< orphan*/  picoVec_t ;
typedef  int /*<<< orphan*/  picoSurface_t ;
typedef  int /*<<< orphan*/  picoShader_t ;
typedef  int /*<<< orphan*/  picoModel_t ;
typedef  int /*<<< orphan*/  picoIndex_t ;
typedef  int /*<<< orphan*/ * m4x4_t ;
struct TYPE_11__ {int compileFlags; } ;
struct TYPE_8__ {int /*<<< orphan*/  xyz; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddTraceInfo (TYPE_3__*) ; 
 int C_ALPHASHADOW ; 
 int C_LIGHTFILTER ; 
 int C_NODRAW ; 
 int C_TRANSLUCENT ; 
 int /*<<< orphan*/  FilterTraceWindingIntoNodes_r (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PICO_TRIANGLES ; 
 int PicoGetModelNumSurfaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PicoGetModelSurface (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PicoGetShaderName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PicoGetSurfaceIndexes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PicoGetSurfaceNumIndexes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PicoGetSurfaceST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PicoGetSurfaceShader (int /*<<< orphan*/ *) ; 
 scalar_t__ PicoGetSurfaceType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PicoGetSurfaceXYZ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector2Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  headNodeNum ; 
 int /*<<< orphan*/  m4x4_transform_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PopulateWithPicoModel( int castShadows, picoModel_t *model, m4x4_t transform ){
	int i, j, k, numSurfaces, numIndexes;
	picoSurface_t       *surface;
	picoShader_t        *shader;
	picoVec_t           *xyz, *st;
	picoIndex_t         *indexes;
	traceInfo_t ti;
	traceWinding_t tw;


	/* dummy check */
	if ( model == NULL || transform == NULL ) {
		return;
	}

	/* get info */
	numSurfaces = PicoGetModelNumSurfaces( model );

	/* walk the list of surfaces in this model and fill out the info structs */
	for ( i = 0; i < numSurfaces; i++ )
	{
		/* get surface */
		surface = PicoGetModelSurface( model, i );
		if ( surface == NULL ) {
			continue;
		}

		/* only handle triangle surfaces initially (fixme: support patches) */
		if ( PicoGetSurfaceType( surface ) != PICO_TRIANGLES ) {
			continue;
		}

		/* get shader (fixme: support shader remapping) */
		shader = PicoGetSurfaceShader( surface );
		if ( shader == NULL ) {
			continue;
		}
		ti.si = ShaderInfoForShader( PicoGetShaderName( shader ) );
		if ( ti.si == NULL ) {
			continue;
		}

		/* translucent surfaces that are neither alphashadow or lightfilter don't cast shadows */
		if ( ( ti.si->compileFlags & C_NODRAW ) ) {
			continue;
		}
		if ( ( ti.si->compileFlags & C_TRANSLUCENT ) &&
			 !( ti.si->compileFlags & C_ALPHASHADOW ) &&
			 !( ti.si->compileFlags & C_LIGHTFILTER ) ) {
			continue;
		}

		/* setup trace info */
		ti.castShadows = castShadows;
		ti.surfaceNum = -1;

		/* setup trace winding */
		memset( &tw, 0, sizeof( tw ) );
		tw.infoNum = AddTraceInfo( &ti );
		tw.numVerts = 3;

		/* get info */
		numIndexes = PicoGetSurfaceNumIndexes( surface );
		indexes = PicoGetSurfaceIndexes( surface, 0 );

		/* walk the triangle list */
		for ( j = 0; j < numIndexes; j += 3, indexes += 3 )
		{
			for ( k = 0; k < 3; k++ )
			{
				xyz = PicoGetSurfaceXYZ( surface, indexes[ k ] );
				st = PicoGetSurfaceST( surface, 0, indexes[ k ] );
				VectorCopy( xyz, tw.v[ k ].xyz );
				Vector2Copy( st, tw.v[ k ].st );
				m4x4_transform_point( transform, tw.v[ k ].xyz );
			}
			FilterTraceWindingIntoNodes_r( &tw, headNodeNum );
		}
	}
}