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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int FALSE ; 
 scalar_t__ I40E_SR_SECTOR_SIZE_IN_WORDS ; 
 int I40E_SUCCESS ; 
 scalar_t__ LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int i40e_read_nvm_aq (struct i40e_hw*,int,scalar_t__,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum i40e_status_code i40e_read_nvm_buffer_aq(struct i40e_hw *hw, u16 offset,
						     u16 *words, u16 *data)
{
	enum i40e_status_code ret_code;
	u16 read_size = *words;
	bool last_cmd = FALSE;
	u16 words_read = 0;
	u16 i = 0;

	DEBUGFUNC("i40e_read_nvm_buffer_aq");

	do {
		/* Calculate number of bytes we should read in this step.
		 * FVL AQ do not allow to read more than one page at a time or
		 * to cross page boundaries.
		 */
		if (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)
			read_size = min(*words,
					(u16)(I40E_SR_SECTOR_SIZE_IN_WORDS -
				      (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)));
		else
			read_size = min((*words - words_read),
					I40E_SR_SECTOR_SIZE_IN_WORDS);

		/* Check if this is last command, if so set proper flag */
		if ((words_read + read_size) >= *words)
			last_cmd = TRUE;

		ret_code = i40e_read_nvm_aq(hw, 0x0, offset, read_size,
					    data + words_read, last_cmd);
		if (ret_code != I40E_SUCCESS)
			goto read_nvm_buffer_aq_exit;

		/* Increment counter for words already read and move offset to
		 * new read location
		 */
		words_read += read_size;
		offset += read_size;
	} while (words_read < *words);

	for (i = 0; i < *words; i++)
		data[i] = LE16_TO_CPU(((__le16 *)data)[i]);

read_nvm_buffer_aq_exit:
	*words = words_read;
	return ret_code;
}