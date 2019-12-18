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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int dev_pm_qos_raw_resume_latency (struct device*) ; 
 struct device* get_cpu_device (unsigned int) ; 
 int pm_qos_request (int /*<<< orphan*/ ) ; 

int cpuidle_governor_latency_req(unsigned int cpu)
{
	int global_req = pm_qos_request(PM_QOS_CPU_DMA_LATENCY);
	struct device *device = get_cpu_device(cpu);
	int device_req = dev_pm_qos_raw_resume_latency(device);

	return device_req < global_req ? device_req : global_req;
}