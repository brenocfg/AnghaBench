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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 int /*<<< orphan*/  e1000_read_flash_data_ich8lan (struct e1000_hw*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 e1000_read_flash_word_ich8lan(struct e1000_hw *hw, u32 offset,
					 u16 *data)
{
	DEBUGFUNC("e1000_read_flash_word_ich8lan");

	if (!data)
		return -E1000_ERR_NVM;

	/* Must convert offset into bytes. */
	offset <<= 1;

	return e1000_read_flash_data_ich8lan(hw, offset, 2, data);
}