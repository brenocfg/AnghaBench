#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cpu_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cpu_up_prepare ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_SMT ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  INVALID_THREAD_HWID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  booting_thread_hwid ; 
 int cpu_first_thread_sibling (int) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpu_thread_in_core (int) ; 
 int /*<<< orphan*/  generic_set_cpu_up (int) ; 
 int num_possible_cpus () ; 
 TYPE_2__** paca_ptrs ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__* qoriq_pm_ops ; 
 int smp_85xx_start_cpu (int) ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int threads_per_core ; 
 int /*<<< orphan*/  wake_hw_thread ; 

__attribute__((used)) static int smp_85xx_kick_cpu(int nr)
{
	int ret = 0;
#ifdef CONFIG_PPC64
	int primary = nr;
#endif

	WARN_ON(nr < 0 || nr >= num_possible_cpus());

	pr_debug("kick CPU #%d\n", nr);

#ifdef CONFIG_PPC64
	if (threads_per_core == 2) {
		if (WARN_ON_ONCE(!cpu_has_feature(CPU_FTR_SMT)))
			return -ENOENT;

		booting_thread_hwid = cpu_thread_in_core(nr);
		primary = cpu_first_thread_sibling(nr);

		if (qoriq_pm_ops)
			qoriq_pm_ops->cpu_up_prepare(nr);

		/*
		 * If either thread in the core is online, use it to start
		 * the other.
		 */
		if (cpu_online(primary)) {
			smp_call_function_single(primary,
					wake_hw_thread, &nr, 1);
			goto done;
		} else if (cpu_online(primary + 1)) {
			smp_call_function_single(primary + 1,
					wake_hw_thread, &nr, 1);
			goto done;
		}

		/*
		 * If getting here, it means both threads in the core are
		 * offline. So start the primary thread, then it will start
		 * the thread specified in booting_thread_hwid, the one
		 * corresponding to nr.
		 */

	} else if (threads_per_core == 1) {
		/*
		 * If one core has only one thread, set booting_thread_hwid to
		 * an invalid value.
		 */
		booting_thread_hwid = INVALID_THREAD_HWID;

	} else if (threads_per_core > 2) {
		pr_err("Do not support more than 2 threads per CPU.");
		return -EINVAL;
	}

	ret = smp_85xx_start_cpu(primary);
	if (ret)
		return ret;

done:
	paca_ptrs[nr]->cpu_start = 1;
	generic_set_cpu_up(nr);

	return ret;
#else
	ret = smp_85xx_start_cpu(nr);
	if (ret)
		return ret;

	generic_set_cpu_up(nr);

	return ret;
#endif
}