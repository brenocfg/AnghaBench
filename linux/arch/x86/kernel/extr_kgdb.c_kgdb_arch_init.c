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
 int /*<<< orphan*/  NMI_LOCAL ; 
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 int /*<<< orphan*/  kgdb_nmi_handler ; 
 int /*<<< orphan*/  kgdb_notifier ; 
 int register_die_notifier (int /*<<< orphan*/ *) ; 
 int register_nmi_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unregister_die_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_nmi_handler (int /*<<< orphan*/ ,char*) ; 

int kgdb_arch_init(void)
{
	int retval;

	retval = register_die_notifier(&kgdb_notifier);
	if (retval)
		goto out;

	retval = register_nmi_handler(NMI_LOCAL, kgdb_nmi_handler,
					0, "kgdb");
	if (retval)
		goto out1;

	retval = register_nmi_handler(NMI_UNKNOWN, kgdb_nmi_handler,
					0, "kgdb");

	if (retval)
		goto out2;

	return retval;

out2:
	unregister_nmi_handler(NMI_LOCAL, "kgdb");
out1:
	unregister_die_notifier(&kgdb_notifier);
out:
	return retval;
}