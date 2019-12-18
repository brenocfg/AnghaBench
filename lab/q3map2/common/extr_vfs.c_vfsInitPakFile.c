#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unz_s ;
struct TYPE_14__ {scalar_t__ number_entry; } ;
typedef  TYPE_1__ unz_global_info ;
struct TYPE_15__ {int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_2__ unz_file_info ;
typedef  TYPE_3__* unzFile ;
typedef  scalar_t__ guint32 ;
typedef  int /*<<< orphan*/  filename_inzip ;
struct TYPE_16__ {int /*<<< orphan*/  zipinfo; struct TYPE_16__* zipfile; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ VFS_PAKFILE ;

/* Variables and functions */
 int NAME_MAX ; 
 int UNZ_OK ; 
 char* g_ascii_strdown (char*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_pakFiles ; 
 int /*<<< orphan*/  g_slist_append (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  g_unzFiles ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ safe_malloc (int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int unzGetCurrentFileInfo (TYPE_3__*,TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unzGetGlobalInfo (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  unzGoToFirstFile (TYPE_3__*) ; 
 int unzGoToNextFile (TYPE_3__*) ; 
 TYPE_3__* unzOpen (char const*) ; 
 int /*<<< orphan*/  vfsFixDOSName (char*) ; 

__attribute__((used)) static void vfsInitPakFile( const char *filename ){
	unz_global_info gi;
	unzFile uf;
	guint32 i;
	int err;

	uf = unzOpen( filename );
	if ( uf == NULL ) {
		return;
	}

	g_unzFiles = g_slist_append( g_unzFiles, uf );

	err = unzGetGlobalInfo( uf,&gi );
	if ( err != UNZ_OK ) {
		return;
	}
	unzGoToFirstFile( uf );

	for ( i = 0; i < gi.number_entry; i++ )
	{
		char filename_inzip[NAME_MAX];
		char *filename_lower;
		unz_file_info file_info;
		VFS_PAKFILE* file;

		err = unzGetCurrentFileInfo( uf, &file_info, filename_inzip, sizeof( filename_inzip ), NULL, 0, NULL, 0 );
		if ( err != UNZ_OK ) {
			break;
		}

		file = (VFS_PAKFILE*)safe_malloc( sizeof( VFS_PAKFILE ) );
		g_pakFiles = g_slist_append( g_pakFiles, file );

		vfsFixDOSName( filename_inzip );
		filename_lower = g_ascii_strdown( filename_inzip, -1 );//-1 null terminated string

		file->name = strdup( filename_lower );
		file->size = file_info.uncompressed_size;
		file->zipfile = uf;
		memcpy( &file->zipinfo, uf, sizeof( unz_s ) );

		if ( ( i + 1 ) < gi.number_entry ) {
			err = unzGoToNextFile( uf );
			if ( err != UNZ_OK ) {
				break;
			}
		}
		g_free( filename_lower );
	}
}