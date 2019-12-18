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
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int i40e_read_nvm_aq (struct i40e_hw*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40e_status_code i40e_read_nvm_word_aq(struct i40e_hw *hw, u16 offset,
						   u16 *data)
{
	enum i40e_status_code ret_code = I40E_ERR_TIMEOUT;

	DEBUGFUNC("i40e_read_nvm_word_aq");

	ret_code = i40e_read_nvm_aq(hw, 0x0, offset, 1, data, TRUE);
	*data = LE16_TO_CPU(*(__le16 *)data);

	return ret_code;
}