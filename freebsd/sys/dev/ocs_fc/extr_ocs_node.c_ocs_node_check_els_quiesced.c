#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ els_req_cnt; scalar_t__ els_cmpl_cnt; int /*<<< orphan*/  attached; int /*<<< orphan*/  els_io_active_list; } ;
typedef  TYPE_1__ ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ocs_node_wait_ios_shutdown ; 
 int /*<<< orphan*/  __ocs_node_wait_node_free ; 
 int /*<<< orphan*/  node_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int) ; 
 scalar_t__ ocs_els_io_list_empty (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_node_transition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ocs_node_check_els_quiesced(ocs_node_t *node)
{
	ocs_assert(node, -1);

	/* check to see if ELS requests, completions are quiesced */
	if ((node->els_req_cnt == 0) && (node->els_cmpl_cnt == 0) &&
	    ocs_els_io_list_empty(node, &node->els_io_active_list)) {
		if (!node->attached) {
			/* hw node detach already completed, proceed */
			node_printf(node, "HW node not attached\n");
			ocs_node_transition(node, __ocs_node_wait_ios_shutdown, NULL);
		} else {
			/* hw node detach hasn't completed, transition and wait */
			node_printf(node, "HW node still attached\n");
			ocs_node_transition(node, __ocs_node_wait_node_free, NULL);
		}
		return 1;
	}
	return 0;
}