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

/* Variables and functions */
 float DEG2RAD (int) ; 
 int DIRT_CONE_ANGLE ; 
 float DIRT_NUM_ANGLE_STEPS ; 
 int DIRT_NUM_ELEVATION_STEPS ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int cos (float) ; 
 int** dirtVectors ; 
 size_t numDirtVectors ; 
 int sin (float) ; 

void SetupDirt( void ){
	int i, j;
	float angle, elevation, angleStep, elevationStep;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- SetupDirt ---\n" );

	/* calculate angular steps */
	angleStep = DEG2RAD( 360.0f / DIRT_NUM_ANGLE_STEPS );
	elevationStep = DEG2RAD( DIRT_CONE_ANGLE / DIRT_NUM_ELEVATION_STEPS );

	/* iterate angle */
	angle = 0.0f;
	for ( i = 0, angle = 0.0f; i < DIRT_NUM_ANGLE_STEPS; i++, angle += angleStep )
	{
		/* iterate elevation */
		for ( j = 0, elevation = elevationStep * 0.5f; j < DIRT_NUM_ELEVATION_STEPS; j++, elevation += elevationStep )
		{
			dirtVectors[ numDirtVectors ][ 0 ] = sin( elevation ) * cos( angle );
			dirtVectors[ numDirtVectors ][ 1 ] = sin( elevation ) * sin( angle );
			dirtVectors[ numDirtVectors ][ 2 ] = cos( elevation );
			numDirtVectors++;
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d dirtmap vectors\n", numDirtVectors );
}