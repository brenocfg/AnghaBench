#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int cmd; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ qlnx_nvram_t ;
struct TYPE_15__ {int /*<<< orphan*/  mcp_nvm_resp; } ;
struct TYPE_17__ {TYPE_11__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_NVM_WRITE_NVRAM ; 
 int /*<<< orphan*/  ECORE_PUT_FILE_DATA ; 
 int EINVAL ; 
#define  QLNX_NVRAM_CMD_DEL_FILE 134 
#define  QLNX_NVRAM_CMD_GET_NVRAM_RESP 133 
#define  QLNX_NVRAM_CMD_PUT_FILE_BEGIN 132 
#define  QLNX_NVRAM_CMD_PUT_FILE_DATA 131 
#define  QLNX_NVRAM_CMD_READ_NVRAM 130 
#define  QLNX_NVRAM_CMD_SET_SECURE_MODE 129 
#define  QLNX_NVRAM_CMD_WRITE_NVRAM 128 
 int /*<<< orphan*/  QL_DPRINT9 (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int ecore_mcp_nvm_del_file (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int ecore_mcp_nvm_put_file_begin (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int ecore_mcp_nvm_set_secure_mode (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int qlnx_get_nvram_resp (TYPE_2__*,TYPE_1__*) ; 
 int qlnx_read_nvram (TYPE_2__*,TYPE_1__*) ; 
 int qlnx_write_nvram (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_nvram(qlnx_host_t *ha, qlnx_nvram_t *nvram)
{
	int ret = 0;

	switch (nvram->cmd) {

	case QLNX_NVRAM_CMD_WRITE_NVRAM:
		ret = qlnx_write_nvram(ha, nvram, ECORE_NVM_WRITE_NVRAM);
		break;

	case QLNX_NVRAM_CMD_PUT_FILE_DATA:
		ret = qlnx_write_nvram(ha, nvram, ECORE_PUT_FILE_DATA);
		break;

	case QLNX_NVRAM_CMD_READ_NVRAM:
		ret = qlnx_read_nvram(ha, nvram);
		break;

	case QLNX_NVRAM_CMD_SET_SECURE_MODE:
		ret = ecore_mcp_nvm_set_secure_mode(&ha->cdev, nvram->offset);

		QL_DPRINT9(ha, "QLNX_NVRAM_CMD_SET_SECURE_MODE \
			 resp = 0x%x ret = 0x%x exit\n",
			 ha->cdev.mcp_nvm_resp, ret);
		break;

	case QLNX_NVRAM_CMD_DEL_FILE:
		ret = ecore_mcp_nvm_del_file(&ha->cdev, nvram->offset);

		QL_DPRINT9(ha, "QLNX_NVRAM_CMD_DEL_FILE \
			 resp = 0x%x ret = 0x%x exit\n",
			ha->cdev.mcp_nvm_resp, ret);
		break;

	case QLNX_NVRAM_CMD_PUT_FILE_BEGIN:
		ret = ecore_mcp_nvm_put_file_begin(&ha->cdev, nvram->offset);

		QL_DPRINT9(ha, "QLNX_NVRAM_CMD_PUT_FILE_BEGIN \
			 resp = 0x%x ret = 0x%x exit\n",
			ha->cdev.mcp_nvm_resp, ret);
		break;

	case QLNX_NVRAM_CMD_GET_NVRAM_RESP:
		ret = qlnx_get_nvram_resp(ha, nvram);
		break;

	default:
		ret = EINVAL;
		break;
	}

	return (ret);
}