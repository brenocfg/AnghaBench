#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int parentSurfaceNum; int entityNum; int castShadows; int recvShadows; int sampleSize; double longestCurve; double* lightmapAxis; TYPE_2__* si; TYPE_1__* mds; } ;
typedef  TYPE_3__ surfaceExtra_t ;
struct TYPE_7__ {char* shader; } ;
struct TYPE_6__ {size_t type; int numVerts; int numIndexes; scalar_t__ planar; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 TYPE_3__* GetSurfaceExtra (int) ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,...) ; 
 scalar_t__ VectorCompare (double*,double*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int numSurfaceExtras ; 
 scalar_t__ qfalse ; 
 TYPE_3__ seDefault ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char** surfaceTypes ; 

void WriteSurfaceExtraFile( const char *path ){
	char srfPath[ 1024 ];
	FILE            *sf;
	surfaceExtra_t  *se;
	int i;


	/* dummy check */
	if ( path == NULL || path[ 0 ] == '\0' ) {
		return;
	}

	/* note it */
	Sys_Printf( "--- WriteSurfaceExtraFile ---\n" );

	/* open the file */
	strcpy( srfPath, path );
	StripExtension( srfPath );
	strcat( srfPath, ".srf" );
	Sys_Printf( "Writing %s\n", srfPath );
	sf = fopen( srfPath, "w" );
	if ( sf == NULL ) {
		Error( "Error opening %s for writing", srfPath );
	}

	/* lap through the extras list */
	for ( i = -1; i < numSurfaceExtras; i++ )
	{
		/* get extra */
		se = GetSurfaceExtra( i );

		/* default or surface num? */
		if ( i < 0 ) {
			fprintf( sf, "default" );
		}
		else{
			fprintf( sf, "%d", i );
		}

		/* valid map drawsurf? */
		if ( se->mds == NULL ) {
			fprintf( sf, "\n" );
		}
		else
		{
			fprintf( sf, " // %s V: %d I: %d %s\n",
					 surfaceTypes[ se->mds->type ],
					 se->mds->numVerts,
					 se->mds->numIndexes,
					 ( se->mds->planar ? "planar" : "" ) );
		}

		/* open braces */
		fprintf( sf, "{\n" );

		/* shader */
		if ( se->si != NULL ) {
			fprintf( sf, "\tshader %s\n", se->si->shader );
		}

		/* parent surface number */
		if ( se->parentSurfaceNum != seDefault.parentSurfaceNum ) {
			fprintf( sf, "\tparent %d\n", se->parentSurfaceNum );
		}

		/* entity number */
		if ( se->entityNum != seDefault.entityNum ) {
			fprintf( sf, "\tentity %d\n", se->entityNum );
		}

		/* cast shadows */
		if ( se->castShadows != seDefault.castShadows || se == &seDefault ) {
			fprintf( sf, "\tcastShadows %d\n", se->castShadows );
		}

		/* recv shadows */
		if ( se->recvShadows != seDefault.recvShadows || se == &seDefault ) {
			fprintf( sf, "\treceiveShadows %d\n", se->recvShadows );
		}

		/* lightmap sample size */
		if ( se->sampleSize != seDefault.sampleSize || se == &seDefault ) {
			fprintf( sf, "\tsampleSize %d\n", se->sampleSize );
		}

		/* longest curve */
		if ( se->longestCurve != seDefault.longestCurve || se == &seDefault ) {
			fprintf( sf, "\tlongestCurve %f\n", se->longestCurve );
		}

		/* lightmap axis vector */
		if ( VectorCompare( se->lightmapAxis, seDefault.lightmapAxis ) == qfalse ) {
			fprintf( sf, "\tlightmapAxis ( %f %f %f )\n", se->lightmapAxis[ 0 ], se->lightmapAxis[ 1 ], se->lightmapAxis[ 2 ] );
		}

		/* close braces */
		fprintf( sf, "}\n\n" );
	}

	/* close the file */
	fclose( sf );
}