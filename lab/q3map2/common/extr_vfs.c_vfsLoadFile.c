#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unz_s ;
struct TYPE_6__ {int size; int /*<<< orphan*/  zipfile; int /*<<< orphan*/  zipinfo; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VFS_PAKFILE ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ GSList ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NAME_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ UNZ_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (void*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* g_ascii_strdown (char*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_numDirs ; 
 TYPE_2__* g_pakFiles ; 
 TYPE_2__* g_slist_next (TYPE_2__*) ; 
 char const** g_strDirs ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 void* safe_malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  unzCloseCurrentFile (int /*<<< orphan*/ ) ; 
 scalar_t__ unzOpenCurrentFile (int /*<<< orphan*/ ) ; 
 int unzReadCurrentFile (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  vfsFixDOSName (char*) ; 

int vfsLoadFile( const char *filename, void **bufferptr, int index ){
	int i, count = 0;
	char tmp[NAME_MAX], fixed[NAME_MAX];
	char *lower;
	GSList *lst;

	// filename is a full path
	if ( index == -1 ) {
		long len;
		FILE *f;

		f = fopen( filename, "rb" );
		if ( f == NULL ) {
			return -1;
		}

		fseek( f, 0, SEEK_END );
		len = ftell( f );
		rewind( f );

		*bufferptr = safe_malloc( len + 1 );
		if ( *bufferptr == NULL ) {
			return -1;
		}

		fread( *bufferptr, 1, len, f );
		fclose( f );

		// we need to end the buffer with a 0
		( (char*) ( *bufferptr ) )[len] = 0;

		return len;
	}

	*bufferptr = NULL;
	strcpy( fixed, filename );
	vfsFixDOSName( fixed );
	lower = g_ascii_strdown( fixed, -1 );

	for ( i = 0; i < g_numDirs; i++ )
	{
		strcpy( tmp, g_strDirs[i] );
		strcat( tmp, filename );
		if ( access( tmp, R_OK ) == 0 ) {
			if ( count == index ) {
				long len;
				FILE *f;

				f = fopen( tmp, "rb" );
				if ( f == NULL ) {
					return -1;
				}

				fseek( f, 0, SEEK_END );
				len = ftell( f );
				rewind( f );

				*bufferptr = safe_malloc( len + 1 );
				if ( *bufferptr == NULL ) {
					return -1;
				}

				fread( *bufferptr, 1, len, f );
				fclose( f );

				// we need to end the buffer with a 0
				( (char*) ( *bufferptr ) )[len] = 0;

				return len;
			}

			count++;
		}
	}

	for ( lst = g_pakFiles; lst != NULL; lst = g_slist_next( lst ) )
	{
		VFS_PAKFILE* file = (VFS_PAKFILE*)lst->data;

		if ( strcmp( file->name, lower ) != 0 ) {
			continue;
		}

		if ( count == index ) {
			memcpy( file->zipfile, &file->zipinfo, sizeof( unz_s ) );

			if ( unzOpenCurrentFile( file->zipfile ) != UNZ_OK ) {
				return -1;
			}

			*bufferptr = safe_malloc( file->size + 1 );
			// we need to end the buffer with a 0
			( (char*) ( *bufferptr ) )[file->size] = 0;

			i = unzReadCurrentFile( file->zipfile, *bufferptr, file->size );
			unzCloseCurrentFile( file->zipfile );
			if ( i < 0 ) {
				return -1;
			}
			else{
				g_free( lower );
				return file->size;
			}
		}

		count++;
	}
	g_free( lower );
	return -1;
}