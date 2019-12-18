#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int UINT32 ;
struct TYPE_9__ {int member_0; int** member_1; TYPE_2__* Pointer; } ;
struct TYPE_7__ {scalar_t__ Pointer; } ;
struct TYPE_8__ {scalar_t__ Type; TYPE_1__ Buffer; } ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HP_WMI_BIOS_GUID ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_WMI_EVALUATE_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*,TYPE_3__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_hp_free_buffer (TYPE_3__*) ; 

__attribute__((used)) static int
acpi_hp_exec_wmi_command(device_t wmi_dev, int command, int is_write,
    int val, int *retval)
{
	UINT32		params[4+32] = { 0x55434553, is_write ? 2 : 1,
			    command, 4, val};
	UINT32*		result;
	ACPI_OBJECT	*obj;
	ACPI_BUFFER	in = { sizeof(params), &params };
	ACPI_BUFFER	out = { ACPI_ALLOCATE_BUFFER, NULL };
	int res;
	
	if (ACPI_FAILURE(ACPI_WMI_EVALUATE_CALL(wmi_dev, ACPI_HP_WMI_BIOS_GUID,
		    0, 0x3, &in, &out))) {
		acpi_hp_free_buffer(&out);
		return (-EINVAL);
	}
	obj = out.Pointer;
	if (!obj || obj->Type != ACPI_TYPE_BUFFER) {
		acpi_hp_free_buffer(&out);
		return (-EINVAL);
	}
	result = (UINT32*) obj->Buffer.Pointer;
	res = result[1];
	if (res == 0 && retval != NULL)
		*retval = result[2];
	acpi_hp_free_buffer(&out);

	return (res);
}