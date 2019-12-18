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
typedef  int /*<<< orphan*/  modName ;
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 scalar_t__ DR_YES ; 
 int /*<<< orphan*/  DT_YES_NO ; 
 int /*<<< orphan*/  FS_GetModDescription (char const*,char*,int) ; 
 int MAX_OSPATH ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 scalar_t__ Sys_Dialog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ Sys_WritePIDFile (char const*) ; 

void Sys_InitPIDFile( const char *gamedir ) {
	if( Sys_WritePIDFile( gamedir ) ) {
#ifndef DEDICATED
		char message[1024];
		char modName[MAX_OSPATH];

		FS_GetModDescription( gamedir, modName, sizeof ( modName ) );
		Q_CleanStr( modName );

		Com_sprintf( message, sizeof (message), "The last time %s ran, "
			"it didn't exit properly. This may be due to inappropriate video "
			"settings. Would you like to start with \"safe\" video settings?", modName );

		if( Sys_Dialog( DT_YES_NO, message, "Abnormal Exit" ) == DR_YES ) {
			Cvar_Set( "com_abnormalExit", "1" );
		}
#endif
	}
}