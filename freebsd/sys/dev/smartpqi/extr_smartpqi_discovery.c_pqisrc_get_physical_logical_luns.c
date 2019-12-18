#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  list_length; } ;
struct TYPE_10__ {TYPE_1__ header; int /*<<< orphan*/  list_length; } ;
typedef  TYPE_2__ reportlun_header_t ;
typedef  TYPE_2__ reportlun_data_ext_t ;
typedef  int /*<<< orphan*/  report_lun_header ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 size_t BE_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_DISC (char*) ; 
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_STATUS_FAILURE ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* os_mem_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,void*,size_t) ; 
 int pqisrc_report_luns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,size_t) ; 

__attribute__((used)) static int pqisrc_get_physical_logical_luns(pqisrc_softstate_t *softs, uint8_t cmd,
		reportlun_data_ext_t **buff, size_t *data_length)
{
	int ret;
	size_t list_len;
	size_t data_len;
	size_t new_lun_list_length;
	reportlun_data_ext_t *lun_data;
	reportlun_header_t report_lun_header;

	DBG_FUNC("IN\n");

	ret = pqisrc_report_luns(softs, cmd, &report_lun_header,
		sizeof(report_lun_header));

	if (ret) {
		DBG_ERR("failed return code: %d\n", ret);
		return ret;
	}
	list_len = BE_32(report_lun_header.list_length);

retry:
	data_len = sizeof(reportlun_header_t) + list_len;
	*data_length = data_len;

	lun_data = os_mem_alloc(softs, data_len);

	if (!lun_data) {
		DBG_ERR("failed to allocate memory for lun_data\n");
		return PQI_STATUS_FAILURE;
	}
		
	if (list_len == 0) {
		DBG_DISC("list_len is 0\n");
		memcpy(lun_data, &report_lun_header, sizeof(report_lun_header));
		goto out;
	}

	ret = pqisrc_report_luns(softs, cmd, lun_data, data_len);

	if (ret) {
		DBG_ERR("error\n");
		goto error;
	}

	new_lun_list_length = BE_32(lun_data->header.list_length);

	if (new_lun_list_length > list_len) {
		list_len = new_lun_list_length;
		os_mem_free(softs, (void *)lun_data, data_len);
		goto retry;
	}

out:
	*buff = lun_data;
	DBG_FUNC("OUT\n");
	return 0;

error:
	os_mem_free(softs, (void *)lun_data, data_len);
	DBG_ERR("FAILED\n");
	return ret;
}