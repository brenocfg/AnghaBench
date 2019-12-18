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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ioapic_domain_cfg {int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  IOAPIC_DOMAIN_DYNAMIC ; 
 int /*<<< orphan*/  METHOD_NAME__UID ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 int acpi_get_ioapic_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_handle_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ioapic_lock ; 
 int /*<<< orphan*/  mp_ioapic_irqdomain_ops ; 
 int mp_register_ioapic (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioapic_domain_cfg*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int acpi_register_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
{
	int ret = -ENOSYS;
#ifdef CONFIG_ACPI_HOTPLUG_IOAPIC
	int ioapic_id;
	u64 addr;
	struct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_irqdomain_ops,
	};

	ioapic_id = acpi_get_ioapic_id(handle, gsi_base, &addr);
	if (ioapic_id < 0) {
		unsigned long long uid;
		acpi_status status;

		status = acpi_evaluate_integer(handle, METHOD_NAME__UID,
					       NULL, &uid);
		if (ACPI_FAILURE(status)) {
			acpi_handle_warn(handle, "failed to get IOAPIC ID.\n");
			return -EINVAL;
		}
		ioapic_id = (int)uid;
	}

	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_register_ioapic(ioapic_id, phys_addr, gsi_base, &cfg);
	mutex_unlock(&acpi_ioapic_lock);
#endif

	return ret;
}