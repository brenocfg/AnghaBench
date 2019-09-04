#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * classname; } ;
typedef  TYPE_1__ gitem_t ;
struct TYPE_7__ {int /*<<< orphan*/  move_type; int /*<<< orphan*/  tag; int /*<<< orphan*/  type; int /*<<< orphan*/  quantity; int /*<<< orphan*/  model_name; int /*<<< orphan*/  classname; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ dm_item_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BG_CreateItem (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_ITEMS ; 
 int bg_defaultNumItems ; 
 TYPE_1__* bg_itemlist ; 
 int bg_numItems ; 
 scalar_t__ dmlab_item (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmlab_itemcount () ; 

void BG_UpdateItems( void ) {
	int i;
	dm_item_args_t dm_args;
	gitem_t* item;

	// Calculate how many custom items we currently have. We assume that the item
	// order is deterministic.
	int num_custom_items = bg_numItems - bg_defaultNumItems;

	if ( num_custom_items != dmlab_itemcount( ) ) {
		for ( i = num_custom_items; i < dmlab_itemcount( ); ++i ) {

			// Check we have enough space to allocate the new item.
			// Make sure we always have an end of list marks (null item).
			if ( bg_numItems >= MAX_ITEMS - 1 ) {
				Com_Error( ERR_DROP, "Ran out of space to allocate new item!" );
				break;
			}

			if (dmlab_item(
					i, dm_args.name, sizeof(dm_args.name),
					dm_args.classname, sizeof(dm_args.classname),
					dm_args.model_name, sizeof(dm_args.model_name),
					&dm_args.quantity, &dm_args.type, &dm_args.tag,
					&dm_args.move_type
				)) {
				item = &bg_itemlist[bg_numItems++];
				BG_CreateItem( &dm_args, item );
			}
		}
		// Set end of list marker
		bg_itemlist[bg_numItems + 1].classname = NULL;
	}
}