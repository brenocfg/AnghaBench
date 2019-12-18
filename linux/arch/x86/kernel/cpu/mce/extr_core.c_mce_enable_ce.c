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
 int /*<<< orphan*/  __mcheck_cpu_init_timer () ; 
 int /*<<< orphan*/  cmci_recheck () ; 
 int /*<<< orphan*/  cmci_reenable () ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  mce_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mce_enable_ce(void *all)
{
	if (!mce_available(raw_cpu_ptr(&cpu_info)))
		return;
	cmci_reenable();
	cmci_recheck();
	if (all)
		__mcheck_cpu_init_timer();
}