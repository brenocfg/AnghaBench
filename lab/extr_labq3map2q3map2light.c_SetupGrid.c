#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_8__ {float* mins; float* maxs; } ;
struct TYPE_7__ {float** ambient; void** styles; } ;

/* Variables and functions */
 void* LS_NONE ; 
 void* LS_NORMAL ; 
 int MAX_LIGHTMAPS ; 
 int MAX_MAP_LIGHTGRID ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SetKeyValue (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,int,...) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VectorCompare (float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float* ambientColor ; 
 TYPE_1__* bspGridPoints ; 
 TYPE_5__* bspModels ; 
 float ceil (float) ; 
 int /*<<< orphan*/ * entities ; 
 float floor (float) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int* gridBounds ; 
 float* gridMins ; 
 float* gridSize ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ noGridLighting ; 
 int numBSPGridPoints ; 
 int numRawGridPoints ; 
 TYPE_1__* rawGridPoints ; 
 TYPE_1__* safe_malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,float,float,float) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,float*,float*,float*) ; 

void SetupGrid( void ){
	int i, j;
	vec3_t maxs, oldGridSize;
	const char  *value;
	char temp[ 64 ];


	/* don't do this if not grid lighting */
	if ( noGridLighting ) {
		return;
	}

	/* ydnar: set grid size */
	value = ValueForKey( &entities[ 0 ], "gridsize" );
	if ( value[ 0 ] != '\0' ) {
		sscanf( value, "%f %f %f", &gridSize[ 0 ], &gridSize[ 1 ], &gridSize[ 2 ] );
	}

	/* quantize it */
	VectorCopy( gridSize, oldGridSize );
	for ( i = 0; i < 3; i++ )
		gridSize[ i ] = gridSize[ i ] >= 8.0f ? floor( gridSize[ i ] ) : 8.0f;

	/* ydnar: increase gridSize until grid count is smaller than max allowed */
	numRawGridPoints = MAX_MAP_LIGHTGRID + 1;
	j = 0;
	while ( numRawGridPoints > MAX_MAP_LIGHTGRID )
	{
		/* get world bounds */
		for ( i = 0; i < 3; i++ )
		{
			gridMins[ i ] = gridSize[ i ] * ceil( bspModels[ 0 ].mins[ i ] / gridSize[ i ] );
			maxs[ i ] = gridSize[ i ] * floor( bspModels[ 0 ].maxs[ i ] / gridSize[ i ] );
			gridBounds[ i ] = ( maxs[ i ] - gridMins[ i ] ) / gridSize[ i ] + 1;
		}

		/* set grid size */
		numRawGridPoints = gridBounds[ 0 ] * gridBounds[ 1 ] * gridBounds[ 2 ];

		/* increase grid size a bit */
		if ( numRawGridPoints > MAX_MAP_LIGHTGRID ) {
			gridSize[ j++ % 3 ] += 16.0f;
		}
	}

	/* print it */
	Sys_Printf( "Grid size = { %1.0f, %1.0f, %1.0f }\n", gridSize[ 0 ], gridSize[ 1 ], gridSize[ 2 ] );

	/* different? */
	if ( !VectorCompare( gridSize, oldGridSize ) ) {
		sprintf( temp, "%.0f %.0f %.0f", gridSize[ 0 ], gridSize[ 1 ], gridSize[ 2 ] );
		SetKeyValue( &entities[ 0 ], "gridsize", (const char*) temp );
		Sys_FPrintf( SYS_VRB, "Storing adjusted grid size\n" );
	}

	/* 2nd variable. fixme: is this silly? */
	numBSPGridPoints = numRawGridPoints;

	/* allocate lightgrid */
	rawGridPoints = safe_malloc( numRawGridPoints * sizeof( *rawGridPoints ) );
	memset( rawGridPoints, 0, numRawGridPoints * sizeof( *rawGridPoints ) );

	if ( bspGridPoints != NULL ) {
		free( bspGridPoints );
	}
	bspGridPoints = safe_malloc( numBSPGridPoints * sizeof( *bspGridPoints ) );
	memset( bspGridPoints, 0, numBSPGridPoints * sizeof( *bspGridPoints ) );

	/* clear lightgrid */
	for ( i = 0; i < numRawGridPoints; i++ )
	{
		VectorCopy( ambientColor, rawGridPoints[ i ].ambient[ j ] );
		rawGridPoints[ i ].styles[ 0 ] = LS_NORMAL;
		bspGridPoints[ i ].styles[ 0 ] = LS_NORMAL;
		for ( j = 1; j < MAX_LIGHTMAPS; j++ )
		{
			rawGridPoints[ i ].styles[ j ] = LS_NONE;
			bspGridPoints[ i ].styles[ j ] = LS_NONE;
		}
	}

	/* note it */
	Sys_Printf( "%9d grid points\n", numRawGridPoints );
}