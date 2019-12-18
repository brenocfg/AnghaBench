#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct charlcd {int dummy; } ;
struct TYPE_3__ {scalar_t__ bl; } ;
struct TYPE_4__ {TYPE_1__ pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_BIT_BL ; 
 scalar_t__ PIN_NONE ; 
 int /*<<< orphan*/  bits ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ lcd ; 
 int /*<<< orphan*/  panel_set_bits () ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lcd_backlight(struct charlcd *charlcd, int on)
{
	if (lcd.pins.bl == PIN_NONE)
		return;

	/* The backlight is activated by setting the AUTOFEED line to +5V  */
	spin_lock_irq(&pprt_lock);
	if (on)
		set_bit(LCD_BIT_BL, bits);
	else
		clear_bit(LCD_BIT_BL, bits);
	panel_set_bits();
	spin_unlock_irq(&pprt_lock);
}