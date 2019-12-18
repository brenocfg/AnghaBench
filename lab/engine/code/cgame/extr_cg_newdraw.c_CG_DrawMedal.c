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
typedef  double* vec4_t ;
struct TYPE_5__ {float accuracy; float assistCount; float defendCount; float excellentCount; float impressiveCount; float perfect; float guantletCount; float captures; } ;
typedef  TYPE_1__ score_t ;
struct TYPE_6__ {float w; scalar_t__ h; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_7__ {size_t selectedScore; TYPE_1__* scores; } ;

/* Variables and functions */
#define  CG_ACCURACY 135 
#define  CG_ASSISTS 134 
#define  CG_CAPTURES 133 
#define  CG_DEFEND 132 
 int /*<<< orphan*/  CG_DrawPic (scalar_t__,scalar_t__,float,scalar_t__,int /*<<< orphan*/ ) ; 
#define  CG_EXCELLENT 131 
#define  CG_GAUNTLET 130 
#define  CG_IMPRESSIVE 129 
#define  CG_PERFECT 128 
 int /*<<< orphan*/  CG_Text_Paint (scalar_t__,scalar_t__,float,double*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float CG_Text_Width (char*,float,int /*<<< orphan*/ ) ; 
 TYPE_3__ cg ; 
 int /*<<< orphan*/  trap_R_SetColor (double*) ; 
 char* va (char*,int) ; 

void CG_DrawMedal(int ownerDraw, rectDef_t *rect, float scale, vec4_t color, qhandle_t shader) {
	score_t *score = &cg.scores[cg.selectedScore];
	float value = 0;
	char *text = NULL;
	color[3] = 0.25;

	switch (ownerDraw) {
		case CG_ACCURACY:
			value = score->accuracy;
			break;
		case CG_ASSISTS:
			value = score->assistCount;
			break;
		case CG_DEFEND:
			value = score->defendCount;
			break;
		case CG_EXCELLENT:
			value = score->excellentCount;
			break;
		case CG_IMPRESSIVE:
			value = score->impressiveCount;
			break;
		case CG_PERFECT:
			value = score->perfect;
			break;
		case CG_GAUNTLET:
			value = score->guantletCount;
			break;
		case CG_CAPTURES:
			value = score->captures;
			break;
	}

	if (value > 0) {
		if (ownerDraw != CG_PERFECT) {
			if (ownerDraw == CG_ACCURACY) {
				text = va("%i%%", (int)value);
				if (value > 50) {
					color[3] = 1.0;
				}
			} else {
				text = va("%i", (int)value);
				color[3] = 1.0;
			}
		} else {
			if (value) {
				color[3] = 1.0;
			}
			text = "Wow";
		}
	}

	trap_R_SetColor(color);
	CG_DrawPic( rect->x, rect->y, rect->w, rect->h, shader );

	if (text) {
		color[3] = 1.0;
		value = CG_Text_Width(text, scale, 0);
		CG_Text_Paint(rect->x + (rect->w - value) / 2, rect->y + rect->h + 10 , scale, color, text, 0, 0, 0);
	}
	trap_R_SetColor(NULL);

}