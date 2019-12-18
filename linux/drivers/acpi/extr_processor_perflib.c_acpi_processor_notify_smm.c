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
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_processor_cpufreq_init ; 
 int /*<<< orphan*/  acpi_processor_ppc_in_use ; 
 int acpi_processor_pstate_control () ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int acpi_processor_notify_smm(struct module *calling_module)
{
	static int is_done = 0;
	int result;

	if (!acpi_processor_cpufreq_init)
		return -EBUSY;

	if (!try_module_get(calling_module))
		return -EINVAL;

	/* is_done is set to negative if an error occurred,
	 * and to postitive if _no_ error occurred, but SMM
	 * was already notified. This avoids double notification
	 * which might lead to unexpected results...
	 */
	if (is_done > 0) {
		module_put(calling_module);
		return 0;
	} else if (is_done < 0) {
		module_put(calling_module);
		return is_done;
	}

	is_done = -EIO;

	result = acpi_processor_pstate_control();
	if (!result) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "No SMI port or pstate_control\n"));
		module_put(calling_module);
		return 0;
	}
	if (result < 0) {
		module_put(calling_module);
		return result;
	}

	/* Success. If there's no _PPC, we need to fear nothing, so
	 * we can allow the cpufreq driver to be rmmod'ed. */
	is_done = 1;

	if (!acpi_processor_ppc_in_use)
		module_put(calling_module);

	return 0;
}