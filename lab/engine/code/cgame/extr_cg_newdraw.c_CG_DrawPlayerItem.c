#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_11__ {int time; TYPE_2__* snap; } ;
struct TYPE_10__ {int /*<<< orphan*/ * models; int /*<<< orphan*/  icon; } ;
struct TYPE_7__ {int* stats; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw3DModel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_RegisterItemVisuals (int) ; 
 size_t STAT_HOLDABLE_ITEM ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 size_t YAW ; 
 TYPE_5__ cg ; 
 TYPE_4__* cg_items ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static void CG_DrawPlayerItem( rectDef_t *rect, float scale, qboolean draw2D) {
	int		value;
  vec3_t origin, angles;

	value = cg.snap->ps.stats[STAT_HOLDABLE_ITEM];
	if ( value ) {
		CG_RegisterItemVisuals( value );

		if (qtrue) {
		  CG_RegisterItemVisuals( value );
		  CG_DrawPic( rect->x, rect->y, rect->w, rect->h, cg_items[ value ].icon );
		} else {
 			VectorClear( angles );
			origin[0] = 90;
  		origin[1] = 0;
   		origin[2] = -10;
  		angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0;
			CG_Draw3DModel(rect->x, rect->y, rect->w, rect->h, cg_items[ value ].models[0], 0, origin, angles );
		}
	}

}