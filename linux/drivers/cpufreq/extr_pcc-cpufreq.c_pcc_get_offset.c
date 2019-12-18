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
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
struct pcc_cpu {scalar_t__ output_offset; scalar_t__ input_offset; } ;
struct acpi_processor {int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  BUF_SZ ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_cpu_info ; 
 scalar_t__ pcch_virt_addr ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,int) ; 
 struct pcc_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  processors ; 

__attribute__((used)) static int pcc_get_offset(int cpu)
{
	acpi_status status;
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	union acpi_object *pccp, *offset;
	struct pcc_cpu *pcc_cpu_data;
	struct acpi_processor *pr;
	int ret = 0;

	pr = per_cpu(processors, cpu);
	pcc_cpu_data = per_cpu_ptr(pcc_cpu_info, cpu);

	if (!pr)
		return -ENODEV;

	status = acpi_evaluate_object(pr->handle, "PCCP", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	pccp = buffer.pointer;
	if (!pccp || pccp->type != ACPI_TYPE_PACKAGE) {
		ret = -ENODEV;
		goto out_free;
	}

	offset = &(pccp->package.elements[0]);
	if (!offset || offset->type != ACPI_TYPE_INTEGER) {
		ret = -ENODEV;
		goto out_free;
	}

	pcc_cpu_data->input_offset = offset->integer.value;

	offset = &(pccp->package.elements[1]);
	if (!offset || offset->type != ACPI_TYPE_INTEGER) {
		ret = -ENODEV;
		goto out_free;
	}

	pcc_cpu_data->output_offset = offset->integer.value;

	memset_io((pcch_virt_addr + pcc_cpu_data->input_offset), 0, BUF_SZ);
	memset_io((pcch_virt_addr + pcc_cpu_data->output_offset), 0, BUF_SZ);

	pr_debug("pcc_get_offset: for CPU %d: pcc_cpu_data "
		"input_offset: 0x%x, pcc_cpu_data output_offset: 0x%x\n",
		cpu, pcc_cpu_data->input_offset, pcc_cpu_data->output_offset);
out_free:
	kfree(buffer.pointer);
	return ret;
}