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
 scalar_t__ ctr_running ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  nmi_cpu_stop ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

__attribute__((used)) static void nmi_stop(void)
{
	get_online_cpus();
	on_each_cpu(nmi_cpu_stop, NULL, 1);
	ctr_running = 0;
	put_online_cpus();
}