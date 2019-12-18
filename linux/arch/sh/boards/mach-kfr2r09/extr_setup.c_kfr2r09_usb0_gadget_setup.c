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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO_FN_PDSTATUS ; 
 int /*<<< orphan*/  GPIO_PTN4 ; 
 int /*<<< orphan*/  GPIO_PTV6 ; 
 int PORT_MSELCRB ; 
 int __raw_readw (int) ; 
 int /*<<< orphan*/  __raw_writew (int,int) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kfr2r09_usb0_gadget_i2c_setup () ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int kfr2r09_usb0_gadget_setup(void)
{
	int plugged_in;

	gpio_request(GPIO_PTN4, NULL); /* USB_DET */
	gpio_direction_input(GPIO_PTN4);
	plugged_in = gpio_get_value(GPIO_PTN4);
	if (!plugged_in)
		return -ENODEV; /* no cable plugged in */

	if (kfr2r09_usb0_gadget_i2c_setup() != 0)
		return -ENODEV; /* unable to configure using i2c */

	__raw_writew((__raw_readw(PORT_MSELCRB) & ~0xc000) | 0x8000, PORT_MSELCRB);
	gpio_request(GPIO_FN_PDSTATUS, NULL); /* R-standby disables USB clock */
	gpio_request(GPIO_PTV6, NULL); /* USBCLK_ON */
	gpio_direction_output(GPIO_PTV6, 1); /* USBCLK_ON = H */
	msleep(20); /* wait 20ms to let the clock settle */
	clk_enable(clk_get(NULL, "usb0"));
	__raw_writew(0x0600, 0xa40501d4);

	return 0;
}