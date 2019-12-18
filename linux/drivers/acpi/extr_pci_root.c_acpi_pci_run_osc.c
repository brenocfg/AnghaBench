#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ pointer; } ;
struct TYPE_3__ {int length; void* pointer; } ;
struct acpi_osc_context {int rev; TYPE_2__ ret; TYPE_1__ cap; int /*<<< orphan*/  uuid_str; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_run_osc (int /*<<< orphan*/ ,struct acpi_osc_context*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pci_osc_uuid_str ; 

__attribute__((used)) static acpi_status acpi_pci_run_osc(acpi_handle handle,
				    const u32 *capbuf, u32 *retval)
{
	struct acpi_osc_context context = {
		.uuid_str = pci_osc_uuid_str,
		.rev = 1,
		.cap.length = 12,
		.cap.pointer = (void *)capbuf,
	};
	acpi_status status;

	status = acpi_run_osc(handle, &context);
	if (ACPI_SUCCESS(status)) {
		*retval = *((u32 *)(context.ret.pointer + 8));
		kfree(context.ret.pointer);
	}
	return status;
}