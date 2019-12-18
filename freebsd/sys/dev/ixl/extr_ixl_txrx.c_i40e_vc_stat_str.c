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
struct i40e_hw {char const* err_str; } ;
typedef  enum virtchnl_status_code { ____Placeholder_virtchnl_status_code } virtchnl_status_code ;

/* Variables and functions */
#define  VIRTCHNL_ERR_PARAM 133 
#define  VIRTCHNL_STATUS_ERR_CQP_COMPL_ERROR 132 
#define  VIRTCHNL_STATUS_ERR_INVALID_VF_ID 131 
#define  VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH 130 
#define  VIRTCHNL_STATUS_NOT_SUPPORTED 129 
#define  VIRTCHNL_STATUS_SUCCESS 128 
 int /*<<< orphan*/  snprintf (char const*,int,char*,int) ; 

const char *
i40e_vc_stat_str(struct i40e_hw *hw, enum virtchnl_status_code stat_err)
{
	switch (stat_err) {
	case VIRTCHNL_STATUS_SUCCESS:
		return "OK";
	case VIRTCHNL_ERR_PARAM:
		return "VIRTCHNL_ERR_PARAM";
	case VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH:
		return "VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH";
	case VIRTCHNL_STATUS_ERR_CQP_COMPL_ERROR:
		return "VIRTCHNL_STATUS_ERR_CQP_COMPL_ERROR";
	case VIRTCHNL_STATUS_ERR_INVALID_VF_ID:
		return "VIRTCHNL_STATUS_ERR_INVALID_VF_ID";
	case VIRTCHNL_STATUS_NOT_SUPPORTED:
		return "VIRTCHNL_STATUS_NOT_SUPPORTED";
	}

	snprintf(hw->err_str, sizeof(hw->err_str), "%d", stat_err);
	return hw->err_str;
}