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
typedef  scalar_t__ UINT32 ;
struct TYPE_9__ {int member_0; scalar_t__** member_1; TYPE_2__* Pointer; } ;
struct TYPE_7__ {scalar_t__ Value; } ;
struct TYPE_8__ {scalar_t__ Type; TYPE_1__ Integer; } ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_ASUS_WMI_MGMT_GUID ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_WMI_EVALUATE_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ ASUS_WMI_UNSUPPORTED_METHOD ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_asus_wmi_free_buffer (TYPE_3__*) ; 

__attribute__((used)) static int
acpi_asus_wmi_evaluate_method(device_t wmi_dev, int method,
    UINT32 arg0, UINT32 arg1, UINT32 *retval)
{
	UINT32		params[2] = { arg0, arg1 };
	UINT32		result;
	ACPI_OBJECT	*obj;
	ACPI_BUFFER	in = { sizeof(params), &params };
	ACPI_BUFFER	out = { ACPI_ALLOCATE_BUFFER, NULL };
	
	if (ACPI_FAILURE(ACPI_WMI_EVALUATE_CALL(wmi_dev,
	    ACPI_ASUS_WMI_MGMT_GUID, 1, method, &in, &out))) {
		acpi_asus_wmi_free_buffer(&out);
		return (-EINVAL);
	}
	obj = out.Pointer;
	if (obj && obj->Type == ACPI_TYPE_INTEGER)
		result = (UINT32) obj->Integer.Value;
	else
		result = 0;
	acpi_asus_wmi_free_buffer(&out);
	if (retval)
		*retval = result;
	return (result == ASUS_WMI_UNSUPPORTED_METHOD ? -ENODEV : 0);
}