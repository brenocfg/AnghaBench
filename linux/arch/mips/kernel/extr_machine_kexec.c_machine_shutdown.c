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
 int /*<<< orphan*/  _machine_kexec_shutdown () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kexec_shutdown_secondary ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
machine_shutdown(void)
{
	if (_machine_kexec_shutdown)
		_machine_kexec_shutdown();

#ifdef CONFIG_SMP
	smp_call_function(kexec_shutdown_secondary, NULL, 0);

	while (num_online_cpus() > 1) {
		cpu_relax();
		mdelay(1);
	}
#endif
}