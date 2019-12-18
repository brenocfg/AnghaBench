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
struct TYPE_10__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_13__ {TYPE_2__* snap; } ;
struct TYPE_12__ {int /*<<< orphan*/  icon; } ;
struct TYPE_11__ {scalar_t__ gametype; } ;
struct TYPE_8__ {int* stats; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_RegisterItemVisuals (int) ; 
 scalar_t__ GT_CTF ; 
 size_t STAT_PERSISTANT_POWERUP ; 
 TYPE_6__ cg ; 
 TYPE_5__* cg_items ; 
 TYPE_4__ cgs ; 

__attribute__((used)) static void CG_DrawCTFPowerUp(rectDef_t *rect) {
	int		value;

	if (cgs.gametype < GT_CTF) {
		return;
	}
	value = cg.snap->ps.stats[STAT_PERSISTANT_POWERUP];
	if ( value ) {
		CG_RegisterItemVisuals( value );
		CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cg_items[ value ].icon );
	}
}