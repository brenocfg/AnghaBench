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
struct TYPE_6__ {int /*<<< orphan*/  ocs; int /*<<< orphan*/  node_group_lock; int /*<<< orphan*/  node_group_dir_list; int /*<<< orphan*/  display_name; } ;
typedef  TYPE_1__ ocs_sport_t ;
struct TYPE_7__ {int /*<<< orphan*/  node_group_list; int /*<<< orphan*/  instance_index; TYPE_1__* sport; } ;
typedef  TYPE_2__ ocs_node_group_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

void
ocs_node_group_dir_free(ocs_node_group_dir_t *node_group_dir)
{
	ocs_sport_t *sport;
	if (node_group_dir != NULL) {
		sport = node_group_dir->sport;
		ocs_log_debug(sport->ocs, "[%s] [%d] freeing node group directory\n", sport->display_name,
			node_group_dir->instance_index);
		ocs_lock(&sport->node_group_lock);
			if (!ocs_list_empty(&node_group_dir->node_group_list)) {
				ocs_log_test(sport->ocs, "[%s] WARNING: node group list not empty\n", sport->display_name);
			}
			ocs_list_remove(&sport->node_group_dir_list, node_group_dir);
		ocs_unlock(&sport->node_group_lock);
		ocs_free(sport->ocs, node_group_dir, sizeof(*node_group_dir));
	}
}