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
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  vmem_periodic ; 
 int /*<<< orphan*/  vmem_periodic_ch ; 
 int vmem_periodic_interval ; 
 int /*<<< orphan*/  vmem_periodic_kick ; 
 int /*<<< orphan*/  vmem_periodic_wk ; 

__attribute__((used)) static void
vmem_start_callout(void *unused)
{

	TASK_INIT(&vmem_periodic_wk, 0, vmem_periodic, NULL);
	vmem_periodic_interval = hz * 10;
	callout_init(&vmem_periodic_ch, 1);
	callout_reset(&vmem_periodic_ch, vmem_periodic_interval,
	    vmem_periodic_kick, NULL);
}