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
typedef  int /*<<< orphan*/  ocs_sport_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FC_ADDR_CONTROLLER ; 
 int /*<<< orphan*/  __ocs_fabctl_init ; 
 int /*<<< orphan*/ * ocs_node_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocs_node_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_node_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_start_fabctl_node(ocs_sport_t *sport)
{
	ocs_node_t *fabctl;

	fabctl = ocs_node_find(sport, FC_ADDR_CONTROLLER);
	if (fabctl == NULL) {
		fabctl = ocs_node_alloc(sport, FC_ADDR_CONTROLLER, FALSE, FALSE);
		if (fabctl == NULL) {
			return -1;
		}
	}
	/* TODO: for found ns, should we be transitioning from here?
	 * breaks transition only 1. from within state machine or
	 * 2. if after alloc
	 */
	ocs_node_transition(fabctl, __ocs_fabctl_init, NULL);
	return 0;
}