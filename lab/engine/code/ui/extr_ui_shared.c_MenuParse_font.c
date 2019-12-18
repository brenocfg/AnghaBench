#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  font; } ;
typedef  TYPE_2__ menuDef_t ;
typedef  int /*<<< orphan*/  itemDef_t ;
struct TYPE_4__ {scalar_t__ fontRegistered; int /*<<< orphan*/  textFont; } ;
struct TYPE_6__ {TYPE_1__ Assets; int /*<<< orphan*/  (* registerFont ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_3__* DC ; 
 int /*<<< orphan*/  PC_String_Parse (int,int /*<<< orphan*/ *) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

qboolean MenuParse_font( itemDef_t *item, int handle ) {
	menuDef_t *menu = (menuDef_t*)item;
	if (!PC_String_Parse(handle, &menu->font)) {
		return qfalse;
	}
	if (!DC->Assets.fontRegistered) {
		DC->registerFont(menu->font, 48, &DC->Assets.textFont);
		DC->Assets.fontRegistered = qtrue;
	}
	return qtrue;
}