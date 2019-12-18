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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_nvm_image_att {int /*<<< orphan*/  length; int /*<<< orphan*/  start_addr; } ;
struct ecore_hwfn {int dummy; } ;
struct bist_nvm_image_att {int image_type; int /*<<< orphan*/  len; int /*<<< orphan*/  nvm_start_addr; } ;
typedef  enum nvm_image_type { ____Placeholder_nvm_image_type } nvm_image_type ;
typedef  enum ecore_nvm_images { ____Placeholder_ecore_nvm_images } ecore_nvm_images ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_STORAGE ; 
#define  ECORE_NVM_IMAGE_FCOE_CFG 130 
#define  ECORE_NVM_IMAGE_ISCSI_CFG 129 
#define  ECORE_NVM_IMAGE_MDUMP 128 
 int ECORE_SUCCESS ; 
 int NVM_TYPE_FCOE_CFG ; 
 int NVM_TYPE_ISCSI_CFG ; 
 int NVM_TYPE_MDUMP ; 
 int ecore_mcp_bist_nvm_test_get_image_att (struct ecore_hwfn*,struct ecore_ptt*,struct bist_nvm_image_att*,scalar_t__) ; 
 int ecore_mcp_bist_nvm_test_get_num_images (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*) ; 

enum _ecore_status_t
ecore_mcp_get_nvm_image_att(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			    enum ecore_nvm_images image_id,
			    struct ecore_nvm_image_att *p_image_att)
{
	struct bist_nvm_image_att mfw_image_att;
	enum nvm_image_type type;
	u32 num_images, i;
	enum _ecore_status_t rc;

	/* Translate image_id into MFW definitions */
	switch (image_id) {
	case ECORE_NVM_IMAGE_ISCSI_CFG:
		type = NVM_TYPE_ISCSI_CFG;
		break;
	case ECORE_NVM_IMAGE_FCOE_CFG:
		type = NVM_TYPE_FCOE_CFG;
		break;
	case ECORE_NVM_IMAGE_MDUMP:
		type = NVM_TYPE_MDUMP;
		break;
	default:
		DP_NOTICE(p_hwfn, false, "Unknown request of image_id %08x\n",
			  image_id);
		return ECORE_INVAL;
	}

	/* Learn number of images, then traverse and see if one fits */
	rc = ecore_mcp_bist_nvm_test_get_num_images(p_hwfn, p_ptt, &num_images);
	if (rc != ECORE_SUCCESS || !num_images)
		return ECORE_INVAL;

	for (i = 0; i < num_images; i++) {
		rc = ecore_mcp_bist_nvm_test_get_image_att(p_hwfn, p_ptt,
							   &mfw_image_att, i);
		if (rc != ECORE_SUCCESS)
			return rc;

		if (type == mfw_image_att.image_type)
			break;
	}
	if (i == num_images) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
			   "Failed to find nvram image of type %08x\n",
			   image_id);
		return ECORE_INVAL;
	}

	p_image_att->start_addr = mfw_image_att.nvm_start_addr;
	p_image_att->length = mfw_image_att.len;

	return ECORE_SUCCESS;
}