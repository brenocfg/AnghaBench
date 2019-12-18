#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nn_map_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ name_map_item_t ;

/* Variables and functions */
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_nodedesc (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char *remap_node_name(nn_map_t * map, uint64_t target_guid, char *nodedesc)
{
	char *rc = NULL;
	name_map_item_t *item = NULL;

	if (!map)
		goto done;

	item = (name_map_item_t *) cl_qmap_get(map, target_guid);
	if (item != (name_map_item_t *) cl_qmap_end(map))
		rc = strdup(item->name);

done:
	if (rc == NULL)
		rc = strdup(clean_nodedesc(nodedesc));
	return (rc);
}