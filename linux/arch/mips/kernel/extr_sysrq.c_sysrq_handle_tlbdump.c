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
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysrq_tlbdump ; 
 int /*<<< orphan*/  sysrq_tlbdump_single (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sysrq_handle_tlbdump(int key)
{
	sysrq_tlbdump_single(NULL);
#ifdef CONFIG_SMP
	schedule_work(&sysrq_tlbdump);
#endif
}