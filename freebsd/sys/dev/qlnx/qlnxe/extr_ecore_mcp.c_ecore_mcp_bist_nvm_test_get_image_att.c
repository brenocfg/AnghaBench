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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct bist_nvm_image_att {int return_code; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX ; 
 int DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_OFFSET ; 
 int DRV_MB_PARAM_BIST_TEST_INDEX_OFFSET ; 
 int /*<<< orphan*/  DRV_MSG_CODE_BIST_TEST ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_CODE_OK ; 
 int ecore_mcp_nvm_rd_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 

enum _ecore_status_t ecore_mcp_bist_nvm_test_get_image_att(
	struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
	struct bist_nvm_image_att *p_image_att, u32 image_index)
{
	u32 buf_size, nvm_offset, resp, param;
	enum _ecore_status_t rc;

	nvm_offset = (DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX <<
				    DRV_MB_PARAM_BIST_TEST_INDEX_OFFSET);
	nvm_offset |= (image_index <<
		       DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_OFFSET);
	rc = ecore_mcp_nvm_rd_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BIST_TEST,
				  nvm_offset, &resp, &param, &buf_size,
				  (u32 *)p_image_att);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (((resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (p_image_att->return_code != 1))
		rc = ECORE_UNKNOWN_ERROR;

	return rc;
}