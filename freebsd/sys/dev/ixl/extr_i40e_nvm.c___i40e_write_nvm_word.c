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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int i40e_write_nvm_aq (struct i40e_hw*,int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 

enum i40e_status_code __i40e_write_nvm_word(struct i40e_hw *hw, u32 offset,
					    void *data)
{
	DEBUGFUNC("i40e_write_nvm_word");

	*((__le16 *)data) = CPU_TO_LE16(*((u16 *)data));

	/* Value 0x00 below means that we treat SR as a flat mem */
	return i40e_write_nvm_aq(hw, 0x00, offset, 1, data, FALSE);
}