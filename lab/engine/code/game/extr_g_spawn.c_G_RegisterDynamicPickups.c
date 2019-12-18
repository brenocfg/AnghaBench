#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BG_FindItemByClassName (char*) ; 
 int /*<<< orphan*/  RegisterItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmlab_read_dynamic_item_name (int,char*) ; 
 int dmlab_register_dynamic_items () ; 

void G_RegisterDynamicPickups( void ) {
	char classname[256];
	int i, item_count = dmlab_register_dynamic_items();
	for (i = 0; i < item_count; ++i) {
		dmlab_read_dynamic_item_name( i, classname );
		RegisterItem( BG_FindItemByClassName( classname ) );
	}
}