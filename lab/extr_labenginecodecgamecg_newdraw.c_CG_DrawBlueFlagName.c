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
struct TYPE_6__ {scalar_t__ h; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
struct TYPE_7__ {int maxclients; TYPE_1__* clientinfo; } ;
struct TYPE_5__ {scalar_t__ team; int powerups; int /*<<< orphan*/  name; scalar_t__ infoValid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Text_Paint (int /*<<< orphan*/ ,scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int PW_BLUEFLAG ; 
 scalar_t__ TEAM_RED ; 
 TYPE_3__ cgs ; 

__attribute__((used)) static void CG_DrawBlueFlagName(rectDef_t *rect, float scale, vec4_t color, int textStyle ) {
  int i;
  for ( i = 0 ; i < cgs.maxclients ; i++ ) {
	  if ( cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_RED  && cgs.clientinfo[i].powerups & ( 1<< PW_BLUEFLAG )) {
      CG_Text_Paint(rect->x, rect->y + rect->h, scale, color, cgs.clientinfo[i].name, 0, 0, textStyle);
      return;
    }
  }
}