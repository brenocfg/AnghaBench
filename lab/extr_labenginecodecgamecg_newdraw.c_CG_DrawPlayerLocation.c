#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_10__ {scalar_t__ h; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_11__ {scalar_t__ location; } ;
typedef  TYPE_4__ clientInfo_t ;
struct TYPE_13__ {TYPE_2__* snap; } ;
struct TYPE_12__ {TYPE_4__* clientinfo; } ;
struct TYPE_8__ {size_t clientNum; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;

/* Variables and functions */
 char* CG_ConfigString (scalar_t__) ; 
 int /*<<< orphan*/  CG_Text_Paint (int /*<<< orphan*/ ,scalar_t__,float,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CS_LOCATIONS ; 
 TYPE_6__ cg ; 
 TYPE_5__ cgs ; 

__attribute__((used)) static void CG_DrawPlayerLocation( rectDef_t *rect, float scale, vec4_t color, int textStyle  ) {
	clientInfo_t *ci = &cgs.clientinfo[cg.snap->ps.clientNum];
  if (ci) {
		const char *p = CG_ConfigString(CS_LOCATIONS + ci->location);
		if (!p || !*p) {
			p = "unknown";
		}
    CG_Text_Paint(rect->x, rect->y + rect->h, scale, color, p, 0, 0, textStyle);
  }
}