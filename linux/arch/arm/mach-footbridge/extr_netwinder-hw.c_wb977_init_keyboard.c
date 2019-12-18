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
 int /*<<< orphan*/  wb977_device_enable () ; 
 int /*<<< orphan*/  wb977_device_select (int) ; 
 int /*<<< orphan*/  wb977_wb (int,int) ; 
 int /*<<< orphan*/  wb977_ww (int,int) ; 

__attribute__((used)) static inline void wb977_init_keyboard(void)
{
	wb977_device_select(5);

	/*
	 * Keyboard controller address
	 */
	wb977_ww(0x60, 0x0060);
	wb977_ww(0x62, 0x0064);

	/*
	 * Keyboard IRQ 1, active high, edge trigger
	 */
	wb977_wb(0x70, 1);
	wb977_wb(0x71, 0x02);

	/*
	 * Mouse IRQ 5, active high, edge trigger
	 */
	wb977_wb(0x72, 5);
	wb977_wb(0x73, 0x02);

	/*
	 * KBC 8MHz
	 */
	wb977_wb(0xf0, 0x40);

	/*
	 * Enable device
	 */
	wb977_device_enable();
}