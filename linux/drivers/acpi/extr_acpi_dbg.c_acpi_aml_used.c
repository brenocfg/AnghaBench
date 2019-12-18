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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __acpi_aml_used () ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool acpi_aml_used(void)
{
	bool ret;

	/*
	 * The usage count is prepared to avoid race conditions between the
	 * starts and the stops of the debugger thread.
	 */
	mutex_lock(&acpi_aml_io.lock);
	ret = __acpi_aml_used();
	mutex_unlock(&acpi_aml_io.lock);
	return ret;
}