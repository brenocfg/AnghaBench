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
struct circ_buf {int dummy; } ;
struct TYPE_2__ {unsigned long flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int /*<<< orphan*/  __acpi_aml_access_ok (unsigned long) ; 
 int /*<<< orphan*/  __acpi_aml_writable (struct circ_buf*,unsigned long) ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_aml_lock_write(struct circ_buf *circ, unsigned long flag)
{
	int ret = 0;

	mutex_lock(&acpi_aml_io.lock);
	if (!__acpi_aml_access_ok(flag)) {
		ret = -EFAULT;
		goto out;
	}
	if (!__acpi_aml_writable(circ, flag)) {
		ret = -EAGAIN;
		goto out;
	}
	acpi_aml_io.flags |= flag;
out:
	mutex_unlock(&acpi_aml_io.lock);
	return ret;
}