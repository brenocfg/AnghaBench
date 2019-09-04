#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {int areanum; struct TYPE_8__* next_area; } ;
typedef  TYPE_1__ aas_link_t ;
struct TYPE_9__ {int frames; } ;
typedef  TYPE_2__ aas_clientmove_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 scalar_t__ AAS_AreaJumpPad (int) ; 
 float AAS_AreaVolume (int) ; 
 int /*<<< orphan*/  AAS_ClientMovementHitBBox (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAS_GetJumpPadInfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AAS_LinkEntityClientBBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int AAS_NextBSPEntity (int) ; 
 int /*<<< orphan*/  AAS_UnlinkFromAreas (TYPE_1__*) ; 
 int /*<<< orphan*/  AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int LibVarValue (char*,char*) ; 
 int MAX_EPAIRKEY ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

int AAS_BestReachableFromJumpPadArea(vec3_t origin, vec3_t mins, vec3_t maxs)
{
	int ent, bot_visualizejumppads, bestareanum;
	float volume, bestareavolume;
	vec3_t areastart, cmdmove, bboxmins, bboxmaxs;
	vec3_t absmins, absmaxs, velocity;
	aas_clientmove_t move;
	aas_link_t *areas, *link;
	char classname[MAX_EPAIRKEY];

#ifdef BSPC
	bot_visualizejumppads = 0;
#else
	bot_visualizejumppads = LibVarValue("bot_visualizejumppads", "0");
#endif
	VectorAdd(origin, mins, bboxmins);
	VectorAdd(origin, maxs, bboxmaxs);
	for (ent = AAS_NextBSPEntity(0); ent; ent = AAS_NextBSPEntity(ent))
	{
		if (!AAS_ValueForBSPEpairKey(ent, "classname", classname, MAX_EPAIRKEY)) continue;
		if (strcmp(classname, "trigger_push")) continue;
		//
		if (!AAS_GetJumpPadInfo(ent, areastart, absmins, absmaxs, velocity)) continue;
		//get the areas the jump pad brush is in
		areas = AAS_LinkEntityClientBBox(absmins, absmaxs, -1, PRESENCE_CROUCH);
		for (link = areas; link; link = link->next_area)
		{
			if (AAS_AreaJumpPad(link->areanum)) break;
		} //end for
		if (!link)
		{
			botimport.Print(PRT_MESSAGE, "trigger_push not in any jump pad area\n");
			AAS_UnlinkFromAreas(areas);
			continue;
		} //end if
		//
		//botimport.Print(PRT_MESSAGE, "found a trigger_push with velocity %f %f %f\n", velocity[0], velocity[1], velocity[2]);
		//
		VectorSet(cmdmove, 0, 0, 0);
		Com_Memset(&move, 0, sizeof(aas_clientmove_t));
		AAS_ClientMovementHitBBox(&move, -1, areastart, PRESENCE_NORMAL, qfalse,
								velocity, cmdmove, 0, 30, 0.1f, bboxmins, bboxmaxs, bot_visualizejumppads);
		if (move.frames < 30)
		{
			bestareanum = 0;
			bestareavolume = 0;
			for (link = areas; link; link = link->next_area)
			{
				if (!AAS_AreaJumpPad(link->areanum)) continue;
				volume = AAS_AreaVolume(link->areanum);
				if (volume >= bestareavolume)
				{
					bestareanum = link->areanum;
					bestareavolume = volume;
				} //end if
			} //end if
			AAS_UnlinkFromAreas(areas);
			return bestareanum;
		} //end if
		AAS_UnlinkFromAreas(areas);
	} //end for
	return 0;
}