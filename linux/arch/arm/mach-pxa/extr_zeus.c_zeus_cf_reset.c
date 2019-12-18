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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ZEUS_CPLD_CONTROL ; 
 int /*<<< orphan*/  ZEUS_CPLD_CONTROL_CF_RST ; 
 int /*<<< orphan*/  __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zeus_cf_reset(int state)
{
	u16 cpld_state = __raw_readw(ZEUS_CPLD_CONTROL);

	if (state)
		cpld_state |= ZEUS_CPLD_CONTROL_CF_RST;
	else
		cpld_state &= ~ZEUS_CPLD_CONTROL_CF_RST;

	__raw_writew(cpld_state, ZEUS_CPLD_CONTROL);
}