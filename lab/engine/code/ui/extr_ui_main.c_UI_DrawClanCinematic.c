#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec4_t ;
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
struct TYPE_7__ {int teamCount; TYPE_1__* teamList; } ;
struct TYPE_5__ {int cinematic; int /*<<< orphan*/  teamIcon; int /*<<< orphan*/  teamIcon_Metal; int /*<<< orphan*/  imageName; } ;

/* Variables and functions */
 int CIN_loop ; 
 int CIN_silent ; 
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  UI_DrawCinematic (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UI_TeamIndexFromName (int /*<<< orphan*/ ) ; 
 int trap_CIN_PlayCinematic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_CIN_RunCinematic (int) ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 
 TYPE_3__ uiInfo ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UI_DrawClanCinematic(rectDef_t *rect, float scale, vec4_t color) {
  int i;
  i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_teamName"));
  if (i >= 0 && i < uiInfo.teamCount) {

		if (uiInfo.teamList[i].cinematic >= -2) {
			if (uiInfo.teamList[i].cinematic == -1) {
				uiInfo.teamList[i].cinematic = trap_CIN_PlayCinematic(va("%s.roq", uiInfo.teamList[i].imageName), 0, 0, 0, 0, (CIN_loop | CIN_silent) );
			}
			if (uiInfo.teamList[i].cinematic >= 0) {
			  trap_CIN_RunCinematic(uiInfo.teamList[i].cinematic);
				UI_DrawCinematic(uiInfo.teamList[i].cinematic, rect->x, rect->y, rect->w, rect->h);
			} else {
			  	trap_R_SetColor( color );
				UI_DrawHandlePic( rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon_Metal);
				trap_R_SetColor(NULL);
				uiInfo.teamList[i].cinematic = -2;
			}
		} else {
	  	trap_R_SetColor( color );
			UI_DrawHandlePic( rect->x, rect->y, rect->w, rect->h, uiInfo.teamList[i].teamIcon);
			trap_R_SetColor(NULL);
		}
	}

}