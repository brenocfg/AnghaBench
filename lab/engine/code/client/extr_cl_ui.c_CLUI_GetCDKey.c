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

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (char*,int /*<<< orphan*/ *,int) ; 
 char* Cvar_VariableString (char*) ; 
 scalar_t__ UI_usesUniqueCDKey () ; 
 int /*<<< orphan*/ * cl_cdkey ; 

__attribute__((used)) static void CLUI_GetCDKey( char *buf, int buflen ) {
#ifndef STANDALONE
	const char *gamedir;
	gamedir = Cvar_VariableString( "fs_game" );
	if (UI_usesUniqueCDKey() && gamedir[0] != 0) {
		Com_Memcpy( buf, &cl_cdkey[16], 16);
		buf[16] = 0;
	} else {
		Com_Memcpy( buf, cl_cdkey, 16);
		buf[16] = 0;
	}
#else
	*buf = 0;
#endif
}