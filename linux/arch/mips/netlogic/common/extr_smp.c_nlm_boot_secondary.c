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
typedef  int /*<<< orphan*/  uint64_t ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  picbase; } ;

/* Variables and functions */
 scalar_t__ __KSTK_TOS (struct task_struct*) ; 
 int /*<<< orphan*/  __sync () ; 
 int cpu_logical_map (int) ; 
 TYPE_1__* nlm_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_hwtid_to_node (int) ; 
 unsigned long nlm_next_gp ; 
 unsigned long nlm_next_sp ; 
 int /*<<< orphan*/  nlm_pic_send_ipi (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ task_thread_info (struct task_struct*) ; 

int nlm_boot_secondary(int logical_cpu, struct task_struct *idle)
{
	uint64_t picbase;
	int hwtid;

	hwtid = cpu_logical_map(logical_cpu);
	picbase = nlm_get_node(nlm_hwtid_to_node(hwtid))->picbase;

	nlm_next_sp = (unsigned long)__KSTK_TOS(idle);
	nlm_next_gp = (unsigned long)task_thread_info(idle);

	/* barrier for sp/gp store above */
	__sync();
	nlm_pic_send_ipi(picbase, hwtid, 1, 1);  /* NMI */

	return 0;
}