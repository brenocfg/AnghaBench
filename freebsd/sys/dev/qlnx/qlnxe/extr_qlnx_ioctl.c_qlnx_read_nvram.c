#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ qlnx_nvram_t ;
struct TYPE_9__ {int /*<<< orphan*/  mcp_nvm_resp; } ;
struct TYPE_8__ {TYPE_5__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_QLNXBUF ; 
 int /*<<< orphan*/  QL_DPRINT9 (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ecore_mcp_nvm_read (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qlnx_zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_read_nvram(qlnx_host_t *ha, qlnx_nvram_t *nvram)
{
	uint8_t *buf;
	int ret = 0;

	if ((nvram->data == NULL) || (nvram->data_len == 0))
		return (EINVAL);

	buf = qlnx_zalloc(nvram->data_len);

	ret = ecore_mcp_nvm_read(&ha->cdev, nvram->offset, buf,
		nvram->data_len);

	QL_DPRINT9(ha, " data = %p data_len = 0x%x \
		 resp = 0x%x ret = 0x%x exit\n",
		nvram->data, nvram->data_len, ha->cdev.mcp_nvm_resp, ret);

	if (ret == 0) {
		ret = copyout(buf, nvram->data, nvram->data_len);
	}

	free(buf, M_QLNXBUF);

	return (ret);
}