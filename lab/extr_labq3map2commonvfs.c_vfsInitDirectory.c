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
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char const*) ; 
 int VFS_MAXDIRS ; 
 scalar_t__ g_bUsePak ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_numDirs ; 
 char** g_strDirs ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  vfsAddSlash (char*) ; 
 int /*<<< orphan*/  vfsFixDOSName (char*) ; 
 int /*<<< orphan*/  vfsInitPakFile (char*) ; 

void vfsInitDirectory( const char *path ){
	char filename[PATH_MAX];
	char *dirlist;
	GDir *dir;

	if ( g_numDirs == ( VFS_MAXDIRS - 1 ) ) {
		return;
	}

	Sys_Printf( "VFS Init: %s\n", path );

	strcpy( g_strDirs[g_numDirs], path );
	vfsFixDOSName( g_strDirs[g_numDirs] );
	vfsAddSlash( g_strDirs[g_numDirs] );
	g_numDirs++;

	if ( g_bUsePak ) {
		dir = g_dir_open( path, 0, NULL );

		if ( dir != NULL ) {
			while ( 1 )
			{
				const char* name = g_dir_read_name( dir );
				if ( name == NULL ) {
					break;
				}

				dirlist = g_strdup( name );

				{

					char *ext = strrchr( dirlist, '.' );

					if ( ext != NULL && ( !Q_stricmp( ext, ".pk3dir" ) || !Q_stricmp( ext, ".dpkdir" ) ) ) {
						if ( g_numDirs == VFS_MAXDIRS ) {
							continue;
						}
						snprintf( g_strDirs[g_numDirs], PATH_MAX, "%s/%s", path, name );
						g_strDirs[g_numDirs][PATH_MAX-1] = '\0';
						vfsFixDOSName( g_strDirs[g_numDirs] );
						vfsAddSlash( g_strDirs[g_numDirs] );
						++g_numDirs;
					}

					if ( ext == NULL || ( Q_stricmp( ext, ".pk3" ) != 0 && Q_stricmp( ext, ".dpk" ) != 0 ) ) {
						continue;
					}
				}

				sprintf( filename, "%s/%s", path, dirlist );
				vfsInitPakFile( filename );

				g_free( dirlist );
			}
			g_dir_close( dir );
		}
	}
}