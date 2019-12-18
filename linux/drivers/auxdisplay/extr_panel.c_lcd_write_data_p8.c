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
struct charlcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_BIT_E ; 
 int /*<<< orphan*/  LCD_BIT_RS ; 
 int /*<<< orphan*/  LCD_BIT_RW ; 
 int /*<<< orphan*/  bits ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprt ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ctrl_bits () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lcd_write_data_p8(struct charlcd *charlcd, int data)
{
	spin_lock_irq(&pprt_lock);
	/* present the data to the data port */
	w_dtr(pprt, data);
	udelay(20);	/* maintain the data during 20 us before the strobe */

	set_bit(LCD_BIT_E, bits);
	set_bit(LCD_BIT_RS, bits);
	clear_bit(LCD_BIT_RW, bits);
	set_ctrl_bits();

	udelay(40);	/* maintain the strobe during 40 us */

	clear_bit(LCD_BIT_E, bits);
	set_ctrl_bits();

	udelay(45);	/* the shortest data takes at least 45 us */
	spin_unlock_irq(&pprt_lock);
}