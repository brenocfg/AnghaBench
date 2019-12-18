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
 int /*<<< orphan*/  LCD_BIT_CL ; 
 int /*<<< orphan*/  LCD_BIT_DA ; 
 int /*<<< orphan*/  bits ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panel_set_bits () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_send_serial(int byte)
{
	int bit;

	/*
	 * the data bit is set on D0, and the clock on STROBE.
	 * LCD reads D0 on STROBE's rising edge.
	 */
	for (bit = 0; bit < 8; bit++) {
		clear_bit(LCD_BIT_CL, bits);	/* CLK low */
		panel_set_bits();
		if (byte & 1) {
			set_bit(LCD_BIT_DA, bits);
		} else {
			clear_bit(LCD_BIT_DA, bits);
		}

		panel_set_bits();
		udelay(2);  /* maintain the data during 2 us before CLK up */
		set_bit(LCD_BIT_CL, bits);	/* CLK high */
		panel_set_bits();
		udelay(1);  /* maintain the strobe during 1 us */
		byte >>= 1;
	}
}