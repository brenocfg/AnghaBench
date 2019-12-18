#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoVec3_t ;
typedef  int /*<<< orphan*/  picoVec2_t ;
struct TYPE_21__ {TYPE_2__* shader; } ;
typedef  TYPE_1__ picoSurface_t ;
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ picoShader_t ;
struct TYPE_23__ {int numSurfaces; TYPE_1__** surface; } ;
typedef  TYPE_3__ picoModel_t ;
typedef  int /*<<< orphan*/  picoIndex_t ;
typedef  int /*<<< orphan*/  picoColor_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_ERROR ; 
 int /*<<< orphan*/  PICO_TRIANGLES ; 
 int PicoFindSurfaceVertexNum (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PicoGetSurfaceNumIndexes (TYPE_1__*) ; 
 int PicoGetSurfaceNumVertexes (TYPE_1__*) ; 
 TYPE_1__* PicoNewSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  PicoSetSurfaceColor (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceIndex (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  PicoSetSurfaceName (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceNormal (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceST (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceShader (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PicoSetSurfaceSmoothingGroup (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceType (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceXYZ (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*) ; 

void PicoAddTriangleToModel( picoModel_t *model, picoVec3_t** xyz, picoVec3_t** normals,
							 int numSTs, picoVec2_t **st, int numColors, picoColor_t **colors,
							 picoShader_t* shader, picoIndex_t* smoothingGroup ){
	int i, j;
	int vertDataIndex;
	picoSurface_t* workSurface = NULL;

	/* see if a surface already has the shader */
	for ( i = 0 ; i < model->numSurfaces ; i++ )
	{
		workSurface = model->surface[i];
		if ( workSurface->shader == shader ) {
			break;
		}
	}

	/* no surface uses this shader yet, so create a new surface */
	if ( !workSurface || i >= model->numSurfaces ) {
		/* create a new surface in the model for the unique shader */
		workSurface = PicoNewSurface( model );
		if ( !workSurface ) {
			_pico_printf( PICO_ERROR, "Could not allocate a new surface!\n" );
			return;
		}

		/* do surface setup */
		PicoSetSurfaceType( workSurface, PICO_TRIANGLES );
		PicoSetSurfaceName( workSurface, shader->name );
		PicoSetSurfaceShader( workSurface, shader );
	}

	/* add the triangle data to the surface */
	for ( i = 0 ; i < 3 ; i++ )
	{
		/* get the next free spot in the index array */
		int newVertIndex = PicoGetSurfaceNumIndexes( workSurface );

		/* get the index of the vertex that we're going to store at newVertIndex */
		vertDataIndex = PicoFindSurfaceVertexNum( workSurface, *xyz[i], *normals[i], numSTs, st[i], numColors, colors[i], smoothingGroup[i] );

		/* the vertex wasn't found, so create a new vertex in the pool from the data we have */
		if ( vertDataIndex == -1 ) {
			/* find the next spot for a new vertex */
			vertDataIndex = PicoGetSurfaceNumVertexes( workSurface );

			/* assign the data to it */
			PicoSetSurfaceXYZ( workSurface,vertDataIndex, *xyz[i] );
			PicoSetSurfaceNormal( workSurface, vertDataIndex, *normals[i] );

			/* make sure to copy over all available ST's and colors for the vertex */
			for ( j = 0 ; j < numColors ; j++ )
			{
				PicoSetSurfaceColor( workSurface, j, vertDataIndex, colors[i][j] );
			}
			for ( j = 0 ; j < numSTs ; j++ )
			{
				PicoSetSurfaceST( workSurface, j, vertDataIndex, st[i][j] );
			}

			PicoSetSurfaceSmoothingGroup( workSurface, vertDataIndex, smoothingGroup[ i ] );
		}

		/* add this vertex to the triangle */
		PicoSetSurfaceIndex( workSurface, newVertIndex, vertDataIndex );
	}
}