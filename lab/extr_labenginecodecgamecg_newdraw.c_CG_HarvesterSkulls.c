#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int* vec3_t ;
struct TYPE_13__ {int x; int w; scalar_t__ y; scalar_t__ h; } ;
typedef  TYPE_4__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_17__ {int time; TYPE_2__* snap; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_12__ {int /*<<< orphan*/  blueCubeIcon; int /*<<< orphan*/  redCubeIcon; int /*<<< orphan*/  blueCubeModel; int /*<<< orphan*/  redCubeModel; } ;
struct TYPE_14__ {scalar_t__ gametype; TYPE_3__ media; } ;
struct TYPE_10__ {int generic1; scalar_t__* persistant; } ;
struct TYPE_11__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw3DModel (int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  CG_DrawPic (int,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Text_Paint (int,scalar_t__,float,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CG_Text_Width (char*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 scalar_t__ GT_HARVESTER ; 
 size_t PERS_TEAM ; 
 scalar_t__ TEAM_BLUE ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 size_t YAW ; 
 TYPE_8__ cg ; 
 TYPE_7__ cg_draw3dIcons ; 
 TYPE_6__ cg_drawIcons ; 
 TYPE_5__ cgs ; 

__attribute__((used)) static void CG_HarvesterSkulls(rectDef_t *rect, float scale, vec4_t color, qboolean force2D, int textStyle ) {
	char num[16];
	vec3_t origin, angles;
	qhandle_t handle;
	int value = cg.snap->ps.generic1;

	if (cgs.gametype != GT_HARVESTER) {
		return;
	}

	if( value > 99 ) {
		value = 99;
	}

	Com_sprintf (num, sizeof(num), "%i", value);
	value = CG_Text_Width(num, scale, 0);
	CG_Text_Paint(rect->x + (rect->w - value), rect->y + rect->h, scale, color, num, 0, 0, textStyle);

	if (cg_drawIcons.integer) {
		if (!force2D && cg_draw3dIcons.integer) {
			VectorClear(angles);
			origin[0] = 90;
			origin[1] = 0;
			origin[2] = -10;
			angles[YAW] = ( cg.time & 2047 ) * 360 / 2048.0;
			if( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
				handle = cgs.media.redCubeModel;
			} else {
				handle = cgs.media.blueCubeModel;
			}
			CG_Draw3DModel( rect->x, rect->y, 35, 35, handle, 0, origin, angles );
		} else {
			if( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE ) {
				handle = cgs.media.redCubeIcon;
			} else {
				handle = cgs.media.blueCubeIcon;
			}
			CG_DrawPic( rect->x + 3, rect->y + 16, 20, 20, handle );
		}
	}
}