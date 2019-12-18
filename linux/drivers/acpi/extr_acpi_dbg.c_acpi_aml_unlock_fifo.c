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
struct TYPE_2__ {unsigned long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_aml_unlock_fifo(unsigned long flag, bool wakeup)
{
	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.flags &= ~flag;
	if (wakeup)
		wake_up_interruptible(&acpi_aml_io.wait);
	mutex_unlock(&acpi_aml_io.lock);
}