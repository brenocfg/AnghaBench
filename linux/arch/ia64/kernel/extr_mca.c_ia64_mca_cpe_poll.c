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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_CPEP_VECTOR ; 
 int /*<<< orphan*/  IA64_IPI_DM_INT ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_send_ipi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_mca_cpe_poll (struct timer_list *unused)
{
	/* Trigger a CPE interrupt cascade  */
	ia64_send_ipi(cpumask_first(cpu_online_mask), IA64_CPEP_VECTOR,
							IA64_IPI_DM_INT, 0);
}