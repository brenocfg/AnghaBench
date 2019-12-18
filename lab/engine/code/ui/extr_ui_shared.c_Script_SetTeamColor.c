#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec4_t ;
struct TYPE_5__ {int /*<<< orphan*/ * backColor; } ;
struct TYPE_6__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* getTeamColor ) (int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 TYPE_4__* DC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **) ; 

void Script_SetTeamColor(itemDef_t *item, char **args) {
  if (DC->getTeamColor) {
    int i;
    vec4_t color;
    DC->getTeamColor(&color);
    for (i = 0; i < 4; i++) {
      item->window.backColor[i] = color[i];
    }
  }
}