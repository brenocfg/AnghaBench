#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct i40e_virt_mem {scalar_t__ va; } ;
struct TYPE_2__ {int sr_size; } ;
struct i40e_hw {TYPE_1__ nvm; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int I40E_ERR_NVM_CHECKSUM ; 
 int /*<<< orphan*/  I40E_SR_PCIE_ALT_AUTO_LOAD_PTR ; 
 int I40E_SR_PCIE_ALT_MODULE_MAX_SIZE ; 
 int I40E_SR_SECTOR_SIZE_IN_WORDS ; 
 scalar_t__ I40E_SR_SW_CHECKSUM_BASE ; 
 int I40E_SR_SW_CHECKSUM_WORD ; 
 int I40E_SR_VPD_MODULE_MAX_SIZE ; 
 int /*<<< orphan*/  I40E_SR_VPD_PTR ; 
 int I40E_SUCCESS ; 
 int __i40e_read_nvm_buffer (struct i40e_hw*,int,int*,int*) ; 
 int __i40e_read_nvm_word (struct i40e_hw*,int /*<<< orphan*/ ,int*) ; 
 int i40e_allocate_virt_mem (struct i40e_hw*,struct i40e_virt_mem*,int) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,struct i40e_virt_mem*) ; 

enum i40e_status_code i40e_calc_nvm_checksum(struct i40e_hw *hw, u16 *checksum)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	struct i40e_virt_mem vmem;
	u16 pcie_alt_module = 0;
	u16 checksum_local = 0;
	u16 vpd_module = 0;
	u16 *data;
	u16 i = 0;

	DEBUGFUNC("i40e_calc_nvm_checksum");

	ret_code = i40e_allocate_virt_mem(hw, &vmem,
				    I40E_SR_SECTOR_SIZE_IN_WORDS * sizeof(u16));
	if (ret_code)
		goto i40e_calc_nvm_checksum_exit;
	data = (u16 *)vmem.va;

	/* read pointer to VPD area */
	ret_code = __i40e_read_nvm_word(hw, I40E_SR_VPD_PTR, &vpd_module);
	if (ret_code != I40E_SUCCESS) {
		ret_code = I40E_ERR_NVM_CHECKSUM;
		goto i40e_calc_nvm_checksum_exit;
	}

	/* read pointer to PCIe Alt Auto-load module */
	ret_code = __i40e_read_nvm_word(hw, I40E_SR_PCIE_ALT_AUTO_LOAD_PTR,
					&pcie_alt_module);
	if (ret_code != I40E_SUCCESS) {
		ret_code = I40E_ERR_NVM_CHECKSUM;
		goto i40e_calc_nvm_checksum_exit;
	}

	/* Calculate SW checksum that covers the whole 64kB shadow RAM
	 * except the VPD and PCIe ALT Auto-load modules
	 */
	for (i = 0; i < hw->nvm.sr_size; i++) {
		/* Read SR page */
		if ((i % I40E_SR_SECTOR_SIZE_IN_WORDS) == 0) {
			u16 words = I40E_SR_SECTOR_SIZE_IN_WORDS;

			ret_code = __i40e_read_nvm_buffer(hw, i, &words, data);
			if (ret_code != I40E_SUCCESS) {
				ret_code = I40E_ERR_NVM_CHECKSUM;
				goto i40e_calc_nvm_checksum_exit;
			}
		}

		/* Skip Checksum word */
		if (i == I40E_SR_SW_CHECKSUM_WORD)
			continue;
		/* Skip VPD module (convert byte size to word count) */
		if ((i >= (u32)vpd_module) &&
		    (i < ((u32)vpd_module +
		     (I40E_SR_VPD_MODULE_MAX_SIZE / 2)))) {
			continue;
		}
		/* Skip PCIe ALT module (convert byte size to word count) */
		if ((i >= (u32)pcie_alt_module) &&
		    (i < ((u32)pcie_alt_module +
		     (I40E_SR_PCIE_ALT_MODULE_MAX_SIZE / 2)))) {
			continue;
		}

		checksum_local += data[i % I40E_SR_SECTOR_SIZE_IN_WORDS];
	}

	*checksum = (u16)I40E_SR_SW_CHECKSUM_BASE - checksum_local;

i40e_calc_nvm_checksum_exit:
	i40e_free_virt_mem(hw, &vmem);
	return ret_code;
}