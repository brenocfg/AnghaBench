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
struct e1000_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_FD ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  FULL_DUPLEX ; 
 int /*<<< orphan*/  HALF_DUPLEX ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 

__attribute__((used)) static s32 e1000_get_link_up_info_vf(struct e1000_hw *hw, u16 *speed,
				     u16 *duplex)
{
	s32 status;

	DEBUGFUNC("e1000_get_link_up_info_vf");

	status = E1000_READ_REG(hw, E1000_STATUS);
	if (status & E1000_STATUS_SPEED_1000) {
		*speed = SPEED_1000;
		DEBUGOUT("1000 Mbs, ");
	} else if (status & E1000_STATUS_SPEED_100) {
		*speed = SPEED_100;
		DEBUGOUT("100 Mbs, ");
	} else {
		*speed = SPEED_10;
		DEBUGOUT("10 Mbs, ");
	}

	if (status & E1000_STATUS_FD) {
		*duplex = FULL_DUPLEX;
		DEBUGOUT("Full Duplex\n");
	} else {
		*duplex = HALF_DUPLEX;
		DEBUGOUT("Half Duplex\n");
	}

	return E1000_SUCCESS;
}