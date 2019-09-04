#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_1__*) ; 
 int /*<<< orphan*/  PC_Int_Parse (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ItemParse_type( itemDef_t *item, int handle ) {
	if (!PC_Int_Parse(handle, &item->type)) {
		return qfalse;
	}
	Item_ValidateTypeData(item);
	return qtrue;
}