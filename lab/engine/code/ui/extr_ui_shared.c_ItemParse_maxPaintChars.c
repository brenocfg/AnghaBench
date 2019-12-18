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
struct TYPE_5__ {scalar_t__ typeData; } ;
typedef  TYPE_1__ itemDef_t ;
struct TYPE_6__ {int maxPaintChars; } ;
typedef  TYPE_2__ editFieldDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_1__*) ; 
 int /*<<< orphan*/  PC_Int_Parse (int,int*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ItemParse_maxPaintChars( itemDef_t *item, int handle ) {
	editFieldDef_t *editPtr;
	int maxChars;

	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;

	if (!PC_Int_Parse(handle, &maxChars)) {
		return qfalse;
	}
	editPtr = (editFieldDef_t*)item->typeData;
	editPtr->maxPaintChars = maxChars;
	return qtrue;
}