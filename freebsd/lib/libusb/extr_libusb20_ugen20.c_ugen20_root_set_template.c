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
struct libusb20_backend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SET_TEMPLATE ; 
 int ugen20_be_ioctl (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ugen20_root_set_template(struct libusb20_backend *pbe, int temp)
{
	return (ugen20_be_ioctl(IOUSB(USB_SET_TEMPLATE), &temp));
}