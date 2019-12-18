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
struct nps_host_reg_thr_init_sts {scalar_t__ thr_id; scalar_t__ err; scalar_t__ bsy; int /*<<< orphan*/  value; } ;
struct nps_host_reg_thr_init {scalar_t__ thr_id; int str; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTM_THR_INIT (int) ; 
 int /*<<< orphan*/  MTM_THR_INIT_STS (int) ; 
 scalar_t__ NPS_CPU_TO_THREAD_NUM (int) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void mtm_init_thread(int cpu)
{
	int i, tries = 5;
	struct nps_host_reg_thr_init thr_init;
	struct nps_host_reg_thr_init_sts thr_init_sts;

	/* Set thread init register */
	thr_init.value = 0;
	iowrite32be(thr_init.value, MTM_THR_INIT(cpu));
	thr_init.thr_id = NPS_CPU_TO_THREAD_NUM(cpu);
	thr_init.str = 1;
	iowrite32be(thr_init.value, MTM_THR_INIT(cpu));

	/* Poll till thread init is done */
	for (i = 0; i < tries; i++) {
		thr_init_sts.value = ioread32be(MTM_THR_INIT_STS(cpu));
		if (thr_init_sts.thr_id == thr_init.thr_id) {
			if (thr_init_sts.bsy)
				continue;
			else if (thr_init_sts.err)
				pr_warn("Failed to thread init cpu %u\n", cpu);
			break;
		}

		pr_warn("Wrong thread id in thread init for cpu %u\n", cpu);
		break;
	}

	if (i == tries)
		pr_warn("Got thread init timeout for cpu %u\n", cpu);
}