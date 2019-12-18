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
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int LIBUSB20_ERROR_OTHER ; 
#define  LIBUSB20_POWER_OFF 132 
#define  LIBUSB20_POWER_ON 131 
#define  LIBUSB20_POWER_RESUME 130 
#define  LIBUSB20_POWER_SAVE 129 
#define  LIBUSB20_POWER_SUSPEND 128 
 int USB_POWER_MODE_OFF ; 
 int USB_POWER_MODE_ON ; 
 int USB_POWER_MODE_RESUME ; 
 int USB_POWER_MODE_SAVE ; 
 int USB_POWER_MODE_SUSPEND ; 
 int /*<<< orphan*/  USB_SET_POWER_MODE ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ugen20_set_power_mode(struct libusb20_device *pdev, uint8_t power_mode)
{
	int temp;

	switch (power_mode) {
	case LIBUSB20_POWER_OFF:
		temp = USB_POWER_MODE_OFF;
		break;
	case LIBUSB20_POWER_ON:
		temp = USB_POWER_MODE_ON;
		break;
	case LIBUSB20_POWER_SAVE:
		temp = USB_POWER_MODE_SAVE;
		break;
	case LIBUSB20_POWER_SUSPEND:
		temp = USB_POWER_MODE_SUSPEND;
		break;
	case LIBUSB20_POWER_RESUME:
		temp = USB_POWER_MODE_RESUME;
		break;
	default:
		return (LIBUSB20_ERROR_INVALID_PARAM);
	}
	if (ioctl(pdev->file_ctrl, IOUSB(USB_SET_POWER_MODE), &temp)) {
		return (LIBUSB20_ERROR_OTHER);
	}
	return (0);
}