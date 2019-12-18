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
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40E_GLGEN_I2CCMD (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_GLGEN_I2CCMD_R_MASK ; 
 int /*<<< orphan*/  i40e_usec_delay (int) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
ixl_wait_for_i2c_completion(struct i40e_hw *hw, u8 portnum)
{
	s32 status = 0;
	u32 timeout = 100;
	u32 reg;
	do {
		reg = rd32(hw, I40E_GLGEN_I2CCMD(portnum));
		if ((reg & I40E_GLGEN_I2CCMD_R_MASK) != 0)
			break;
		i40e_usec_delay(10);
	} while (timeout-- > 0);

	if (timeout == 0)
		return I40E_ERR_TIMEOUT;
	else
		return status;
}