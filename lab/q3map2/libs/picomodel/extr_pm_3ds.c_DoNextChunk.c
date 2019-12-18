#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; int id; } ;
struct TYPE_8__ {int cofs; long maxofs; } ;
typedef  TYPE_1__ T3dsLoaderPers ;
typedef  TYPE_2__ T3dsChunk ;

/* Variables and functions */
 int CHUNK_EDITOR_DATA ; 
 int CHUNK_VERSION ; 
 char* DebugGetChunkName (int) ; 
 int /*<<< orphan*/  DoNextEditorDataChunk (TYPE_1__*,long) ; 
 TYPE_2__* GetChunk (TYPE_1__*) ; 
 int GetWord (TYPE_1__*) ; 
 int /*<<< orphan*/  PICO_WARNING ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int DoNextChunk( T3dsLoaderPers *pers, int endofs ){
	T3dsChunk *chunk;

#ifdef DEBUG_PM_3DS
	printf( "DoNextChunk: endofs %d\n",endofs );
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
		/*** version ***/
		if ( chunk->id == CHUNK_VERSION ) {
			/* at this point i get the 3ds file version. since there */
			/* might be new additions to the 3ds file format in 4.0 */
			/* it might be a good idea to store the version somewhere */
			/* for later handling or message displaying */

			/* get the version */
			int version;
			version = GetWord( pers );
			GetWord( pers );
#ifdef DEBUG_PM_3DS
			printf( "FileVersion: %d\n",version );
#endif

			/* throw out a warning for version 4 models */
			if ( version == 4 ) {
				_pico_printf( PICO_WARNING,
							  "3DS version is 4. Model might load incorrectly." );
			}
			/* store the 3ds file version in pico special field 0 */
			/* PicoSetSurfaceSpecial(pers->surface,0,version); */		/* ydnar: this was causing a crash accessing uninitialized surface */

			/* rest of chunk is skipped here */
		}
		/*** editor data ***/
		if ( chunk->id == CHUNK_EDITOR_DATA ) {
			if ( !DoNextEditorDataChunk( pers,nextofs ) ) {
				return 0;
			}
			continue;
		}
		/* skip unknown chunk */
		pers->cofs = nextofs;
		if ( pers->cofs >= pers->maxofs ) {
			break;
		}
	}
	return 1;
}