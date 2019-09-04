#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Text_Paint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int numSkillLevels ; 
 int /*<<< orphan*/ * skillLevels ; 
 int trap_Cvar_VariableValue (char*) ; 

__attribute__((used)) static void UI_DrawSkill(rectDef_t *rect, float scale, vec4_t color, int textStyle) {
  int i;
	i = trap_Cvar_VariableValue( "g_spSkill" );
  if (i < 1 || i > numSkillLevels) {
    i = 1;
  }
  Text_Paint(rect->x, rect->y, scale, color, skillLevels[i-1],0, 0, textStyle);
}