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
struct acpi_device {int ad_flags; void* ad_private; int /*<<< orphan*/  ad_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_IVAR_FLAGS 130 
#define  ACPI_IVAR_HANDLE 129 
#define  ACPI_IVAR_PRIVATE 128 
 int ENOENT ; 
 struct acpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
acpi_write_ivar(device_t dev, device_t child, int index, uintptr_t value)
{
    struct acpi_device	*ad;

    if ((ad = device_get_ivars(child)) == NULL) {
	device_printf(child, "device has no ivars\n");
	return (ENOENT);
    }

    switch(index) {
    case ACPI_IVAR_HANDLE:
	ad->ad_handle = (ACPI_HANDLE)value;
	break;
    case ACPI_IVAR_PRIVATE:
	ad->ad_private = (void *)value;
	break;
    case ACPI_IVAR_FLAGS:
	ad->ad_flags = (int)value;
	break;
    default:
	panic("bad ivar write request (%d)", index);
	return (ENOENT);
    }

    return (0);
}