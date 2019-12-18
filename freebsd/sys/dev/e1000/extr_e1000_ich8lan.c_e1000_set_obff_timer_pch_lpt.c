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
struct e1000_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int E1000_ERR_CONFIG ; 
 int E1000_ITR_MASK ; 
 int E1000_ITR_MULT ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_SVCR ; 
 int E1000_SVCR_OFF_TIMER_MASK ; 
 int E1000_SVCR_OFF_TIMER_SHIFT ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_set_obff_timer_pch_lpt(struct e1000_hw *hw, u32 itr)
{
	u32 svcr;
	s32 timer;

	DEBUGFUNC("e1000_set_obff_timer_pch_lpt");

	/* Convert ITR value into microseconds for OBFF timer */
	timer = itr & E1000_ITR_MASK;
	timer = (timer * E1000_ITR_MULT) / 1000;

	if ((timer < 0) || (timer > E1000_ITR_MASK)) {
		DEBUGOUT1("Invalid OBFF timer %d\n", timer);
		return -E1000_ERR_CONFIG;
	}

	svcr = E1000_READ_REG(hw, E1000_SVCR);
	svcr &= ~E1000_SVCR_OFF_TIMER_MASK;
	svcr |= timer << E1000_SVCR_OFF_TIMER_SHIFT;
	E1000_WRITE_REG(hw, E1000_SVCR, svcr);

	return E1000_SUCCESS;
}