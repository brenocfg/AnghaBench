#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_4__ {scalar_t__ h; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Text_Paint (int /*<<< orphan*/ ,scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ cg_redTeamName ; 

__attribute__((used)) static void CG_DrawRedName(rectDef_t *rect, float scale, vec4_t color, int textStyle ) {
  CG_Text_Paint(rect->x, rect->y + rect->h, scale, color, cg_redTeamName.string , 0, 0, textStyle);
}