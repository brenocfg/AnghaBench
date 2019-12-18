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
struct TYPE_3__ {int /*<<< orphan*/  registered; } ;
typedef  TYPE_1__ itemInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BG_InitItemList () ; 
 int /*<<< orphan*/  BG_UpdateItems () ; 
 int /*<<< orphan*/  CG_RegisterItemVisuals (int) ; 
 int bg_defaultNumItems ; 
 int bg_numItems ; 
 TYPE_1__* cg_items ; 
 int /*<<< orphan*/  qfalse ; 

void CG_UpdateCustomItems( void ) {
	int i;

	// Pull all the custom items back down.
	BG_InitItemList();
	BG_UpdateItems();

	// Associate each custom item with its rendering data.
	for ( i = bg_defaultNumItems ; i < bg_numItems ; i++ ) {
		itemInfo_t *itemInfo = &cg_items[ i ];
		itemInfo->registered = qfalse;

		CG_RegisterItemVisuals( i );
	}
}