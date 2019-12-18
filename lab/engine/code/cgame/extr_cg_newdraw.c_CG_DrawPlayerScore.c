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
struct TYPE_8__ {int w; scalar_t__ h; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  scalar_t__ qhandle_t ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_9__ {TYPE_2__* snap; } ;
struct TYPE_6__ {int* persistant; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawPic (scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CG_Text_Paint (scalar_t__,scalar_t__,float,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CG_Text_Width (char*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 size_t PERS_SCORE ; 
 TYPE_4__ cg ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CG_DrawPlayerScore( rectDef_t *rect, float scale, vec4_t color, qhandle_t shader, int textStyle ) {
  char num[16];
  int value = cg.snap->ps.persistant[PERS_SCORE];

	if (shader) {
		trap_R_SetColor( color );
		CG_DrawPic(rect->x, rect->y, rect->w, rect->h, shader);
		trap_R_SetColor( NULL );
	} else {
		Com_sprintf (num, sizeof(num), "%i", value);
		value = CG_Text_Width(num, scale, 0);
	  CG_Text_Paint(rect->x + (rect->w - value) / 2, rect->y + rect->h, scale, color, num, 0, 0, textStyle);
	}
}