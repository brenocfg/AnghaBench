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
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_5__ {scalar_t__ h; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ clientInfo_t ;
struct TYPE_7__ {int currentVoiceClient; TYPE_2__* clientinfo; } ;

/* Variables and functions */
 size_t CG_GetSelectedPlayer () ; 
 int /*<<< orphan*/  CG_Text_Paint (int /*<<< orphan*/ ,scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ cgs ; 
 int* sortedTeamPlayers ; 

__attribute__((used)) static void CG_DrawSelectedPlayerName( rectDef_t *rect, float scale, vec4_t color, qboolean voice, int textStyle) {
	clientInfo_t *ci;
  ci = cgs.clientinfo + ((voice) ? cgs.currentVoiceClient : sortedTeamPlayers[CG_GetSelectedPlayer()]);
  if (ci) {
    CG_Text_Paint(rect->x, rect->y + rect->h, scale, color, ci->name, 0, 0, textStyle);
  }
}