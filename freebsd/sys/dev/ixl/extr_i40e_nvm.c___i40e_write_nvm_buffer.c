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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (size_t) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int i40e_write_nvm_aq (struct i40e_hw*,int /*<<< orphan*/ ,size_t,size_t,void*,int /*<<< orphan*/ ) ; 

enum i40e_status_code __i40e_write_nvm_buffer(struct i40e_hw *hw,
					      u8 module_pointer, u32 offset,
					      u16 words, void *data)
{
	__le16 *le_word_ptr = (__le16 *)data;
	u16 *word_ptr = (u16 *)data;
	u32 i = 0;

	DEBUGFUNC("i40e_write_nvm_buffer");

	for (i = 0; i < words; i++)
		le_word_ptr[i] = CPU_TO_LE16(word_ptr[i]);

	/* Here we will only write one buffer as the size of the modules
	 * mirrored in the Shadow RAM is always less than 4K.
	 */
	return i40e_write_nvm_aq(hw, module_pointer, offset, words,
				 data, FALSE);
}