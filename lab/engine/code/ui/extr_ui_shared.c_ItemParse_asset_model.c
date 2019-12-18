#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int angle; } ;
typedef  TYPE_1__ modelDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  asset; scalar_t__ typeData; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* registerModel ) (char const*) ;} ;

/* Variables and functions */
 TYPE_5__* DC ; 
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_2__*) ; 
 int /*<<< orphan*/  PC_String_Parse (int,char const**) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int rand () ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

qboolean ItemParse_asset_model( itemDef_t *item, int handle ) {
	const char *temp;
	modelDef_t *modelPtr;
	Item_ValidateTypeData(item);
	modelPtr = (modelDef_t*)item->typeData;

	if (!PC_String_Parse(handle, &temp)) {
		return qfalse;
	}
	item->asset = DC->registerModel(temp);
	modelPtr->angle = rand() % 360;
	return qtrue;
}