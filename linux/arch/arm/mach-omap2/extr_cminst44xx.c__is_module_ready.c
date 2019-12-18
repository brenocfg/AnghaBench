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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ CLKCTRL_IDLEST_FUNCTIONAL ; 
 scalar_t__ CLKCTRL_IDLEST_INTERFACE_IDLE ; 
 scalar_t__ _clkctrl_idlest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _is_module_ready(u8 part, u16 inst, u16 clkctrl_offs)
{
	u32 v;

	v = _clkctrl_idlest(part, inst, clkctrl_offs);

	return (v == CLKCTRL_IDLEST_FUNCTIONAL ||
		v == CLKCTRL_IDLEST_INTERFACE_IDLE) ? true : false;
}