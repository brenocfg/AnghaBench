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

/* Variables and functions */
 int /*<<< orphan*/  consumer_cookie ; 
 int /*<<< orphan*/  nvme_register_consumer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_sim_controller_fail ; 
 int /*<<< orphan*/  nvme_sim_new_controller ; 
 int /*<<< orphan*/  nvme_sim_new_ns ; 
 scalar_t__ nvme_use_nvd ; 

__attribute__((used)) static void
nvme_sim_init(void)
{
	if (nvme_use_nvd)
		return;

	consumer_cookie = nvme_register_consumer(nvme_sim_new_ns,
	    nvme_sim_new_controller, NULL, nvme_sim_controller_fail);
}