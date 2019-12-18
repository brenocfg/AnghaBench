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
typedef  int u8 ;
typedef  int u32 ;
struct i40e_nvm_info {int sr_size; int /*<<< orphan*/  blank_nvm_mode; int /*<<< orphan*/  timeout; } ;
struct i40e_hw {struct i40e_nvm_info nvm; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int I40E_ERR_NVM_BLANK_MODE ; 
 int /*<<< orphan*/  I40E_GLNVM_FLA ; 
 int I40E_GLNVM_FLA_LOCKED_MASK ; 
 int /*<<< orphan*/  I40E_GLNVM_GENS ; 
 int I40E_GLNVM_GENS_SR_SIZE_MASK ; 
 int I40E_GLNVM_GENS_SR_SIZE_SHIFT ; 
 int /*<<< orphan*/  I40E_MAX_NVM_TIMEOUT ; 
 int I40E_SR_WORDS_IN_1KB ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_init_nvm(struct i40e_hw *hw)
{
	struct i40e_nvm_info *nvm = &hw->nvm;
	enum i40e_status_code ret_code = I40E_SUCCESS;
	u32 fla, gens;
	u8 sr_size;

	DEBUGFUNC("i40e_init_nvm");

	/* The SR size is stored regardless of the nvm programming mode
	 * as the blank mode may be used in the factory line.
	 */
	gens = rd32(hw, I40E_GLNVM_GENS);
	sr_size = ((gens & I40E_GLNVM_GENS_SR_SIZE_MASK) >>
			   I40E_GLNVM_GENS_SR_SIZE_SHIFT);
	/* Switching to words (sr_size contains power of 2KB) */
	nvm->sr_size = BIT(sr_size) * I40E_SR_WORDS_IN_1KB;

	/* Check if we are in the normal or blank NVM programming mode */
	fla = rd32(hw, I40E_GLNVM_FLA);
	if (fla & I40E_GLNVM_FLA_LOCKED_MASK) { /* Normal programming mode */
		/* Max NVM timeout */
		nvm->timeout = I40E_MAX_NVM_TIMEOUT;
		nvm->blank_nvm_mode = FALSE;
	} else { /* Blank programming mode */
		nvm->blank_nvm_mode = TRUE;
		ret_code = I40E_ERR_NVM_BLANK_MODE;
		i40e_debug(hw, I40E_DEBUG_NVM, "NVM init error: unsupported blank mode.\n");
	}

	return ret_code;
}