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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  COM_StripExtension (char*,char*,int) ; 
 int /*<<< orphan*/  FS_ConvertPath (char*) ; 
 int /*<<< orphan*/  FS_FreeFileList (char**) ; 
 char** FS_ListFilteredFiles (char const*,char const*,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int /*<<< orphan*/  FS_SortFileList (char**,int) ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 

void	FS_FilenameCompletion( const char *dir, const char *ext,
		qboolean stripExt, void(*callback)(const char *s), qboolean allowNonPureFilesOnDisk ) {
	char	**filenames;
	int		nfiles;
	int		i;
	char	filename[ MAX_STRING_CHARS ];

	filenames = FS_ListFilteredFiles( dir, ext, NULL, &nfiles, allowNonPureFilesOnDisk );

	FS_SortFileList( filenames, nfiles );

	for( i = 0; i < nfiles; i++ ) {
		FS_ConvertPath( filenames[ i ] );
		Q_strncpyz( filename, filenames[ i ], MAX_STRING_CHARS );

		if( stripExt ) {
			COM_StripExtension(filename, filename, sizeof(filename));
		}

		callback( filename );
	}
	FS_FreeFileList( filenames );
}