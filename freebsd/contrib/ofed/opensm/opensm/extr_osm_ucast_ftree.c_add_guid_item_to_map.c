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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  item; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ name_map_item_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;

/* Variables and functions */
 scalar_t__ cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static int add_guid_item_to_map(void *cxt, uint64_t guid, char *p)
{
	cl_qmap_t *map = cxt;
	name_map_item_t *item;
	name_map_item_t *inserted_item;

	item = malloc(sizeof(*item));
	if (!item)
		return -1;

	item->guid = guid;
	inserted_item = (name_map_item_t *) cl_qmap_insert(map, guid, &item->item);
	if (inserted_item != item)
                free(item);

	return 0;
}