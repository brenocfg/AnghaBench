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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_nvm_image_att {int length; int /*<<< orphan*/  start_addr; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum ecore_nvm_images { ____Placeholder_ecore_nvm_images } ecore_nvm_images ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_STORAGE ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (int /*<<< orphan*/ *,int) ; 
 int ecore_mcp_get_nvm_image_att (struct ecore_hwfn*,struct ecore_ptt*,int,struct ecore_nvm_image_att*) ; 
 int ecore_mcp_nvm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

enum _ecore_status_t ecore_mcp_get_nvm_image(struct ecore_hwfn *p_hwfn,
					     struct ecore_ptt *p_ptt,
					     enum ecore_nvm_images image_id,
					     u8 *p_buffer, u32 buffer_len)
{
	struct ecore_nvm_image_att image_att;
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(p_buffer, buffer_len);

	rc = ecore_mcp_get_nvm_image_att(p_hwfn, p_ptt, image_id, &image_att);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Validate sizes - both the image's and the supplied buffer's */
	if (image_att.length <= 4) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
			   "Image [%d] is too small - only %d bytes\n",
			   image_id, image_att.length);
		return ECORE_INVAL;
	}

	/* Each NVM image is suffixed by CRC; Upper-layer has no need for it */
	image_att.length -= 4;

	if (image_att.length > buffer_len) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
			   "Image [%d] is too big - %08x bytes where only %08x are available\n",
			   image_id, image_att.length, buffer_len);
		return ECORE_NOMEM;
	}

	return ecore_mcp_nvm_read(p_hwfn->p_dev, image_att.start_addr,
				  p_buffer, image_att.length);
}