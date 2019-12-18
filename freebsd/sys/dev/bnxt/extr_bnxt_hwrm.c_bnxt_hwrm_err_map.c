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
typedef  int uint16_t ;

/* Variables and functions */
 int EACCES ; 
 int EDOOFUS ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
#define  HWRM_ERR_CODE_CMD_NOT_SUPPORTED 137 
#define  HWRM_ERR_CODE_FAIL 136 
#define  HWRM_ERR_CODE_HWRM_ERROR 135 
#define  HWRM_ERR_CODE_INVALID_ENABLES 134 
#define  HWRM_ERR_CODE_INVALID_FLAGS 133 
#define  HWRM_ERR_CODE_INVALID_PARAMS 132 
#define  HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED 131 
#define  HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR 130 
#define  HWRM_ERR_CODE_SUCCESS 129 
#define  HWRM_ERR_CODE_UNKNOWN_ERR 128 

__attribute__((used)) static int
bnxt_hwrm_err_map(uint16_t err)
{
	int rc;

	switch (err) {
	case HWRM_ERR_CODE_SUCCESS:
		return 0;
	case HWRM_ERR_CODE_INVALID_PARAMS:
	case HWRM_ERR_CODE_INVALID_FLAGS:
	case HWRM_ERR_CODE_INVALID_ENABLES:
		return EINVAL;
	case HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED:
		return EACCES;
	case HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR:
		return ENOMEM;
	case HWRM_ERR_CODE_CMD_NOT_SUPPORTED:
		return ENOSYS;
	case HWRM_ERR_CODE_FAIL:
		return EIO;
	case HWRM_ERR_CODE_HWRM_ERROR:
	case HWRM_ERR_CODE_UNKNOWN_ERR:
	default:
		return EDOOFUS;
	}

	return rc;
}