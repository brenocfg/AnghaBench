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
typedef  int u_int ;
struct monitorbuf {int /*<<< orphan*/  stop_state; } ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_2__ {struct monitorbuf pc_monitorbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_NAND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MONITOR_STOPSTATE_RUNNING ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_reset_proxy ; 
 int cpu_reset_proxy_active ; 
 scalar_t__ cpu_reset_proxyid ; 
 int /*<<< orphan*/  cpu_reset_real () ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  cpustop_restartfunc ; 
 int /*<<< orphan*/  ia32_pause () ; 
 TYPE_1__* pcpu_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ smp_started ; 
 int /*<<< orphan*/  started_cpus ; 
 int /*<<< orphan*/  stop_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stopped_cpus ; 

void
cpu_reset(void)
{
#ifdef SMP
	struct monitorbuf *mb;
	cpuset_t map;
	u_int cnt;

	if (smp_started) {
		map = all_cpus;
		CPU_CLR(PCPU_GET(cpuid), &map);
		CPU_NAND(&map, &stopped_cpus);
		if (!CPU_EMPTY(&map)) {
			printf("cpu_reset: Stopping other CPUs\n");
			stop_cpus(map);
		}

		if (PCPU_GET(cpuid) != 0) {
			cpu_reset_proxyid = PCPU_GET(cpuid);
			cpustop_restartfunc = cpu_reset_proxy;
			cpu_reset_proxy_active = 0;
			printf("cpu_reset: Restarting BSP\n");

			/* Restart CPU #0. */
			CPU_SETOF(0, &started_cpus);
			mb = &pcpu_find(0)->pc_monitorbuf;
			atomic_store_int(&mb->stop_state,
			    MONITOR_STOPSTATE_RUNNING);

			cnt = 0;
			while (cpu_reset_proxy_active == 0 && cnt < 10000000) {
				ia32_pause();
				cnt++;	/* Wait for BSP to announce restart */
			}
			if (cpu_reset_proxy_active == 0) {
				printf("cpu_reset: Failed to restart BSP\n");
			} else {
				cpu_reset_proxy_active = 2;
				while (1)
					ia32_pause();
				/* NOTREACHED */
			}
		}

		DELAY(1000000);
	}
#endif
	cpu_reset_real();
	/* NOTREACHED */
}