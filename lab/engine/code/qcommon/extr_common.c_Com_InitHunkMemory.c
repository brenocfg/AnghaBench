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
struct TYPE_5__ {int integer; } ;
typedef  TYPE_1__ cvar_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_6__ {scalar_t__ integer; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Meminfo_f ; 
 int /*<<< orphan*/  Com_Printf (char*,int,int) ; 
 TYPE_1__* Cvar_Get (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Cvar_SetDescription (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  DEF_COMHUNKMEGS_S ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ FS_LoadStack () ; 
 int /*<<< orphan*/  Hunk_Clear () ; 
 int /*<<< orphan*/  Hunk_Log ; 
 int /*<<< orphan*/  Hunk_SmallLog ; 
 int MIN_COMHUNKMEGS ; 
 int MIN_DEDICATED_COMHUNKMEGS ; 
 int /*<<< orphan*/  Z_LogHeap ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* com_dedicated ; 
 int /*<<< orphan*/ * s_hunkData ; 
 scalar_t__ s_hunkDataRaw ; 
 int s_hunkTotal ; 

void Com_InitHunkMemory( void ) {
	cvar_t	*cv;
	int nMinAlloc;
	char *pMsg = NULL;

	// make sure the file system has allocated and "not" freed any temp blocks
	// this allows the config and product id files ( journal files too ) to be loaded
	// by the file system without redunant routines in the file system utilizing different 
	// memory systems
	if (FS_LoadStack() != 0) {
		Com_Error( ERR_FATAL, "Hunk initialization failed. File system load stack not zero");
	}

	// allocate the stack based hunk allocator
	cv = Cvar_Get( "com_hunkMegs", DEF_COMHUNKMEGS_S, CVAR_LATCH | CVAR_ARCHIVE );
	Cvar_SetDescription(cv, "The size of the hunk memory segment");

	// if we are not dedicated min allocation is 56, otherwise min is 1
	if (com_dedicated && com_dedicated->integer) {
		nMinAlloc = MIN_DEDICATED_COMHUNKMEGS;
		pMsg = "Minimum com_hunkMegs for a dedicated server is %i, allocating %i megs.\n";
	}
	else {
		nMinAlloc = MIN_COMHUNKMEGS;
		pMsg = "Minimum com_hunkMegs is %i, allocating %i megs.\n";
	}

	if ( cv->integer < nMinAlloc ) {
		s_hunkTotal = 1024 * 1024 * nMinAlloc;
	    Com_Printf(pMsg, nMinAlloc, s_hunkTotal / (1024 * 1024));
	} else {
		s_hunkTotal = cv->integer * 1024 * 1024;
	}

	s_hunkDataRaw = calloc( s_hunkTotal + 31, 1 );
	if ( !s_hunkDataRaw ) {
		Com_Error( ERR_FATAL, "Hunk data failed to allocate %i megs", s_hunkTotal / (1024*1024) );
	}
	// cacheline align
	s_hunkData = (byte *) ( ( (intptr_t)s_hunkDataRaw + 31 ) & ~31 );
	Hunk_Clear();

	Cmd_AddCommand( "meminfo", Com_Meminfo_f );
#ifdef ZONE_DEBUG
	Cmd_AddCommand( "zonelog", Z_LogHeap );
#endif
#ifdef HUNK_DEBUG
	Cmd_AddCommand( "hunklog", Hunk_Log );
	Cmd_AddCommand( "hunksmalllog", Hunk_SmallLog );
#endif
}