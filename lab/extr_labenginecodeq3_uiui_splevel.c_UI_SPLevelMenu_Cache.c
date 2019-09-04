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
struct TYPE_2__ {void** levelCompletePic; void* levelFocusPic; void* levelSelectedPic; int /*<<< orphan*/ * awardSounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_ARROW ; 
 int /*<<< orphan*/  ART_ARROW_FOCUS ; 
 int /*<<< orphan*/  ART_BACK0 ; 
 int /*<<< orphan*/  ART_BACK1 ; 
 int /*<<< orphan*/  ART_CUSTOM0 ; 
 int /*<<< orphan*/  ART_CUSTOM1 ; 
 int /*<<< orphan*/  ART_FIGHT0 ; 
 int /*<<< orphan*/  ART_FIGHT1 ; 
 int /*<<< orphan*/  ART_LEVELFRAME_FOCUS ; 
 int /*<<< orphan*/  ART_LEVELFRAME_SELECTED ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE1 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE2 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE3 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE4 ; 
 int /*<<< orphan*/  ART_MAP_COMPLETE5 ; 
 int /*<<< orphan*/  ART_MAP_UNKNOWN ; 
 int /*<<< orphan*/  ART_RESET0 ; 
 int /*<<< orphan*/  ART_RESET1 ; 
 TYPE_1__ levelMenuInfo ; 
 int /*<<< orphan*/  qfalse ; 
 void* trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_S_RegisterSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ui_medalPicNames ; 
 int /*<<< orphan*/ * ui_medalSounds ; 

void UI_SPLevelMenu_Cache( void ) {
	int				n;

	trap_R_RegisterShaderNoMip( ART_LEVELFRAME_FOCUS );
	trap_R_RegisterShaderNoMip( ART_LEVELFRAME_SELECTED );
	trap_R_RegisterShaderNoMip( ART_ARROW );
	trap_R_RegisterShaderNoMip( ART_ARROW_FOCUS );
	trap_R_RegisterShaderNoMip( ART_MAP_UNKNOWN );
	trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE1 );
	trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE2 );
	trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE3 );
	trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE4 );
	trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE5 );
	trap_R_RegisterShaderNoMip( ART_BACK0 );
	trap_R_RegisterShaderNoMip( ART_BACK1 );
	trap_R_RegisterShaderNoMip( ART_FIGHT0 );
	trap_R_RegisterShaderNoMip( ART_FIGHT1 );
	trap_R_RegisterShaderNoMip( ART_RESET0 );
	trap_R_RegisterShaderNoMip( ART_RESET1 );
	trap_R_RegisterShaderNoMip( ART_CUSTOM0 );
	trap_R_RegisterShaderNoMip( ART_CUSTOM1 );

	for( n = 0; n < 6; n++ ) {
		trap_R_RegisterShaderNoMip( ui_medalPicNames[n] );
		levelMenuInfo.awardSounds[n] = trap_S_RegisterSound( ui_medalSounds[n], qfalse );
	}

	levelMenuInfo.levelSelectedPic = trap_R_RegisterShaderNoMip( ART_LEVELFRAME_SELECTED );
	levelMenuInfo.levelFocusPic = trap_R_RegisterShaderNoMip( ART_LEVELFRAME_FOCUS );
	levelMenuInfo.levelCompletePic[0] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE1 );
	levelMenuInfo.levelCompletePic[1] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE2 );
	levelMenuInfo.levelCompletePic[2] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE3 );
	levelMenuInfo.levelCompletePic[3] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE4 );
	levelMenuInfo.levelCompletePic[4] = trap_R_RegisterShaderNoMip( ART_MAP_COMPLETE5 );
}