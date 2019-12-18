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
struct hd44780 {scalar_t__* pins; } ;
struct charlcd {struct hd44780* drvdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int*,int) ; 
 size_t PIN_CTRL_RW ; 
 size_t PIN_DATA4 ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (unsigned int,scalar_t__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  hd44780_strobe_gpio (struct hd44780*) ; 
 int* values ; 

__attribute__((used)) static void hd44780_write_cmd_raw_gpio4(struct charlcd *lcd, int cmd)
{
	DECLARE_BITMAP(values, 6); /* for DATA[4-7], RS, RW */
	struct hd44780 *hd = lcd->drvdata;
	unsigned int n;

	/* Command nibble + RS, RW */
	values[0] = cmd & 0x0f;
	n = hd->pins[PIN_CTRL_RW] ? 6 : 5;

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4], NULL, values);

	hd44780_strobe_gpio(hd);
}