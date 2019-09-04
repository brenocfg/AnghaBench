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
struct TYPE_5__ {char* pickup_sound; char* icon; char* precaches; char* sounds; int /*<<< orphan*/  move_type; int /*<<< orphan*/  giTag; int /*<<< orphan*/  giType; int /*<<< orphan*/  quantity; void* pickup_name; void** world_model; void* classname; } ;
typedef  TYPE_1__ gitem_t ;
struct TYPE_6__ {int /*<<< orphan*/  move_type; int /*<<< orphan*/  tag; int /*<<< orphan*/  type; int /*<<< orphan*/  quantity; int /*<<< orphan*/  name; int /*<<< orphan*/  model_name; int /*<<< orphan*/  classname; } ;
typedef  TYPE_2__ dm_item_args_t ;

/* Variables and functions */
 void* BG_NewString (int /*<<< orphan*/ ) ; 

void BG_CreateItem( dm_item_args_t* args, gitem_t* item ) {
	item->classname = BG_NewString( args->classname );
	item->pickup_sound = "sound/misc/w_pkup.wav";
	item->world_model[0] = BG_NewString( args->model_name );
	item->icon = "icons/iconh_green";
	item->pickup_name = BG_NewString( args->name );
	item->quantity = args->quantity;
	item->giType = args->type;
	item->giTag = args->tag;
	item->move_type = args->move_type;
	item->precaches = "";
	item->sounds = "";
}