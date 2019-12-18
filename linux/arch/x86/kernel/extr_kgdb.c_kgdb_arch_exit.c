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
struct TYPE_2__ {int /*<<< orphan*/ * pev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_LOCAL ; 
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 TYPE_1__* breakinfo ; 
 int /*<<< orphan*/  kgdb_notifier ; 
 int /*<<< orphan*/  unregister_die_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_nmi_handler (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unregister_wide_hw_breakpoint (int /*<<< orphan*/ *) ; 

void kgdb_arch_exit(void)
{
	int i;
	for (i = 0; i < 4; i++) {
		if (breakinfo[i].pev) {
			unregister_wide_hw_breakpoint(breakinfo[i].pev);
			breakinfo[i].pev = NULL;
		}
	}
	unregister_nmi_handler(NMI_UNKNOWN, "kgdb");
	unregister_nmi_handler(NMI_LOCAL, "kgdb");
	unregister_die_notifier(&kgdb_notifier);
}