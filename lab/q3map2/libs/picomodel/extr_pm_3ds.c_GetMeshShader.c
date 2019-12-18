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
typedef  int /*<<< orphan*/  temp ;
typedef  int /*<<< orphan*/  shaderName ;
typedef  int /*<<< orphan*/  picoShader_t ;
typedef  int /*<<< orphan*/  mapName ;
struct TYPE_5__ {char* basename; scalar_t__ surface; int /*<<< orphan*/  model; } ;
typedef  TYPE_1__ T3dsLoaderPers ;

/* Variables and functions */
 int /*<<< orphan*/  GetASCIIZ (TYPE_1__*,char*,int) ; 
 int GetWord (TYPE_1__*) ; 
 int /*<<< orphan*/  PICO_WARNING ; 
 int /*<<< orphan*/ * PicoFindShader (int /*<<< orphan*/ ,char*,int) ; 
 char* PicoGetShaderMapName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PicoSetSurfaceShader (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pico_first_token (char*) ; 
 char* _pico_nopath (char*) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _pico_strlwr (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int GetMeshShader( T3dsLoaderPers *pers ){
	char shaderName[255] = { 0 };
	picoShader_t  *shader;
	int numSharedVerts;
	int setShaderName = 0;
	int i;

	/* the shader is either the color or the texture map of the */
	/* object. it can also hold other information like the brightness, */
	/* shine, etc. stuff we don't really care about. we just want the */
	/* color, or the texture map file name really */

	/* get in the shader name */
	if ( !GetASCIIZ( pers,shaderName,sizeof( shaderName ) ) ) {
		return 0;
	}

	/* ydnar: trim to first whitespace */
	_pico_first_token( shaderName );
	
	/* now that we have the shader name we need to go through all of */
	/* the shaders and check the name against each shader. when we */
	/* find a shader in our shader list that matches this name we */
	/* just read in, then we assign the shader's id of the object to */
	/* that shader */

	/* get shader id for shader name */
	shader = PicoFindShader( pers->model, shaderName, 1 );

	/* we've found a matching shader */
	if ( ( shader != NULL ) && pers->surface ) {
		char mapName[1024 + 1];
		char *mapNamePtr;
		memset( mapName,0,sizeof( mapName ) );

		/* get ptr to shader's map name */
		mapNamePtr = PicoGetShaderMapName( shader );

		/* we have a valid map name ptr */
		if ( mapNamePtr != NULL ) {
			char temp[128];
			const char *name;

			/* copy map name to local buffer */
			strcpy( mapName,mapNamePtr );

			/* extract file name */
			name = _pico_nopath( mapName );
			strncpy( temp, name, sizeof( temp ) );

			/* remove file extension */
			/* name = _pico_setfext( name,"" ); */

			/* assign default name if no name available */
			if ( strlen( temp ) < 1 ) {
				strcpy( temp,pers->basename );
			}

			/* build shader name */
			_pico_strlwr( temp ); /* gaynux update -sea */
			sprintf( mapName,"models/mapobjects/%s/%s",pers->basename,temp );

			/* set shader name */
			/* PicoSetShaderName( shader,mapName ); */	/* ydnar: this will screw up the named shader */

			/* set surface's shader index */
			PicoSetSurfaceShader( pers->surface, shader );

			setShaderName = 1;
		}
	}
	/* we didn't set a shader name; throw out warning */
	if ( !setShaderName ) {
		_pico_printf( PICO_WARNING,"3DS mesh is missing shader name" );
	}
	/* we don't process the list of shared vertices here; there is a */
	/* short int that gives the number of faces of the mesh concerned */
	/* by this shader, then there is the list itself of these faces. */
	/* 0000 means the first face of the (4120) face list */

	/* get number of shared verts */
	numSharedVerts = GetWord( pers );

#ifdef DEBUG_PM_3DS
	printf( "GetMeshShader: uses shader '%s' (nsv %d)\n",shaderName,numSharedVerts );
#endif
	/* skip list of shared verts */
	for ( i = 0; i < numSharedVerts; i++ )
	{
		GetWord( pers );
	}
	/* success (no errors occured) */
	return 1;
}