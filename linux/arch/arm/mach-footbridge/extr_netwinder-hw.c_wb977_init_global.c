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
 int /*<<< orphan*/  wb977_wb (int,int) ; 

__attribute__((used)) static inline void wb977_init_global(void)
{
	/*
	 * Enable R/W config registers
	 */
	wb977_wb(0x26, 0x40);

	/*
	 * Power down FDC (not used)
	 */
	wb977_wb(0x22, 0xfe);

	/*
	 * GP12, GP11, CIRRX, IRRXH, GP10
	 */
	wb977_wb(0x2a, 0xc1);

	/*
	 * GP23, GP22, GP21, GP20, GP13
	 */
	wb977_wb(0x2b, 0x6b);

	/*
	 * GP17, GP16, GP15, GP14
	 */
	wb977_wb(0x2c, 0x55);
}