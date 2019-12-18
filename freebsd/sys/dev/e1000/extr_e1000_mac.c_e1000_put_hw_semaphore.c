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

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SWSM ; 
 int E1000_SWSM_SMBI ; 
 int E1000_SWSM_SWESMBI ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

void e1000_put_hw_semaphore(struct e1000_hw *hw)
{
	u32 swsm;

	DEBUGFUNC("e1000_put_hw_semaphore");

	swsm = E1000_READ_REG(hw, E1000_SWSM);

	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);

	E1000_WRITE_REG(hw, E1000_SWSM, swsm);
}