#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  longestCurve; void* sampleSize; void* recvShadows; void* castShadows; void* entityNum; void* parentSurfaceNum; int /*<<< orphan*/  si; } ;
typedef  TYPE_1__ surfaceExtra_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 TYPE_1__* AllocSurfaceExtra () ; 
 int /*<<< orphan*/  Error (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int LoadFile (char*,void**) ; 
 int MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  Parse1DMatrix (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseFromMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripExtension (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char*) ; 
 scalar_t__ TokenAvailable () ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int numSurfaceExtras ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  scriptline ; 
 TYPE_1__ seDefault ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 TYPE_1__* surfaceExtras ; 
 int /*<<< orphan*/  token ; 

void LoadSurfaceExtraFile( const char *path ){
	char srfPath[ 1024 ];
	surfaceExtra_t  *se;
	int surfaceNum, size;
	byte            *buffer;


	/* dummy check */
	if ( path == NULL || path[ 0 ] == '\0' ) {
		return;
	}

	/* load the file */
	strcpy( srfPath, path );
	StripExtension( srfPath );
	strcat( srfPath, ".srf" );
	Sys_Printf( "Loading %s\n", srfPath );
	size = LoadFile( srfPath, (void**) &buffer );
	if ( size <= 0 ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Unable to find surface file %s, using defaults.\n", srfPath );
		return;
	}

	/* parse the file */
	ParseFromMemory( buffer, size );

	/* tokenize it */
	while ( 1 )
	{
		/* test for end of file */
		if ( !GetToken( qtrue ) ) {
			break;
		}

		/* default? */
		if ( !Q_stricmp( token, "default" ) ) {
			se = &seDefault;
		}

		/* surface number */
		else
		{
			surfaceNum = atoi( token );
			if ( surfaceNum < 0 || surfaceNum > MAX_MAP_DRAW_SURFS ) {
				Error( "ReadSurfaceExtraFile(): %s, line %d: bogus surface num %d", srfPath, scriptline, surfaceNum );
			}
			while ( surfaceNum >= numSurfaceExtras )
				se = AllocSurfaceExtra();
			se = &surfaceExtras[ surfaceNum ];
		}

		/* handle { } section */
		if ( !GetToken( qtrue ) || strcmp( token, "{" ) ) {
			Error( "ReadSurfaceExtraFile(): %s, line %d: { not found", srfPath, scriptline );
		}
		while ( 1 )
		{
			if ( !GetToken( qtrue ) ) {
				break;
			}
			if ( !strcmp( token, "}" ) ) {
				break;
			}

			/* shader */
			if ( !Q_stricmp( token, "shader" ) ) {
				GetToken( qfalse );
				se->si = ShaderInfoForShader( token );
			}

			/* parent surface number */
			else if ( !Q_stricmp( token, "parent" ) ) {
				GetToken( qfalse );
				se->parentSurfaceNum = atoi( token );
			}

			/* entity number */
			else if ( !Q_stricmp( token, "entity" ) ) {
				GetToken( qfalse );
				se->entityNum = atoi( token );
			}

			/* cast shadows */
			else if ( !Q_stricmp( token, "castShadows" ) ) {
				GetToken( qfalse );
				se->castShadows = atoi( token );
			}

			/* recv shadows */
			else if ( !Q_stricmp( token, "receiveShadows" ) ) {
				GetToken( qfalse );
				se->recvShadows = atoi( token );
			}

			/* lightmap sample size */
			else if ( !Q_stricmp( token, "sampleSize" ) ) {
				GetToken( qfalse );
				se->sampleSize = atoi( token );
			}

			/* longest curve */
			else if ( !Q_stricmp( token, "longestCurve" ) ) {
				GetToken( qfalse );
				se->longestCurve = atof( token );
			}

			/* lightmap axis vector */
			else if ( !Q_stricmp( token, "lightmapAxis" ) ) {
				Parse1DMatrix( 3, se->lightmapAxis );
			}

			/* ignore all other tokens on the line */
			while ( TokenAvailable() )
				GetToken( qfalse );
		}
	}

	/* free the buffer */
	free( buffer );
}