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
struct i40e_hw {int pf_id; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int FALSE ; 
 int I40E_ALT_BW_VALID_MASK ; 
 int I40E_ALT_STRUCT_DWORDS_PER_PF ; 
 int I40E_ALT_STRUCT_FIRST_PF_OFFSET ; 
 int I40E_ALT_STRUCT_MAX_BW_OFFSET ; 
 int I40E_ALT_STRUCT_MIN_BW_OFFSET ; 
 int TRUE ; 
 int i40e_aq_alternate_read (struct i40e_hw*,int,int*,int,int*) ; 

enum i40e_status_code i40e_read_bw_from_alt_ram(struct i40e_hw *hw,
					u32 *max_bw, u32 *min_bw,
					bool *min_valid, bool *max_valid)
{
	enum i40e_status_code status;
	u32 max_bw_addr, min_bw_addr;

	/* Calculate the address of the min/max bw registers */
	max_bw_addr = I40E_ALT_STRUCT_FIRST_PF_OFFSET +
		      I40E_ALT_STRUCT_MAX_BW_OFFSET +
		      (I40E_ALT_STRUCT_DWORDS_PER_PF * hw->pf_id);
	min_bw_addr = I40E_ALT_STRUCT_FIRST_PF_OFFSET +
		      I40E_ALT_STRUCT_MIN_BW_OFFSET +
		      (I40E_ALT_STRUCT_DWORDS_PER_PF * hw->pf_id);

	/* Read the bandwidths from alt ram */
	status = i40e_aq_alternate_read(hw, max_bw_addr, max_bw,
					min_bw_addr, min_bw);

	if (*min_bw & I40E_ALT_BW_VALID_MASK)
		*min_valid = TRUE;
	else
		*min_valid = FALSE;

	if (*max_bw & I40E_ALT_BW_VALID_MASK)
		*max_valid = TRUE;
	else
		*max_valid = FALSE;

	return status;
}