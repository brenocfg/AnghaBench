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
struct TYPE_2__ {int /*<<< orphan*/  semaphore; int /*<<< orphan*/  port_protocol; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ocs_mgmt_get_port_protocol_result_t ;
typedef  int /*<<< orphan*/  ocs_hw_port_protocol_e ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_mgmt_get_port_protocol_cb(int32_t status,
			      ocs_hw_port_protocol_e port_protocol,
			      void    *arg)
{
	ocs_mgmt_get_port_protocol_result_t *result = arg;

	result->status = status;
	result->port_protocol = port_protocol;

	ocs_sem_v(&(result->semaphore));
}