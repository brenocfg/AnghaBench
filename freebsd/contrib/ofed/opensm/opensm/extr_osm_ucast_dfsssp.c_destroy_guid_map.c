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
struct TYPE_3__ {int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ name_map_item_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;

/* Variables and functions */
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void destroy_guid_map(cl_qmap_t * guid_tbl)
{
	name_map_item_t *p_guid = NULL, *p_next_guid = NULL;

	p_next_guid = (name_map_item_t *) cl_qmap_head(guid_tbl);
	while (p_next_guid != (name_map_item_t *) cl_qmap_end(guid_tbl)) {
		p_guid = p_next_guid;
		p_next_guid = (name_map_item_t *) cl_qmap_next(&p_guid->item);
		free(p_guid);
	}
	cl_qmap_remove_all(guid_tbl);
}