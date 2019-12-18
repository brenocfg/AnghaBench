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
struct i40e_hw {int dummy; } ;
struct i40e_filter_control_settings {int fcoe_filt_num; int fcoe_cntx_num; int pe_filt_num; int pe_cntx_num; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_DMA_CNTX_BASE_SIZE ; 
#define  I40E_DMA_CNTX_SIZE_128K 148 
#define  I40E_DMA_CNTX_SIZE_16K 147 
#define  I40E_DMA_CNTX_SIZE_1K 146 
#define  I40E_DMA_CNTX_SIZE_256K 145 
#define  I40E_DMA_CNTX_SIZE_2K 144 
#define  I40E_DMA_CNTX_SIZE_32K 143 
#define  I40E_DMA_CNTX_SIZE_4K 142 
#define  I40E_DMA_CNTX_SIZE_512 141 
#define  I40E_DMA_CNTX_SIZE_64K 140 
#define  I40E_DMA_CNTX_SIZE_8K 139 
 int I40E_ERR_INVALID_SIZE ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_GLHMC_FCOEFMAX ; 
 int I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_MASK ; 
 int I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_SHIFT ; 
 int I40E_HASH_FILTER_BASE_SIZE ; 
#define  I40E_HASH_FILTER_SIZE_128K 138 
#define  I40E_HASH_FILTER_SIZE_16K 137 
#define  I40E_HASH_FILTER_SIZE_1K 136 
#define  I40E_HASH_FILTER_SIZE_1M 135 
#define  I40E_HASH_FILTER_SIZE_256K 134 
#define  I40E_HASH_FILTER_SIZE_2K 133 
#define  I40E_HASH_FILTER_SIZE_32K 132 
#define  I40E_HASH_FILTER_SIZE_4K 131 
#define  I40E_HASH_FILTER_SIZE_512K 130 
#define  I40E_HASH_FILTER_SIZE_64K 129 
#define  I40E_HASH_FILTER_SIZE_8K 128 
 int I40E_SUCCESS ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40e_status_code i40e_validate_filter_settings(struct i40e_hw *hw,
				struct i40e_filter_control_settings *settings)
{
	u32 fcoe_cntx_size, fcoe_filt_size;
	u32 pe_cntx_size, pe_filt_size;
	u32 fcoe_fmax;

	u32 val;

	/* Validate FCoE settings passed */
	switch (settings->fcoe_filt_num) {
	case I40E_HASH_FILTER_SIZE_1K:
	case I40E_HASH_FILTER_SIZE_2K:
	case I40E_HASH_FILTER_SIZE_4K:
	case I40E_HASH_FILTER_SIZE_8K:
	case I40E_HASH_FILTER_SIZE_16K:
	case I40E_HASH_FILTER_SIZE_32K:
		fcoe_filt_size = I40E_HASH_FILTER_BASE_SIZE;
		fcoe_filt_size <<= (u32)settings->fcoe_filt_num;
		break;
	default:
		return I40E_ERR_PARAM;
	}

	switch (settings->fcoe_cntx_num) {
	case I40E_DMA_CNTX_SIZE_512:
	case I40E_DMA_CNTX_SIZE_1K:
	case I40E_DMA_CNTX_SIZE_2K:
	case I40E_DMA_CNTX_SIZE_4K:
		fcoe_cntx_size = I40E_DMA_CNTX_BASE_SIZE;
		fcoe_cntx_size <<= (u32)settings->fcoe_cntx_num;
		break;
	default:
		return I40E_ERR_PARAM;
	}

	/* Validate PE settings passed */
	switch (settings->pe_filt_num) {
	case I40E_HASH_FILTER_SIZE_1K:
	case I40E_HASH_FILTER_SIZE_2K:
	case I40E_HASH_FILTER_SIZE_4K:
	case I40E_HASH_FILTER_SIZE_8K:
	case I40E_HASH_FILTER_SIZE_16K:
	case I40E_HASH_FILTER_SIZE_32K:
	case I40E_HASH_FILTER_SIZE_64K:
	case I40E_HASH_FILTER_SIZE_128K:
	case I40E_HASH_FILTER_SIZE_256K:
	case I40E_HASH_FILTER_SIZE_512K:
	case I40E_HASH_FILTER_SIZE_1M:
		pe_filt_size = I40E_HASH_FILTER_BASE_SIZE;
		pe_filt_size <<= (u32)settings->pe_filt_num;
		break;
	default:
		return I40E_ERR_PARAM;
	}

	switch (settings->pe_cntx_num) {
	case I40E_DMA_CNTX_SIZE_512:
	case I40E_DMA_CNTX_SIZE_1K:
	case I40E_DMA_CNTX_SIZE_2K:
	case I40E_DMA_CNTX_SIZE_4K:
	case I40E_DMA_CNTX_SIZE_8K:
	case I40E_DMA_CNTX_SIZE_16K:
	case I40E_DMA_CNTX_SIZE_32K:
	case I40E_DMA_CNTX_SIZE_64K:
	case I40E_DMA_CNTX_SIZE_128K:
	case I40E_DMA_CNTX_SIZE_256K:
		pe_cntx_size = I40E_DMA_CNTX_BASE_SIZE;
		pe_cntx_size <<= (u32)settings->pe_cntx_num;
		break;
	default:
		return I40E_ERR_PARAM;
	}

	/* FCHSIZE + FCDSIZE should not be greater than PMFCOEFMAX */
	val = rd32(hw, I40E_GLHMC_FCOEFMAX);
	fcoe_fmax = (val & I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_MASK)
		     >> I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_SHIFT;
	if (fcoe_filt_size + fcoe_cntx_size >  fcoe_fmax)
		return I40E_ERR_INVALID_SIZE;

	return I40E_SUCCESS;
}