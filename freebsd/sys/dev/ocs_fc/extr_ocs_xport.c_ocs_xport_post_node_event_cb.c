#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  context; int /*<<< orphan*/  evt; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ocs_xport_post_node_event_t ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_node_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_xport_post_node_event_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_xport_post_node_event_t *payload = arg;

	if (payload != NULL) {
		ocs_node_post_event(payload->node, payload->evt, payload->context);
		ocs_sem_v(&payload->sem);
	}

        return 0;
}