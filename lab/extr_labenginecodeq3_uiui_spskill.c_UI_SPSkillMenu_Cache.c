#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* silenceSound; void* nightmareSound; void** skillpics; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_BACK ; 
 int /*<<< orphan*/  ART_BACK_FOCUS ; 
 int /*<<< orphan*/  ART_FIGHT ; 
 int /*<<< orphan*/  ART_FIGHT_FOCUS ; 
 int /*<<< orphan*/  ART_FRAME ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE1 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE2 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE3 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE4 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE5 ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_1__ skillMenuInfo ; 
 void* trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 
 void* trap_S_RegisterSound (char*,int /*<<< orphan*/ ) ; 

void UI_SPSkillMenu_Cache( void ) {
	trap_R_RegisterShaderNoMip( ART_FRAME );
	trap_R_RegisterShaderNoMip( ART_BACK );
	trap_R_RegisterShaderNoMip( ART_BACK_FOCUS );
	trap_R_RegisterShaderNoMip( ART_FIGHT );
	trap_R_RegisterShaderNoMip( ART_FIGHT_FOCUS );
	skillMenuInfo.skillpics[0] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE1 );
	skillMenuInfo.skillpics[1] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE2 );
	skillMenuInfo.skillpics[2] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE3 );
	skillMenuInfo.skillpics[3] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE4 );
	skillMenuInfo.skillpics[4] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE5 );

	skillMenuInfo.nightmareSound = trap_S_RegisterSound( "sound/misc/nightmare.wav", qfalse );
	skillMenuInfo.silenceSound = trap_S_RegisterSound( "sound/misc/silence.wav", qfalse );
}