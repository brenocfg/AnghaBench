#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double* origin; double* color; scalar_t__ add; struct TYPE_3__* next; } ;
typedef  TYPE_1__ light_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RadLight ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 scalar_t__ dump ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,double,double,double,double,double,double) ; 
 int iterations ; 
 TYPE_1__* lights ; 
 scalar_t__ numAreaLights ; 
 int /*<<< orphan*/  numBSPDrawSurfaces ; 
 scalar_t__ numBrushDiffuseLights ; 
 scalar_t__ numDiffuseLights ; 
 char* numDiffuseSurfaces ; 
 scalar_t__ numPatchDiffuseLights ; 
 scalar_t__ numTriangleDiffuseLights ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void RadCreateDiffuseLights( void ){
	/* startup */
	Sys_FPrintf( SYS_VRB, "--- RadCreateDiffuseLights ---\n" );
	numDiffuseSurfaces = 0;
	numDiffuseLights = 0;
	numBrushDiffuseLights = 0;
	numTriangleDiffuseLights = 0;
	numPatchDiffuseLights = 0;
	numAreaLights = 0;

	/* hit every surface (threaded) */
	RunThreadsOnIndividual( numBSPDrawSurfaces, qtrue, RadLight );

	/* dump the lights generated to a file */
	if ( dump ) {
		char dumpName[ 1024 ], ext[ 64 ];
		FILE    *file;
		light_t *light;

		strcpy( dumpName, source );
		StripExtension( dumpName );
		sprintf( ext, "_bounce_%03d.map", iterations );
		strcat( dumpName, ext );
		file = fopen( dumpName, "wb" );
		Sys_Printf( "Writing %s...\n", dumpName );
		if ( file ) {
			for ( light = lights; light; light = light->next )
			{
				fprintf( file,
						 "{\n"
						 "\"classname\" \"light\"\n"
						 "\"light\" \"%d\"\n"
						 "\"origin\" \"%.0f %.0f %.0f\"\n"
						 "\"_color\" \"%.3f %.3f %.3f\"\n"
						 "}\n",

						 (int) light->add,

						 light->origin[ 0 ],
						 light->origin[ 1 ],
						 light->origin[ 2 ],

						 light->color[ 0 ],
						 light->color[ 1 ],
						 light->color[ 2 ] );
			}
			fclose( file );
		}
	}

	/* increment */
	iterations++;

	/* print counts */
	Sys_Printf( "%8d diffuse surfaces\n", numDiffuseSurfaces );
	Sys_FPrintf( SYS_VRB, "%8d total diffuse lights\n", numDiffuseLights );
	Sys_FPrintf( SYS_VRB, "%8d brush diffuse lights\n", numBrushDiffuseLights );
	Sys_FPrintf( SYS_VRB, "%8d patch diffuse lights\n", numPatchDiffuseLights );
	Sys_FPrintf( SYS_VRB, "%8d triangle diffuse lights\n", numTriangleDiffuseLights );
}