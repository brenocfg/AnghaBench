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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HCI_REG_LCD_BACKLIGHT ; 
 int HCI_SET ; 
 int hci_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static int
hci_lcd_backlight(ACPI_HANDLE h, int op, UINT32 *backlight)
{

	ACPI_SERIAL_ASSERT(toshiba);
	if (op == HCI_SET) {
		if (*backlight > 1)
			return (EINVAL);
	}
	return (hci_call(h, op, HCI_REG_LCD_BACKLIGHT, backlight));
}