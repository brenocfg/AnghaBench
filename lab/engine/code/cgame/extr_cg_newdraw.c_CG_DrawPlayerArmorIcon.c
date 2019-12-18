#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_10__ {int h; int /*<<< orphan*/  w; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_15__ {int time; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_9__ {int /*<<< orphan*/  armorModel; int /*<<< orphan*/  armorIcon; } ;
struct TYPE_11__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw3DModel (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 size_t YAW ; 
 TYPE_7__ cg ; 
 TYPE_6__ cg_draw3dIcons ; 
 TYPE_5__ cg_drawIcons ; 
 TYPE_4__ cg_drawStatus ; 
 TYPE_3__ cgs ; 

__attribute__((used)) static void CG_DrawPlayerArmorIcon( rectDef_t *rect, qboolean draw2D ) {
	vec3_t		angles;
	vec3_t		origin;

	if ( cg_drawStatus.integer == 0 ) {
		return;
	}

	if ( draw2D || ( !cg_draw3dIcons.integer && cg_drawIcons.integer) ) {
		CG_DrawPic( rect->x, rect->y + rect->h/2 + 1, rect->w, rect->h, cgs.media.armorIcon );
	} else if (cg_draw3dIcons.integer) {
		VectorClear( angles );
		origin[0] = 90;
		origin[1] = 0;
		origin[2] = -10;
		angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0f;
		CG_Draw3DModel( rect->x, rect->y, rect->w, rect->h, cgs.media.armorModel, 0, origin, angles );
	}
}