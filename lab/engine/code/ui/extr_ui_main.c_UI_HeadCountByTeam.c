#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int characterCount; int teamCount; int aliasCount; TYPE_3__* characterList; TYPE_2__* aliasList; TYPE_1__* teamList; } ;
struct TYPE_7__ {int reference; scalar_t__ active; int headImage; int /*<<< orphan*/ * name; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ai; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** teamMembers; int /*<<< orphan*/  teamName; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TEAM_MEMBERS ; 
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 int UI_TeamIndexFromName (int /*<<< orphan*/ ) ; 
 scalar_t__ UI_hasSkinForBase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 void* qtrue ; 
 TYPE_4__ uiInfo ; 

__attribute__((used)) static int UI_HeadCountByTeam(void) {
	static int init = 0;
	int i, j, k, c, tIndex;
	
	c = 0;
	if (!init) {
		for (i = 0; i < uiInfo.characterCount; i++) {
			uiInfo.characterList[i].reference = 0;
			for (j = 0; j < uiInfo.teamCount; j++) {
			  if (UI_hasSkinForBase(uiInfo.characterList[i].base, uiInfo.teamList[j].teamName)) {
					uiInfo.characterList[i].reference |= (1<<j);
			  }
			}
		}
		init = 1;
	}

	tIndex = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));

	// do names
	for (i = 0; i < uiInfo.characterCount; i++) {
		uiInfo.characterList[i].active = qfalse;
		for(j = 0; j < TEAM_MEMBERS; j++) {
			if (uiInfo.teamList[tIndex].teamMembers[j] != NULL) {
				if (uiInfo.characterList[i].reference&(1<<tIndex)) {// && Q_stricmp(uiInfo.teamList[tIndex].teamMembers[j], uiInfo.characterList[i].name)==0) {
					uiInfo.characterList[i].active = qtrue;
					c++;
					break;
				}
			}
		}
	}

	// and then aliases
	for(j = 0; j < TEAM_MEMBERS; j++) {
		for(k = 0; k < uiInfo.aliasCount; k++) {
			if (uiInfo.aliasList[k].name != NULL) {
				if (Q_stricmp(uiInfo.teamList[tIndex].teamMembers[j], uiInfo.aliasList[k].name)==0) {
					for (i = 0; i < uiInfo.characterCount; i++) {
						if (uiInfo.characterList[i].headImage != -1 && uiInfo.characterList[i].reference&(1<<tIndex) && Q_stricmp(uiInfo.aliasList[k].ai, uiInfo.characterList[i].name)==0) {
							if (uiInfo.characterList[i].active == qfalse) {
								uiInfo.characterList[i].active = qtrue;
								c++;
							}
							break;
						}
					}
				}
			}
		}
	}
	return c;
}