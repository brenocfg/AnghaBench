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
typedef  size_t u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int I40E_SUCCESS ; 
 int i40e_read_nvm_word_srctl (struct i40e_hw*,size_t,size_t*) ; 

__attribute__((used)) static enum i40e_status_code i40e_read_nvm_buffer_srctl(struct i40e_hw *hw, u16 offset,
							u16 *words, u16 *data)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	u16 index, word;

	DEBUGFUNC("i40e_read_nvm_buffer_srctl");

	/* Loop through the selected region */
	for (word = 0; word < *words; word++) {
		index = offset + word;
		ret_code = i40e_read_nvm_word_srctl(hw, index, &data[word]);
		if (ret_code != I40E_SUCCESS)
			break;
	}

	/* Update the number of words read from the Shadow RAM */
	*words = word;

	return ret_code;
}