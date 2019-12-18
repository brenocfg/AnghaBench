#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec4_t ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  scalar_t__ qhandle_t ;
typedef  int /*<<< orphan*/  gitem_t ;
struct TYPE_7__ {scalar_t__* flagShaders; scalar_t__ redCubeIcon; } ;
struct TYPE_9__ {scalar_t__ gametype; int redflag; TYPE_2__ media; } ;
struct TYPE_6__ {int member_0; int member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BG_FindItemForPowerup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 int /*<<< orphan*/  PW_REDFLAG ; 
 TYPE_4__ cgs ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CG_DrawRedFlagStatus(rectDef_t *rect, qhandle_t shader) {
	if (cgs.gametype != GT_CTF && cgs.gametype != GT_1FCTF) {
		if (cgs.gametype == GT_HARVESTER) {
		  vec4_t color = {1, 0, 0, 1};
		  trap_R_SetColor(color);
	    CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cgs.media.redCubeIcon );
		  trap_R_SetColor(NULL);
		}
		return;
	}
  if (shader) {
		CG_DrawPic( rect->x, rect->y, rect->w, rect->h, shader );
  } else {
	  gitem_t *item = BG_FindItemForPowerup( PW_REDFLAG );
    if (item) {
		  vec4_t color = {1, 0, 0, 1};
		  trap_R_SetColor(color);
	    if( cgs.redflag >= 0 && cgs.redflag <= 2) {
		    CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cgs.media.flagShaders[cgs.redflag] );
			} else {
		    CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cgs.media.flagShaders[0] );
			}
		  trap_R_SetColor(NULL);
	  }
  }
}