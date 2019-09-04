#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceName ;
typedef  int /*<<< orphan*/  picoSurface_t ;
typedef  int /*<<< orphan*/  picoShader_t ;
struct TYPE_13__ {scalar_t__ id; scalar_t__ len; } ;
struct TYPE_12__ {long cofs; long maxofs; int /*<<< orphan*/ * shader; scalar_t__ bufptr; int /*<<< orphan*/  model; int /*<<< orphan*/ * surface; } ;
typedef  TYPE_1__ T3dsLoaderPers ;
typedef  TYPE_2__ T3dsChunk ;

/* Variables and functions */
 scalar_t__ CHUNK_KEYFRAME_DATA ; 
 scalar_t__ CHUNK_MATDIFFUSE ; 
 scalar_t__ CHUNK_MATERIAL ; 
 scalar_t__ CHUNK_MATMAP ; 
 scalar_t__ CHUNK_MATMAPFILE ; 
 scalar_t__ CHUNK_MATNAME ; 
 scalar_t__ CHUNK_OBJECT ; 
 scalar_t__ CHUNK_OBJECT_FACES ; 
 scalar_t__ CHUNK_OBJECT_MATERIAL ; 
 scalar_t__ CHUNK_OBJECT_MESH ; 
 scalar_t__ CHUNK_OBJECT_UV ; 
 scalar_t__ CHUNK_OBJECT_VERTICES ; 
 int /*<<< orphan*/  GetASCIIZ (TYPE_1__*,char*,int) ; 
 TYPE_2__* GetChunk (TYPE_1__*) ; 
 int /*<<< orphan*/  GetDiffuseColor (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMeshFaces (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMeshShader (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMeshTexCoords (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMeshVertices (TYPE_1__*) ; 
 int /*<<< orphan*/  PICO_TRIANGLES ; 
 int /*<<< orphan*/ * PicoNewShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PicoNewSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetShaderMapName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PicoSetShaderName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PicoSetSurfaceName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PicoSetSurfaceType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* _pico_clone_alloc (char*) ; 
 int /*<<< orphan*/  _pico_first_token (char*) ; 
 int /*<<< orphan*/  _pico_free (char*) ; 

__attribute__((used)) static int DoNextEditorDataChunk( T3dsLoaderPers *pers, long endofs ){
	T3dsChunk *chunk;

#ifdef DEBUG_PM_3DS_EX
	printf( "DoNextEditorDataChunk: endofs %d\n",endofs );
#endif
	while ( pers->cofs < endofs )
	{
		long nextofs = pers->cofs;
		if ( ( chunk = GetChunk( pers ) ) == NULL ) {
			return 0;
		}
		if ( !chunk->len ) {
			return 0;
		}
		nextofs += chunk->len;

#ifdef DEBUG_PM_3DS_EX
		printf( "Chunk %04x (%s), len %d pers->cofs %x\n",chunk->id,DebugGetChunkName( chunk->id ),chunk->len,pers->cofs );
#endif
		/*** meshes ***/
		if ( chunk->id == CHUNK_OBJECT ) {
			picoSurface_t *surface;
			char surfaceName[ 0xff ] = { 0 };

			/* read in surface name */
			if ( !GetASCIIZ( pers,surfaceName,sizeof( surfaceName ) ) ) {
				return 0; /* this is bad */
			}
//PicoGetSurfaceName
			/* ignore NULL name surfaces */
//			if( surfaceName

			/* allocate a pico surface */
			surface = PicoNewSurface( pers->model );
			if ( surface == NULL ) {
				pers->surface = NULL;
				return 0; /* this is bad too */
			}
			/* assign ptr to current surface */
			pers->surface = surface;

			/* 3ds models surfaces are all triangle meshes */
			PicoSetSurfaceType( pers->surface,PICO_TRIANGLES );

			/* set surface name */
			PicoSetSurfaceName( pers->surface,surfaceName );

			/* continue mess with object's sub chunks */
			DoNextEditorDataChunk( pers,nextofs );
			continue;
		}
		if ( chunk->id == CHUNK_OBJECT_MESH ) {
			/* continue mess with mesh's sub chunks */
			if ( !DoNextEditorDataChunk( pers,nextofs ) ) {
				return 0;
			}
			continue;
		}
		if ( chunk->id == CHUNK_OBJECT_VERTICES ) {
			if ( !GetMeshVertices( pers ) ) {
				return 0;
			}
			continue;
		}
		if ( chunk->id == CHUNK_OBJECT_FACES ) {
			if ( !GetMeshFaces( pers ) ) {
				return 0;
			}
			continue;
		}
		if ( chunk->id == CHUNK_OBJECT_UV ) {
			if ( !GetMeshTexCoords( pers ) ) {
				return 0;
			}
			continue;
		}
		if ( chunk->id == CHUNK_OBJECT_MATERIAL ) {
			if ( !GetMeshShader( pers ) ) {
				return 0;
			}
			continue;
		}
		/*** materials ***/
		if ( chunk->id == CHUNK_MATERIAL ) {
			/* new shader specific things should be */
			/* initialized right here */
			picoShader_t *shader;

			/* allocate a pico shader */
			shader = PicoNewShader( pers->model );  /* ydnar */
			if ( shader == NULL ) {
				pers->shader = NULL;
				return 0; /* this is bad too */
			}

			/* assign ptr to current shader */
			pers->shader = shader;

			/* continue and process the material's sub chunks */
			DoNextEditorDataChunk( pers,nextofs );
			continue;
		}
		if ( chunk->id == CHUNK_MATNAME ) {
			/* new material's names should be stored here. note that */
			/* GetMeshMaterial returns the name of the material that */
			/* is used by the mesh. new material names are set HERE. */
			/* but for now we skip the new material's name ... */
			if ( pers->shader ) {
				char *name = (char *)( pers->bufptr + pers->cofs );
				char *cleanedName = _pico_clone_alloc( name );
				_pico_first_token( cleanedName );
				PicoSetShaderName( pers->shader, cleanedName );
#ifdef DEBUG_PM_3DS
				printf( "NewShader: '%s'\n", cleanedName );
#endif
				_pico_free( cleanedName );
			}
		}
		if ( chunk->id == CHUNK_MATDIFFUSE ) {
			/* todo: color for last inserted new material should be */
			/* stored somewhere by GetDiffuseColor */
			if ( !GetDiffuseColor( pers ) ) {
				return 0;
			}

			/* rest of chunk is skipped here */
		}
		if ( chunk->id == CHUNK_MATMAP ) {
			/* continue and process the material map sub chunks */
			DoNextEditorDataChunk( pers,nextofs );
			continue;
		}
		if ( chunk->id == CHUNK_MATMAPFILE ) {
			/* map file name for last inserted new material should */
			/* be stored here. but for now we skip this too ... */
			if ( pers->shader ) {
				char *name = (char *)( pers->bufptr + pers->cofs );
				PicoSetShaderMapName( pers->shader,name );
#ifdef DEBUG_PM_3DS
				printf( "NewShaderMapfile: '%s'\n",name );
#endif
			}
		}
		/*** keyframes ***/
		if ( chunk->id == CHUNK_KEYFRAME_DATA ) {
			/* well umm, this is a bit too much since we don't really */
			/* need model animation sequences right now. we skip this */
#ifdef DEBUG_PM_3DS
			printf( "KeyframeData: len %d\n",chunk->len );
#endif
		}
		/* skip unknown chunk */
		pers->cofs = nextofs;
		if ( pers->cofs >= pers->maxofs ) {
			break;
		}
	}
	return 1;
}