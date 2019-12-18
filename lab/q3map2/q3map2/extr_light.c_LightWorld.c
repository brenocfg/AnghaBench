#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEntityLights () ; 
 int /*<<< orphan*/  CreateSurfaceLights () ; 
 int /*<<< orphan*/  DirtyRawLightmap ; 
 float FloatForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetVectorForKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IlluminateRawLightmap ; 
 int /*<<< orphan*/  IlluminateVertexes ; 
 int /*<<< orphan*/  MapRawLightmap ; 
 int /*<<< orphan*/  RadCreateDiffuseLights () ; 
 int /*<<< orphan*/  RadFreeLights () ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SetupEnvelopes (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGrid () ; 
 int /*<<< orphan*/  SmoothNormals () ; 
 int /*<<< orphan*/  StitchSurfaceLightmaps () ; 
 int /*<<< orphan*/  StoreSurfaceLightmaps () ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 int /*<<< orphan*/  TraceGrid ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/  WriteBSPFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ambientColor ; 
 float atof (char const*) ; 
 int bounce ; 
 scalar_t__ bouncegrid ; 
 scalar_t__ bouncing ; 
 scalar_t__ dirty ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/  fast ; 
 int /*<<< orphan*/  fastbounce ; 
 int /*<<< orphan*/  fastgrid ; 
 int /*<<< orphan*/ * gridBounds ; 
 scalar_t__ gridBoundsCulled ; 
 scalar_t__ gridEnvelopeCulled ; 
 scalar_t__ lightsBoundsCulled ; 
 scalar_t__ lightsClusterCulled ; 
 scalar_t__ lightsEnvelopeCulled ; 
 scalar_t__ lightsPlaneCulled ; 
 int /*<<< orphan*/  minGridLight ; 
 int /*<<< orphan*/  minLight ; 
 int /*<<< orphan*/  minVertexLight ; 
 int /*<<< orphan*/  noGridLighting ; 
 int /*<<< orphan*/  numBSPDrawSurfaces ; 
 int /*<<< orphan*/  numBSPGridPoints ; 
 int /*<<< orphan*/  numDiffuseLights ; 
 scalar_t__ numLights ; 
 int /*<<< orphan*/  numLuxels ; 
 int /*<<< orphan*/  numLuxelsIlluminated ; 
 int /*<<< orphan*/  numLuxelsMapped ; 
 int /*<<< orphan*/  numLuxelsOccluded ; 
 int /*<<< orphan*/  numPointLights ; 
 int /*<<< orphan*/  numRawGridPoints ; 
 int /*<<< orphan*/  numRawLightmaps ; 
 int /*<<< orphan*/  numSpotLights ; 
 int /*<<< orphan*/  numSunLights ; 
 int /*<<< orphan*/  numVertsIlluminated ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 scalar_t__ shade ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  subdivideThreshold ; 

void LightWorld( void ){
	vec3_t color;
	float f;
	int b, bt;
	qboolean minVertex, minGrid;
	const char  *value;


	/* ydnar: smooth normals */
	if ( shade ) {
		Sys_Printf( "--- SmoothNormals ---\n" );
		SmoothNormals();
	}

	/* determine the number of grid points */
	Sys_Printf( "--- SetupGrid ---\n" );
	SetupGrid();

	/* find the optional minimum lighting values */
	GetVectorForKey( &entities[ 0 ], "_color", color );
	if ( VectorLength( color ) == 0.0f ) {
		VectorSet( color, 1.0, 1.0, 1.0 );
	}

	/* ambient */
	f = FloatForKey( &entities[ 0 ], "_ambient" );
	if ( f == 0.0f ) {
		f = FloatForKey( &entities[ 0 ], "ambient" );
	}
	VectorScale( color, f, ambientColor );

	/* minvertexlight */
	minVertex = qfalse;
	value = ValueForKey( &entities[ 0 ], "_minvertexlight" );
	if ( value[ 0 ] != '\0' ) {
		minVertex = qtrue;
		f = atof( value );
		VectorScale( color, f, minVertexLight );
	}

	/* mingridlight */
	minGrid = qfalse;
	value = ValueForKey( &entities[ 0 ], "_mingridlight" );
	if ( value[ 0 ] != '\0' ) {
		minGrid = qtrue;
		f = atof( value );
		VectorScale( color, f, minGridLight );
	}

	/* minlight */
	value = ValueForKey( &entities[ 0 ], "_minlight" );
	if ( value[ 0 ] != '\0' ) {
		f = atof( value );
		VectorScale( color, f, minLight );
		if ( minVertex == qfalse ) {
			VectorScale( color, f, minVertexLight );
		}
		if ( minGrid == qfalse ) {
			VectorScale( color, f, minGridLight );
		}
	}

	/* create world lights */
	Sys_FPrintf( SYS_VRB, "--- CreateLights ---\n" );
	CreateEntityLights();
	CreateSurfaceLights();
	Sys_Printf( "%9d point lights\n", numPointLights );
	Sys_Printf( "%9d spotlights\n", numSpotLights );
	Sys_Printf( "%9d diffuse (area) lights\n", numDiffuseLights );
	Sys_Printf( "%9d sun/sky lights\n", numSunLights );

	/* calculate lightgrid */
	if ( !noGridLighting ) {
		/* ydnar: set up light envelopes */
		SetupEnvelopes( qtrue, fastgrid );

		Sys_Printf( "--- TraceGrid ---\n" );
		RunThreadsOnIndividual( numRawGridPoints, qtrue, TraceGrid );
		Sys_Printf( "%d x %d x %d = %d grid\n",
					gridBounds[ 0 ], gridBounds[ 1 ], gridBounds[ 2 ], numBSPGridPoints );

		/* ydnar: emit statistics on light culling */
		Sys_FPrintf( SYS_VRB, "%9d grid points envelope culled\n", gridEnvelopeCulled );
		Sys_FPrintf( SYS_VRB, "%9d grid points bounds culled\n", gridBoundsCulled );
	}

	/* slight optimization to remove a sqrt */
	subdivideThreshold *= subdivideThreshold;

	/* map the world luxels */
	Sys_Printf( "--- MapRawLightmap ---\n" );
	RunThreadsOnIndividual( numRawLightmaps, qtrue, MapRawLightmap );
	Sys_Printf( "%9d luxels\n", numLuxels );
	Sys_Printf( "%9d luxels mapped\n", numLuxelsMapped );
	Sys_Printf( "%9d luxels occluded\n", numLuxelsOccluded );

	/* dirty them up */
	if ( dirty ) {
		Sys_Printf( "--- DirtyRawLightmap ---\n" );




		RunThreadsOnIndividual( numRawLightmaps, qtrue, DirtyRawLightmap );
	}


	/* ydnar: set up light envelopes */
	SetupEnvelopes( qfalse, fast );

	/* light up my world */
	lightsPlaneCulled = 0;
	lightsEnvelopeCulled = 0;
	lightsBoundsCulled = 0;
	lightsClusterCulled = 0;

	Sys_Printf( "--- IlluminateRawLightmap ---\n" );
	RunThreadsOnIndividual( numRawLightmaps, qtrue, IlluminateRawLightmap );
	Sys_Printf( "%9d luxels illuminated\n", numLuxelsIlluminated );

	StitchSurfaceLightmaps();

	Sys_Printf( "--- IlluminateVertexes ---\n" );
	RunThreadsOnIndividual( numBSPDrawSurfaces, qtrue, IlluminateVertexes );
	Sys_Printf( "%9d vertexes illuminated\n", numVertsIlluminated );

	/* ydnar: emit statistics on light culling */
	Sys_FPrintf( SYS_VRB, "%9d lights plane culled\n", lightsPlaneCulled );
	Sys_FPrintf( SYS_VRB, "%9d lights envelope culled\n", lightsEnvelopeCulled );
	Sys_FPrintf( SYS_VRB, "%9d lights bounds culled\n", lightsBoundsCulled );
	Sys_FPrintf( SYS_VRB, "%9d lights cluster culled\n", lightsClusterCulled );

	/* radiosity */
	b = 1;
	bt = bounce;
	while ( bounce > 0 )
	{
		/* store off the bsp between bounces */
		StoreSurfaceLightmaps();
		Sys_Printf( "Writing %s\n", source );
		WriteBSPFile( source );

		/* note it */
		Sys_Printf( "\n--- Radiosity (bounce %d of %d) ---\n", b, bt );

		/* flag bouncing */
		bouncing = qtrue;
		VectorClear( ambientColor );

		/* generate diffuse lights */
		RadFreeLights();
		RadCreateDiffuseLights();

		/* setup light envelopes */
		SetupEnvelopes( qfalse, fastbounce );
		if ( numLights == 0 ) {
			Sys_Printf( "No diffuse light to calculate, ending radiosity.\n" );
			return;
		}

		/* add to lightgrid */
		if ( bouncegrid ) {
			gridEnvelopeCulled = 0;
			gridBoundsCulled = 0;

			Sys_Printf( "--- BounceGrid ---\n" );
			RunThreadsOnIndividual( numRawGridPoints, qtrue, TraceGrid );
			Sys_FPrintf( SYS_VRB, "%9d grid points envelope culled\n", gridEnvelopeCulled );
			Sys_FPrintf( SYS_VRB, "%9d grid points bounds culled\n", gridBoundsCulled );
		}

		/* light up my world */
		lightsPlaneCulled = 0;
		lightsEnvelopeCulled = 0;
		lightsBoundsCulled = 0;
		lightsClusterCulled = 0;

		Sys_Printf( "--- IlluminateRawLightmap ---\n" );
		RunThreadsOnIndividual( numRawLightmaps, qtrue, IlluminateRawLightmap );
		Sys_Printf( "%9d luxels illuminated\n", numLuxelsIlluminated );
		Sys_Printf( "%9d vertexes illuminated\n", numVertsIlluminated );

		StitchSurfaceLightmaps();

		Sys_Printf( "--- IlluminateVertexes ---\n" );
		RunThreadsOnIndividual( numBSPDrawSurfaces, qtrue, IlluminateVertexes );
		Sys_Printf( "%9d vertexes illuminated\n", numVertsIlluminated );

		/* ydnar: emit statistics on light culling */
		Sys_FPrintf( SYS_VRB, "%9d lights plane culled\n", lightsPlaneCulled );
		Sys_FPrintf( SYS_VRB, "%9d lights envelope culled\n", lightsEnvelopeCulled );
		Sys_FPrintf( SYS_VRB, "%9d lights bounds culled\n", lightsBoundsCulled );
		Sys_FPrintf( SYS_VRB, "%9d lights cluster culled\n", lightsClusterCulled );

		/* interate */
		bounce--;
		b++;
	}
	/* ydnar: store off lightmaps */
	StoreSurfaceLightmaps();

}