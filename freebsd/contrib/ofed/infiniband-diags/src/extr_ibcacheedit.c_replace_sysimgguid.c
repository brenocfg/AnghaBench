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
typedef  scalar_t__ uint64_t ;
struct guids {scalar_t__ before; int /*<<< orphan*/  found; int /*<<< orphan*/  after; } ;
struct TYPE_3__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ibnd_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_SYSTEM_GUID_F ; 
 scalar_t__ mad_get_field64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_set_field64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void replace_sysimgguid(ibnd_node_t *node, void *user_data)
{
	struct guids *guids;
	uint64_t sysimgguid;

	guids = (struct guids *)user_data;

	sysimgguid = mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F);
	if (sysimgguid == guids->before) {
		mad_set_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F,
				guids->after);
		guids->found++;
	}
}