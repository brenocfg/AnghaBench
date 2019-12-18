#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  notselectable; } ;
typedef  TYPE_1__ listBoxDef_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ typeData; } ;
typedef  TYPE_2__ itemDef_t ;

/* Variables and functions */
 scalar_t__ ITEM_TYPE_LISTBOX ; 
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_2__*) ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ItemParse_notselectable( itemDef_t *item, int handle ) {
	listBoxDef_t *listPtr;
	Item_ValidateTypeData(item);
	listPtr = (listBoxDef_t*)item->typeData;
	if (item->type == ITEM_TYPE_LISTBOX && listPtr) {
		listPtr->notselectable = qtrue;
	}
	return qtrue;
}