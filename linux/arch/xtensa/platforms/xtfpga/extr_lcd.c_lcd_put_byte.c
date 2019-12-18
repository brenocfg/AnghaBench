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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 

__attribute__((used)) static void lcd_put_byte(u8 *addr, u8 data)
{
#ifdef CONFIG_XTFPGA_LCD_8BIT_ACCESS
	WRITE_ONCE(*addr, data);
#else
	WRITE_ONCE(*addr, data & 0xf0);
	WRITE_ONCE(*addr, (data << 4) & 0xf0);
#endif
}