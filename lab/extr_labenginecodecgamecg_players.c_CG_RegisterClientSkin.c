#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_5__ {void* headSkin; void* torsoSkin; void* legsSkin; } ;
typedef  TYPE_1__ clientInfo_t ;

/* Variables and functions */
 scalar_t__ CG_FindClientHeadFile (char*,int,TYPE_1__*,char const*,char const*,char const*,char*,char*) ; 
 scalar_t__ CG_FindClientModelFile (char*,int,TYPE_1__*,char const*,char const*,char const*,char*,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 void* trap_R_RegisterSkin (char*) ; 

__attribute__((used)) static qboolean	CG_RegisterClientSkin( clientInfo_t *ci, const char *teamName, const char *modelName, const char *skinName, const char *headModelName, const char *headSkinName ) {
	char filename[MAX_QPATH];

	/*
	Com_sprintf( filename, sizeof( filename ), "models/players/%s/%slower_%s.skin", modelName, teamName, skinName );
	ci->legsSkin = trap_R_RegisterSkin( filename );
	if (!ci->legsSkin) {
		Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/%slower_%s.skin", modelName, teamName, skinName );
		ci->legsSkin = trap_R_RegisterSkin( filename );
		if (!ci->legsSkin) {
			Com_Printf( "Leg skin load failure: %s\n", filename );
		}
	}


	Com_sprintf( filename, sizeof( filename ), "models/players/%s/%supper_%s.skin", modelName, teamName, skinName );
	ci->torsoSkin = trap_R_RegisterSkin( filename );
	if (!ci->torsoSkin) {
		Com_sprintf( filename, sizeof( filename ), "models/players/characters/%s/%supper_%s.skin", modelName, teamName, skinName );
		ci->torsoSkin = trap_R_RegisterSkin( filename );
		if (!ci->torsoSkin) {
			Com_Printf( "Torso skin load failure: %s\n", filename );
		}
	}
	*/
	if ( CG_FindClientModelFile( filename, sizeof(filename), ci, teamName, modelName, skinName, "lower", "skin" ) ) {
		ci->legsSkin = trap_R_RegisterSkin( filename );
	}
	if (!ci->legsSkin) {
		Com_Printf( "Leg skin load failure: %s\n", filename );
	}

	if ( CG_FindClientModelFile( filename, sizeof(filename), ci, teamName, modelName, skinName, "upper", "skin" ) ) {
		ci->torsoSkin = trap_R_RegisterSkin( filename );
	}
	if (!ci->torsoSkin) {
		Com_Printf( "Torso skin load failure: %s\n", filename );
	}

	if ( CG_FindClientHeadFile( filename, sizeof(filename), ci, teamName, headModelName, headSkinName, "head", "skin" ) ) {
		ci->headSkin = trap_R_RegisterSkin( filename );
	}
	if (!ci->headSkin) {
		Com_Printf( "Head skin load failure: %s\n", filename );
	}

	// if any skins failed to load
	if ( !ci->legsSkin || !ci->torsoSkin || !ci->headSkin ) {
		return qfalse;
	}
	return qtrue;
}