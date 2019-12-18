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
typedef  int /*<<< orphan*/  (* acpi_osd_exec_callback ) (void*) ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/ * thread; int /*<<< orphan*/  usages; void* context; int /*<<< orphan*/  (* function ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __acpi_aml_used () ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_aml_thread(void *unused)
{
	acpi_osd_exec_callback function = NULL;
	void *context;

	mutex_lock(&acpi_aml_io.lock);
	if (acpi_aml_io.function) {
		acpi_aml_io.usages++;
		function = acpi_aml_io.function;
		context = acpi_aml_io.context;
	}
	mutex_unlock(&acpi_aml_io.lock);

	if (function)
		function(context);

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.usages--;
	if (!__acpi_aml_used()) {
		acpi_aml_io.thread = NULL;
		wake_up(&acpi_aml_io.wait);
	}
	mutex_unlock(&acpi_aml_io.lock);

	return 0;
}