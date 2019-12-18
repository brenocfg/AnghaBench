#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pack; struct TYPE_4__* next; } ;
typedef  TYPE_1__ searchpath_t ;
typedef  int qboolean ;
typedef  scalar_t__ fileHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 long FS_FOpenFileReadDir (char const*,TYPE_1__*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 char* Q3CONFIG_CFG ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char const*) ; 
 TYPE_1__* fs_searchpaths ; 
 scalar_t__ missingFiles ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

long FS_FOpenFileRead(const char *filename, fileHandle_t *file, qboolean uniqueFILE)
{
	searchpath_t *search;
	long len;
	qboolean isLocalConfig;

	if(!fs_searchpaths)
		Com_Error(ERR_FATAL, "Filesystem call made without initialization");

	isLocalConfig = !strcmp(filename, "autoexec.cfg") || !strcmp(filename, Q3CONFIG_CFG);
	for(search = fs_searchpaths; search; search = search->next)
	{
		// autoexec.cfg and q3config.cfg can only be loaded outside of pk3 files.
		if (isLocalConfig && search->pack)
			continue;

		len = FS_FOpenFileReadDir(filename, search, file, uniqueFILE, qfalse);

		if(file == NULL)
		{
			if(len > 0)
				return len;
		}
		else
		{
			if(len >= 0 && *file)
				return len;
		}

	}
	
#ifdef FS_MISSING
	if(missingFiles)
		fprintf(missingFiles, "%s\n", filename);
#endif

	if(file)
	{
		*file = 0;
		return -1;
	}
	else
	{
		// When file is NULL, we're querying the existence of the file
		// If we've got here, it doesn't exist
		return 0;
	}
}