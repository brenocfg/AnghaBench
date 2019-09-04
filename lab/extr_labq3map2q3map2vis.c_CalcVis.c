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
 int /*<<< orphan*/  BasePortalVis ; 
 int /*<<< orphan*/  CalcFastVis () ; 
 int /*<<< orphan*/  CalcPassagePortalVis () ; 
 int /*<<< orphan*/  CalcPassageVis () ; 
 int /*<<< orphan*/  CalcPortalVis () ; 
 int /*<<< orphan*/  ClusterMerge (int) ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SortPortals () ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 float atof (char const*) ; 
 int /*<<< orphan*/ * entities ; 
 float farPlaneDist ; 
 scalar_t__ fastvis ; 
 scalar_t__ noPassageVis ; 
 int numportals ; 
 scalar_t__ passageVisOnly ; 
 int portalclusters ; 
 int /*<<< orphan*/  qtrue ; 
 int totalvis ; 

void CalcVis( void ){
	int i;
	const char  *value;


	/* ydnar: rr2do2's farplane code */
	farPlaneDist = 0.0f;
	value = ValueForKey( &entities[ 0 ], "_farplanedist" );     /* proper '_' prefixed key */
	if ( value[ 0 ] == '\0' ) {
		value = ValueForKey( &entities[ 0 ], "fogclip" );       /* wolf compatibility */
	}
	if ( value[ 0 ] == '\0' ) {
		value = ValueForKey( &entities[ 0 ], "distancecull" );  /* sof2 compatibility */
	}
	if ( value[ 0 ] != '\0' ) {
		farPlaneDist = atof( value );
		if ( farPlaneDist > 0.0f ) {
			Sys_Printf( "farplane distance = %.1f\n", farPlaneDist );
		}
		else{
			farPlaneDist = 0.0f;
		}
	}



	Sys_Printf( "\n--- BasePortalVis (%d) ---\n", numportals * 2 );
	RunThreadsOnIndividual( numportals * 2, qtrue, BasePortalVis );

//	RunThreadsOnIndividual (numportals*2, qtrue, BetterPortalVis);

	SortPortals();

	if ( fastvis ) {
		CalcFastVis();
	}
	else if ( noPassageVis ) {
		CalcPortalVis();
	}
	else if ( passageVisOnly ) {
		CalcPassageVis();
	}
	else {
		CalcPassagePortalVis();
	}
	//
	// assemble the leaf vis lists by oring and compressing the portal lists
	//
	Sys_Printf( "creating leaf vis...\n" );
	for ( i = 0 ; i < portalclusters ; i++ )
		ClusterMerge( i );

	Sys_Printf( "Total visible clusters: %i\n", totalvis );
	Sys_Printf( "Average clusters visible: %i\n", totalvis / portalclusters );
}