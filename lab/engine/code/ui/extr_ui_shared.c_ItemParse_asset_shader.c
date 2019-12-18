#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  asset; } ;
typedef  TYPE_1__ itemDef_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* registerShaderNoMip ) (char const*) ;} ;

/* Variables and functions */
 TYPE_3__* DC ; 
 int /*<<< orphan*/  PC_String_Parse (int,char const**) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

qboolean ItemParse_asset_shader( itemDef_t *item, int handle ) {
	const char *temp;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->asset = DC->registerShaderNoMip(temp);
	return qtrue;
}