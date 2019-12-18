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
struct edac_device_ctl_info {int /*<<< orphan*/  work; int /*<<< orphan*/  op_state; int /*<<< orphan*/  edac_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_OFFLINE ; 
 int /*<<< orphan*/  edac_stop_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edac_device_workq_teardown(struct edac_device_ctl_info *edac_dev)
{
	if (!edac_dev->edac_check)
		return;

	edac_dev->op_state = OP_OFFLINE;

	edac_stop_work(&edac_dev->work);
}