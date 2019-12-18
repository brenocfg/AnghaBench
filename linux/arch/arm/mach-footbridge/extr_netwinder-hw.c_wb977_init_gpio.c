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
 int /*<<< orphan*/  GP1_IO_BASE ; 
 int /*<<< orphan*/  GP2_IO_BASE ; 
 int GPIO_DONE ; 
 int GPIO_FAN ; 
 int GPIO_RED_LED ; 
 int GPIO_WDTIMER ; 
 int /*<<< orphan*/  __gpio_modify_io (int,int) ; 
 int current_gpio_io ; 
 int /*<<< orphan*/  nw_gpio_lock ; 
 int /*<<< orphan*/  nw_gpio_modify_op (int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wb977_device_enable () ; 
 int /*<<< orphan*/  wb977_device_select (int) ; 
 int /*<<< orphan*/  wb977_wb (int,int) ; 
 int /*<<< orphan*/  wb977_ww (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wb977_init_gpio(void)
{
	unsigned long flags;

	/*
	 * Set up initial I/O definitions
	 */
	current_gpio_io = -1;
	__gpio_modify_io(-1, GPIO_DONE | GPIO_WDTIMER);

	wb977_device_select(7);

	/*
	 * Group1 base address
	 */
	wb977_ww(0x60, GP1_IO_BASE);
	wb977_ww(0x62, 0);
	wb977_ww(0x64, 0);

	/*
	 * GP10 (Orage button) IRQ 10, active high, edge trigger
	 */
	wb977_wb(0x70, 10);
	wb977_wb(0x71, 0x02);

	/*
	 * GP10: Debounce filter enabled, IRQ, input
	 */
	wb977_wb(0xe0, 0x19);

	/*
	 * Enable Group1
	 */
	wb977_device_enable();

	wb977_device_select(8);

	/*
	 * Group2 base address
	 */
	wb977_ww(0x60, GP2_IO_BASE);

	/*
	 * Clear watchdog timer regs
	 *  - timer disable
	 */
	wb977_wb(0xf2, 0x00);

	/*
	 *  - disable LED, no mouse nor keyboard IRQ
	 */
	wb977_wb(0xf3, 0x00);

	/*
	 *  - timer counting, disable power LED, disable timeouot
	 */
	wb977_wb(0xf4, 0x00);

	/*
	 * Enable group2
	 */
	wb977_device_enable();

	/*
	 * Set Group1/Group2 outputs
	 */
	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_gpio_modify_op(-1, GPIO_RED_LED | GPIO_FAN);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
}