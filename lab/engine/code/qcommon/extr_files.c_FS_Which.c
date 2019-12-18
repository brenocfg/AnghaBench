#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dir; TYPE_1__* pack; } ;
typedef  TYPE_3__ searchpath_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int /*<<< orphan*/  fullpath; } ;
struct TYPE_5__ {int /*<<< orphan*/  pakFilename; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ FS_FOpenFileReadDir (char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean FS_Which(const char *filename, void *searchPath)
{
	searchpath_t *search = searchPath;

	if(FS_FOpenFileReadDir(filename, search, NULL, qfalse, qfalse) > 0)
	{
		if(search->pack)
		{
			Com_Printf("File \"%s\" found in \"%s\"\n", filename, search->pack->pakFilename);
			return qtrue;
		}
		else if(search->dir)
		{
			Com_Printf( "File \"%s\" found at \"%s\"\n", filename, search->dir->fullpath);
			return qtrue;
		}
	}

	return qfalse;
}