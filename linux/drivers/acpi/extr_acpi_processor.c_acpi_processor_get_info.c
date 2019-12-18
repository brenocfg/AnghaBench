#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long long proc_id; int pblk_length; scalar_t__ pblk_address; } ;
union acpi_object {TYPE_3__ processor; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  duty_width; int /*<<< orphan*/  duty_offset; scalar_t__ address; } ;
struct TYPE_5__ {int bm_control; } ;
struct acpi_processor {unsigned long long acpi_id; int id; int /*<<< orphan*/  handle; scalar_t__ pblk; TYPE_2__ throttling; int /*<<< orphan*/  phys_id; TYPE_1__ flags; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
struct acpi_buffer {int member_0; union acpi_object* member_1; } ;
typedef  int acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  duty_width; int /*<<< orphan*/  duty_offset; scalar_t__ pm2_control_length; scalar_t__ pm2_control_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_OBJECT_HID ; 
 scalar_t__ ACPI_SUCCESS (int) ; 
 int AE_OK ; 
 int ENODEV ; 
 char* METHOD_NAME__UID ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 struct acpi_processor* acpi_driver_data (struct acpi_device*) ; 
 scalar_t__ acpi_duplicate_processor_id (unsigned long long) ; 
 int acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 TYPE_4__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_get_phys_id (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_has_cpu_in_madt () ; 
 int acpi_map_cpuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_processor_errata () ; 
 int acpi_processor_hotadd_init (struct acpi_processor*) ; 
 int /*<<< orphan*/  arch_fix_phys_package_id (int,unsigned long long) ; 
 int /*<<< orphan*/  cpu_present (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info_once (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ invalid_logical_cpuid (int) ; 
 scalar_t__ invalid_phys_cpuid (int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_get_info(struct acpi_device *device)
{
	union acpi_object object = { 0 };
	struct acpi_buffer buffer = { sizeof(union acpi_object), &object };
	struct acpi_processor *pr = acpi_driver_data(device);
	int device_declaration = 0;
	acpi_status status = AE_OK;
	static int cpu0_initialized;
	unsigned long long value;

	acpi_processor_errata();

	/*
	 * Check to see if we have bus mastering arbitration control.  This
	 * is required for proper C3 usage (to maintain cache coherency).
	 */
	if (acpi_gbl_FADT.pm2_control_block && acpi_gbl_FADT.pm2_control_length) {
		pr->flags.bm_control = 1;
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Bus mastering arbitration control present\n"));
	} else
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "No bus mastering arbitration control\n"));

	if (!strcmp(acpi_device_hid(device), ACPI_PROCESSOR_OBJECT_HID)) {
		/* Declared with "Processor" statement; match ProcessorID */
		status = acpi_evaluate_object(pr->handle, NULL, NULL, &buffer);
		if (ACPI_FAILURE(status)) {
			dev_err(&device->dev,
				"Failed to evaluate processor object (0x%x)\n",
				status);
			return -ENODEV;
		}

		pr->acpi_id = object.processor.proc_id;
	} else {
		/*
		 * Declared with "Device" statement; match _UID.
		 * Note that we don't handle string _UIDs yet.
		 */
		status = acpi_evaluate_integer(pr->handle, METHOD_NAME__UID,
						NULL, &value);
		if (ACPI_FAILURE(status)) {
			dev_err(&device->dev,
				"Failed to evaluate processor _UID (0x%x)\n",
				status);
			return -ENODEV;
		}
		device_declaration = 1;
		pr->acpi_id = value;
	}

	if (acpi_duplicate_processor_id(pr->acpi_id)) {
		if (pr->acpi_id == 0xff)
			dev_info_once(&device->dev,
				"Entry not well-defined, consider updating BIOS\n");
		else
			dev_err(&device->dev,
				"Failed to get unique processor _UID (0x%x)\n",
				pr->acpi_id);
		return -ENODEV;
	}

	pr->phys_id = acpi_get_phys_id(pr->handle, device_declaration,
					pr->acpi_id);
	if (invalid_phys_cpuid(pr->phys_id))
		acpi_handle_debug(pr->handle, "failed to get CPU physical ID.\n");

	pr->id = acpi_map_cpuid(pr->phys_id, pr->acpi_id);
	if (!cpu0_initialized && !acpi_has_cpu_in_madt()) {
		cpu0_initialized = 1;
		/*
		 * Handle UP system running SMP kernel, with no CPU
		 * entry in MADT
		 */
		if (invalid_logical_cpuid(pr->id) && (num_online_cpus() == 1))
			pr->id = 0;
	}

	/*
	 *  Extra Processor objects may be enumerated on MP systems with
	 *  less than the max # of CPUs. They should be ignored _iff
	 *  they are physically not present.
	 *
	 *  NOTE: Even if the processor has a cpuid, it may not be present
	 *  because cpuid <-> apicid mapping is persistent now.
	 */
	if (invalid_logical_cpuid(pr->id) || !cpu_present(pr->id)) {
		int ret = acpi_processor_hotadd_init(pr);
		if (ret)
			return ret;
	}

	/*
	 * On some boxes several processors use the same processor bus id.
	 * But they are located in different scope. For example:
	 * \_SB.SCK0.CPU0
	 * \_SB.SCK1.CPU0
	 * Rename the processor device bus id. And the new bus id will be
	 * generated as the following format:
	 * CPU+CPU ID.
	 */
	sprintf(acpi_device_bid(device), "CPU%X", pr->id);
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Processor [%d:%d]\n", pr->id,
			  pr->acpi_id));

	if (!object.processor.pblk_address)
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "No PBLK (NULL address)\n"));
	else if (object.processor.pblk_length != 6)
		dev_err(&device->dev, "Invalid PBLK length [%d]\n",
			    object.processor.pblk_length);
	else {
		pr->throttling.address = object.processor.pblk_address;
		pr->throttling.duty_offset = acpi_gbl_FADT.duty_offset;
		pr->throttling.duty_width = acpi_gbl_FADT.duty_width;

		pr->pblk = object.processor.pblk_address;
	}

	/*
	 * If ACPI describes a slot number for this CPU, we can use it to
	 * ensure we get the right value in the "physical id" field
	 * of /proc/cpuinfo
	 */
	status = acpi_evaluate_integer(pr->handle, "_SUN", NULL, &value);
	if (ACPI_SUCCESS(status))
		arch_fix_phys_package_id(pr->id, value);

	return 0;
}