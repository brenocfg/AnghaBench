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
typedef  int /*<<< orphan*/  ocs_node_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_RESUME ; 
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_node_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t
ocs_node_resume(ocs_node_t *node)
{
	ocs_assert(node != NULL, -1);

	ocs_node_post_event(node, OCS_EVT_RESUME, NULL);

	return 0;
}