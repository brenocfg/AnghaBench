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
typedef  int uint8_t ;
struct libusb20_device {int /*<<< orphan*/  file_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_OTHER ; 
 int LIBUSB20_POWER_OFF ; 
 int LIBUSB20_POWER_ON ; 
 int LIBUSB20_POWER_RESUME ; 
 int LIBUSB20_POWER_SAVE ; 
 int LIBUSB20_POWER_SUSPEND ; 
 int /*<<< orphan*/  USB_GET_POWER_MODE ; 
#define  USB_POWER_MODE_OFF 132 
#define  USB_POWER_MODE_ON 131 
#define  USB_POWER_MODE_RESUME 130 
#define  USB_POWER_MODE_SAVE 129 
#define  USB_POWER_MODE_SUSPEND 128 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ugen20_get_power_mode(struct libusb20_device *pdev, uint8_t *power_mode)
{
	int temp;

	if (ioctl(pdev->file_ctrl, IOUSB(USB_GET_POWER_MODE), &temp)) {
		return (LIBUSB20_ERROR_OTHER);
	}
	switch (temp) {
	case USB_POWER_MODE_OFF:
		temp = LIBUSB20_POWER_OFF;
		break;
	case USB_POWER_MODE_ON:
		temp = LIBUSB20_POWER_ON;
		break;
	case USB_POWER_MODE_SAVE:
		temp = LIBUSB20_POWER_SAVE;
		break;
	case USB_POWER_MODE_SUSPEND:
		temp = LIBUSB20_POWER_SUSPEND;
		break;
	case USB_POWER_MODE_RESUME:
		temp = LIBUSB20_POWER_RESUME;
		break;
	default:
		temp = LIBUSB20_POWER_ON;
		break;
	}
	*power_mode = temp;
	return (0);			/* success */
}