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
struct TYPE_3__ {char* string; } ;
typedef  TYPE_1__ vmCvar_t ;

/* Variables and functions */
 int CVAR_INIT ; 
 int CVAR_ROM ; 
 int /*<<< orphan*/  UI_LoadBotsFromFile (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_Cvar_Register (TYPE_1__*,char*,char*,int) ; 
 int trap_FS_GetFileList (char*,char*,char*,int) ; 
 int /*<<< orphan*/  trap_Print (int /*<<< orphan*/ ) ; 
 scalar_t__ ui_numBots ; 
 int /*<<< orphan*/  va (char*,scalar_t__) ; 

__attribute__((used)) static void UI_LoadBots( void ) {
	vmCvar_t	botsFile;
	int			numdirs;
	char		filename[128];
	char		dirlist[1024];
	char*		dirptr;
	int			i;
	int			dirlen;

	ui_numBots = 0;

	trap_Cvar_Register( &botsFile, "g_botsFile", "", CVAR_INIT|CVAR_ROM );
	if( *botsFile.string ) {
		UI_LoadBotsFromFile(botsFile.string);
	}
	else {
		UI_LoadBotsFromFile("scripts/bots.txt");
	}

	// get all bots from .bot files
	numdirs = trap_FS_GetFileList("scripts", ".bot", dirlist, 1024 );
	dirptr  = dirlist;
	for (i = 0; i < numdirs; i++, dirptr += dirlen+1) {
		dirlen = strlen(dirptr);
		strcpy(filename, "scripts/");
		strcat(filename, dirptr);
		UI_LoadBotsFromFile(filename);
	}
	trap_Print( va( "%i bots parsed\n", ui_numBots ) );
}