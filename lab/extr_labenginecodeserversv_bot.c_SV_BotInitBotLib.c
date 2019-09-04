#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  DebugPolygonDelete; int /*<<< orphan*/  DebugPolygonCreate; int /*<<< orphan*/  DebugLineShow; int /*<<< orphan*/  DebugLineDelete; int /*<<< orphan*/  DebugLineCreate; int /*<<< orphan*/  FS_Seek; int /*<<< orphan*/  FS_FCloseFile; int /*<<< orphan*/  FS_Write; int /*<<< orphan*/  FS_Read; int /*<<< orphan*/  FS_FOpenFile; int /*<<< orphan*/  HunkAlloc; int /*<<< orphan*/  AvailableMemory; int /*<<< orphan*/  FreeMemory; int /*<<< orphan*/  GetMemory; int /*<<< orphan*/  BotClientCommand; int /*<<< orphan*/  BSPModelMinsMaxsOrigin; int /*<<< orphan*/  BSPEntityData; int /*<<< orphan*/  inPVS; int /*<<< orphan*/  PointContents; int /*<<< orphan*/  EntityTrace; int /*<<< orphan*/  Trace; int /*<<< orphan*/  Print; } ;
typedef  TYPE_1__ botlib_import_t ;
typedef  int /*<<< orphan*/  botlib_export_t ;
typedef  int /*<<< orphan*/  bot_debugpoly_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOTLIB_API_VERSION ; 
 int /*<<< orphan*/  BotClientCommand ; 
 int /*<<< orphan*/  BotImport_BSPEntityData ; 
 int /*<<< orphan*/  BotImport_BSPModelMinsMaxsOrigin ; 
 int /*<<< orphan*/  BotImport_DebugLineCreate ; 
 int /*<<< orphan*/  BotImport_DebugLineDelete ; 
 int /*<<< orphan*/  BotImport_DebugLineShow ; 
 int /*<<< orphan*/  BotImport_DebugPolygonCreate ; 
 int /*<<< orphan*/  BotImport_DebugPolygonDelete ; 
 int /*<<< orphan*/  BotImport_EntityTrace ; 
 int /*<<< orphan*/  BotImport_FreeMemory ; 
 int /*<<< orphan*/  BotImport_GetMemory ; 
 int /*<<< orphan*/  BotImport_HunkAlloc ; 
 int /*<<< orphan*/  BotImport_PointContents ; 
 int /*<<< orphan*/  BotImport_Print ; 
 int /*<<< orphan*/  BotImport_Trace ; 
 int /*<<< orphan*/  BotImport_inPVS ; 
 int Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  FS_FCloseFile ; 
 int /*<<< orphan*/  FS_FOpenFileByMode ; 
 int /*<<< orphan*/  FS_Read ; 
 int /*<<< orphan*/  FS_Seek ; 
 int /*<<< orphan*/  FS_Write ; 
 scalar_t__ GetBotLibAPI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Z_AvailableMemory ; 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 scalar_t__ Z_Malloc (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bot_maxdebugpolys ; 
 int /*<<< orphan*/ * botlib_export ; 
 scalar_t__ debugpolygons ; 

void SV_BotInitBotLib(void) {
	botlib_import_t	botlib_import;

	if (debugpolygons) Z_Free(debugpolygons);
	bot_maxdebugpolys = Cvar_VariableIntegerValue("bot_maxdebugpolys");
	debugpolygons = Z_Malloc(sizeof(bot_debugpoly_t) * bot_maxdebugpolys);

	botlib_import.Print = BotImport_Print;
	botlib_import.Trace = BotImport_Trace;
	botlib_import.EntityTrace = BotImport_EntityTrace;
	botlib_import.PointContents = BotImport_PointContents;
	botlib_import.inPVS = BotImport_inPVS;
	botlib_import.BSPEntityData = BotImport_BSPEntityData;
	botlib_import.BSPModelMinsMaxsOrigin = BotImport_BSPModelMinsMaxsOrigin;
	botlib_import.BotClientCommand = BotClientCommand;

	//memory management
	botlib_import.GetMemory = BotImport_GetMemory;
	botlib_import.FreeMemory = BotImport_FreeMemory;
	botlib_import.AvailableMemory = Z_AvailableMemory;
	botlib_import.HunkAlloc = BotImport_HunkAlloc;

	// file system access
	botlib_import.FS_FOpenFile = FS_FOpenFileByMode;
	botlib_import.FS_Read = FS_Read;
	botlib_import.FS_Write = FS_Write;
	botlib_import.FS_FCloseFile = FS_FCloseFile;
	botlib_import.FS_Seek = FS_Seek;

	//debug lines
	botlib_import.DebugLineCreate = BotImport_DebugLineCreate;
	botlib_import.DebugLineDelete = BotImport_DebugLineDelete;
	botlib_import.DebugLineShow = BotImport_DebugLineShow;

	//debug polygons
	botlib_import.DebugPolygonCreate = BotImport_DebugPolygonCreate;
	botlib_import.DebugPolygonDelete = BotImport_DebugPolygonDelete;

	botlib_export = (botlib_export_t *)GetBotLibAPI( BOTLIB_API_VERSION, &botlib_import );
	assert(botlib_export); 	// somehow we end up with a zero import.
}