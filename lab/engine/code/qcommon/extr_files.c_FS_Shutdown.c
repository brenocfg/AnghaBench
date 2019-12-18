#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* dir; scalar_t__ pack; struct TYPE_5__* next; } ;
typedef  TYPE_1__ searchpath_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_6__ {scalar_t__ fileSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_RemoveCommand (char*) ; 
 int /*<<< orphan*/  FS_FCloseFile (int) ; 
 int /*<<< orphan*/  FS_FreePak (scalar_t__) ; 
 int MAX_FILE_HANDLES ; 
 int /*<<< orphan*/  Z_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 TYPE_1__* fs_searchpaths ; 
 TYPE_2__* fsh ; 
 int /*<<< orphan*/  missingFiles ; 

void FS_Shutdown( qboolean closemfp ) {
	searchpath_t	*p, *next;
	int	i;

	for(i = 0; i < MAX_FILE_HANDLES; i++) {
		if (fsh[i].fileSize) {
			FS_FCloseFile(i);
		}
	}

	// free everything
	for(p = fs_searchpaths; p; p = next)
	{
		next = p->next;

		if(p->pack)
			FS_FreePak(p->pack);
		if (p->dir)
			Z_Free(p->dir);

		Z_Free(p);
	}

	// any FS_ calls will now be an error until reinitialized
	fs_searchpaths = NULL;

	Cmd_RemoveCommand( "path" );
	Cmd_RemoveCommand( "dir" );
	Cmd_RemoveCommand( "fdir" );
	Cmd_RemoveCommand( "touchFile" );
	Cmd_RemoveCommand( "which" );

#ifdef FS_MISSING
	if (closemfp) {
		fclose(missingFiles);
	}
#endif
}