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
struct TYPE_2__ {int length; int /*<<< orphan*/  pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
struct ata_port {int /*<<< orphan*/  tdev; } ;
struct ata_acpi_gtm {int dummy; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ AE_NOT_FOUND ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  ata_port_err (struct ata_port*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ata_port_warn (struct ata_port*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct ata_acpi_gtm*,int /*<<< orphan*/ ,int) ; 

int ata_acpi_gtm(struct ata_port *ap, struct ata_acpi_gtm *gtm)
{
	struct acpi_buffer output = { .length = ACPI_ALLOCATE_BUFFER };
	union acpi_object *out_obj;
	acpi_status status;
	int rc = 0;
	acpi_handle handle = ACPI_HANDLE(&ap->tdev);

	if (!handle)
		return -EINVAL;

	status = acpi_evaluate_object(handle, "_GTM", NULL, &output);

	rc = -ENOENT;
	if (status == AE_NOT_FOUND)
		goto out_free;

	rc = -EINVAL;
	if (ACPI_FAILURE(status)) {
		ata_port_err(ap, "ACPI get timing mode failed (AE 0x%x)\n",
			     status);
		goto out_free;
	}

	out_obj = output.pointer;
	if (out_obj->type != ACPI_TYPE_BUFFER) {
		ata_port_warn(ap, "_GTM returned unexpected object type 0x%x\n",
			      out_obj->type);

		goto out_free;
	}

	if (out_obj->buffer.length != sizeof(struct ata_acpi_gtm)) {
		ata_port_err(ap, "_GTM returned invalid length %d\n",
			     out_obj->buffer.length);
		goto out_free;
	}

	memcpy(gtm, out_obj->buffer.pointer, sizeof(struct ata_acpi_gtm));
	rc = 0;
 out_free:
	kfree(output.pointer);
	return rc;
}