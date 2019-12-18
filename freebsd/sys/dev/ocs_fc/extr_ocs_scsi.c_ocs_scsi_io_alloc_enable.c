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
struct TYPE_3__ {int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  io_alloc_enabled; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

void
ocs_scsi_io_alloc_enable(ocs_node_t *node)
{
	ocs_assert(node != NULL);
	ocs_lock(&node->active_ios_lock);
		node->io_alloc_enabled = TRUE;
	ocs_unlock(&node->active_ios_lock);
}