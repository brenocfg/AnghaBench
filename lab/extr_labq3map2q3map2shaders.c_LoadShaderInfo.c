#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* shaderPath; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int) ; 
 scalar_t__ GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadScriptFile (char*,int) ; 
 int /*<<< orphan*/  MAX_OS_PATH ; 
 int MAX_SHADER_FILES ; 
 int /*<<< orphan*/  ParseCustomInfoParms () ; 
 int /*<<< orphan*/  ParseShaderFile (char*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* game ; 
 int /*<<< orphan*/  numShaderInfo ; 
 int /*<<< orphan*/  qtrue ; 
 char* safe_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token ; 
 scalar_t__ useCustomInfoParms ; 
 int vfsGetFileCount (char*) ; 

void LoadShaderInfo( void ){
	int i, j, numShaderFiles, count;
	char filename[ 1024 ];
	char            *shaderFiles[ MAX_SHADER_FILES ];


	/* rr2do2: parse custom infoparms first */
	if ( useCustomInfoParms ) {
		ParseCustomInfoParms();
	}

	/* start with zero */
	numShaderFiles = 0;

	/* we can pile up several shader files, the one in baseq3 and ones in the mod dir or other spots */
	sprintf( filename, "%s/shaderlist.txt", game->shaderPath );
	count = vfsGetFileCount( filename );

	/* load them all */
	for ( i = 0; i < count; i++ )
	{
		/* load shader list */
		sprintf( filename, "%s/shaderlist.txt", game->shaderPath );
		LoadScriptFile( filename, i );

		/* parse it */
		while ( GetToken( qtrue ) )
		{
			/* check for duplicate entries */
			for ( j = 0; j < numShaderFiles; j++ )
				if ( !strcmp( shaderFiles[ j ], token ) ) {
					break;
				}

			/* test limit */
			if ( j >= MAX_SHADER_FILES ) {
				Error( "MAX_SHADER_FILES (%d) reached, trim your shaderlist.txt!", (int) MAX_SHADER_FILES );
			}

			/* new shader file */
			if ( j == numShaderFiles ) {
				shaderFiles[ numShaderFiles ] = safe_malloc( MAX_OS_PATH );
				strcpy( shaderFiles[ numShaderFiles ], token );
				numShaderFiles++;
			}
		}
	}

	/* parse the shader files */
	for ( i = 0; i < numShaderFiles; i++ )
	{
		sprintf( filename, "%s/%s.shader", game->shaderPath, shaderFiles[ i ] );
		ParseShaderFile( filename );
		free( shaderFiles[ i ] );
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d shaderInfo\n", numShaderInfo );
}