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
struct TYPE_3__ {int /*<<< orphan*/  pend_frames_lock; int /*<<< orphan*/  pend_frames; int /*<<< orphan*/  ocs; } ;
typedef  TYPE_1__ ocs_node_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_purge_pending (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t
ocs_node_purge_pending(ocs_node_t *node)
{
	return ocs_purge_pending(node->ocs, &node->pend_frames, &node->pend_frames_lock);
}