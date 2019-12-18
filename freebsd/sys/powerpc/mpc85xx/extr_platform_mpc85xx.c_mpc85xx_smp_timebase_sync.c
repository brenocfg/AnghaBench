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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int volatile*,int) ; 
 int /*<<< orphan*/  atomic_thread_fence_seq_cst () ; 
 int /*<<< orphan*/  freeze_timebase (int /*<<< orphan*/ ,int) ; 
 int volatile mp_ncpus ; 
 int /*<<< orphan*/  mttb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcpm_dev ; 

__attribute__((used)) static void
mpc85xx_smp_timebase_sync(platform_t plat, u_long tb, int ap)
{
	static volatile bool tb_ready;
	static volatile int cpu_done;

	if (ap) {
		/* APs.  Hold off until we get a stable timebase. */
		while (!tb_ready)
			atomic_thread_fence_seq_cst();
		mttb(tb);
		atomic_add_int(&cpu_done, 1);
		while (cpu_done < mp_ncpus)
			atomic_thread_fence_seq_cst();
	} else {
		/* BSP */
		freeze_timebase(rcpm_dev, true);
		tb_ready = true;
		mttb(tb);
		atomic_add_int(&cpu_done, 1);
		while (cpu_done < mp_ncpus)
			atomic_thread_fence_seq_cst();
		freeze_timebase(rcpm_dev, false);
	}
}