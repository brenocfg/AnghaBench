#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int DeviceClass; int DeviceSubClass; int DeviceProtocol; } ;
typedef  TYPE_1__ USB_CLASS_DEVICE_PATH ;
typedef  int UINTN ;
struct TYPE_6__ {scalar_t__ (* LocateHandle ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int HID; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  TYPE_2__ ACPI_HID_DEVICE_PATH ;

/* Variables and functions */
 scalar_t__ ACPI_DEVICE_PATH ; 
 scalar_t__ ACPI_DP ; 
 scalar_t__ ACPI_EXTENDED_DP ; 
 TYPE_3__* BS ; 
 int /*<<< orphan*/  ByProtocol ; 
 scalar_t__ DevicePathSubType (int /*<<< orphan*/ *) ; 
 scalar_t__ DevicePathType (int /*<<< orphan*/ *) ; 
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_ERROR (scalar_t__) ; 
 int EISA_ID_TO_NUM (int) ; 
 int /*<<< orphan*/  IsDevicePathEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ MESSAGING_DEVICE_PATH ; 
 scalar_t__ MSG_USB_CLASS_DP ; 
 int /*<<< orphan*/ * NextDevicePathNode (int /*<<< orphan*/ *) ; 
 scalar_t__ OpenProtocolByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int PNP_EISA_ID_CONST ; 
 int /*<<< orphan*/  devid ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inputid ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
has_keyboard(void)
{
	EFI_STATUS status;
	EFI_DEVICE_PATH *path;
	EFI_HANDLE *hin, *hin_end, *walker;
	UINTN sz;
	bool retval = false;

	/*
	 * Find all the handles that support the SIMPLE_TEXT_INPUT_PROTOCOL and
	 * do the typical dance to get the right sized buffer.
	 */
	sz = 0;
	hin = NULL;
	status = BS->LocateHandle(ByProtocol, &inputid, 0, &sz, 0);
	if (status == EFI_BUFFER_TOO_SMALL) {
		hin = (EFI_HANDLE *)malloc(sz);
		status = BS->LocateHandle(ByProtocol, &inputid, 0, &sz,
		    hin);
		if (EFI_ERROR(status))
			free(hin);
	}
	if (EFI_ERROR(status))
		return retval;

	/*
	 * Look at each of the handles. If it supports the device path protocol,
	 * use it to get the device path for this handle. Then see if that
	 * device path matches either the USB device path for keyboards or the
	 * legacy device path for keyboards.
	 */
	hin_end = &hin[sz / sizeof(*hin)];
	for (walker = hin; walker < hin_end; walker++) {
		status = OpenProtocolByHandle(*walker, &devid, (void **)&path);
		if (EFI_ERROR(status))
			continue;

		while (!IsDevicePathEnd(path)) {
			/*
			 * Check for the ACPI keyboard node. All PNP3xx nodes
			 * are keyboards of different flavors. Note: It is
			 * unclear of there's always a keyboard node when
			 * there's a keyboard controller, or if there's only one
			 * when a keyboard is detected at boot.
			 */
			if (DevicePathType(path) == ACPI_DEVICE_PATH &&
			    (DevicePathSubType(path) == ACPI_DP ||
				DevicePathSubType(path) == ACPI_EXTENDED_DP)) {
				ACPI_HID_DEVICE_PATH  *acpi;

				acpi = (ACPI_HID_DEVICE_PATH *)(void *)path;
				if ((EISA_ID_TO_NUM(acpi->HID) & 0xff00) == 0x300 &&
				    (acpi->HID & 0xffff) == PNP_EISA_ID_CONST) {
					retval = true;
					goto out;
				}
			/*
			 * Check for USB keyboard node, if present. Unlike a
			 * PS/2 keyboard, these definitely only appear when
			 * connected to the system.
			 */
			} else if (DevicePathType(path) == MESSAGING_DEVICE_PATH &&
			    DevicePathSubType(path) == MSG_USB_CLASS_DP) {
				USB_CLASS_DEVICE_PATH *usb;

				usb = (USB_CLASS_DEVICE_PATH *)(void *)path;
				if (usb->DeviceClass == 3 && /* HID */
				    usb->DeviceSubClass == 1 && /* Boot devices */
				    usb->DeviceProtocol == 1) { /* Boot keyboards */
					retval = true;
					goto out;
				}
			}
			path = NextDevicePathNode(path);
		}
	}
out:
	free(hin);
	return retval;
}