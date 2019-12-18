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
struct guids {scalar_t__ before; scalar_t__ after; int /*<<< orphan*/  found; } ;
struct TYPE_4__ {scalar_t__ guid; scalar_t__ type; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 scalar_t__ IB_NODE_SWITCH ; 
 int /*<<< orphan*/  update_switchportguids (TYPE_1__*) ; 

__attribute__((used)) static void replace_node_guid(ibnd_node_t *node, void *user_data)
{
	struct guids *guids;

	guids = (struct guids *)user_data;

	if (node->guid == guids->before) {

		node->guid = guids->after;

		/* port guids are identical to switch guids on
		 * switches, so update port guids too
		 */
		if (node->type == IB_NODE_SWITCH)
			update_switchportguids(node);

		guids->found++;
	}
}