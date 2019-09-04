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

void G_RemapTeamShaders( void ) {
#ifdef MISSIONPACK
	char string[1024];
	float f = level.time * 0.001;
	Com_sprintf( string, sizeof(string), "team_icon/%s_red", g_redteam.string );
	AddRemap("textures/ctf2/redteam01", string, f); 
	AddRemap("textures/ctf2/redteam02", string, f); 
	Com_sprintf( string, sizeof(string), "team_icon/%s_blue", g_blueteam.string );
	AddRemap("textures/ctf2/blueteam01", string, f); 
	AddRemap("textures/ctf2/blueteam02", string, f); 
	trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
#endif
}