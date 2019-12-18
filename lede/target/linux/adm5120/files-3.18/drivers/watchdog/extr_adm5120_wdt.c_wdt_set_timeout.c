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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_REG_WDOG0 ; 
 int /*<<< orphan*/  SW_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 int timeout ; 

__attribute__((used)) static inline void wdt_set_timeout(void)
{
	u32 val = (1 << 31) | (((timeout * 100) & 0x7FFF) << 16);
	SW_WRITE_REG(SWITCH_REG_WDOG0, val);
}