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
typedef  int /*<<< orphan*/  uint64_t ;
struct ibv_query_device_resp {int dummy; } ;
struct ibv_query_device {int dummy; } ;
struct ibv_device_attr {int /*<<< orphan*/  fw_ver; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_query_device*,size_t,int /*<<< orphan*/ ,struct ibv_query_device_resp*,int) ; 
 int /*<<< orphan*/  QUERY_DEVICE ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_query_device_resp*,int) ; 
 int /*<<< orphan*/  copy_query_dev_fields (struct ibv_device_attr*,struct ibv_query_device_resp*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_query_device*,size_t) ; 

int ibv_cmd_query_device(struct ibv_context *context,
			 struct ibv_device_attr *device_attr,
			 uint64_t *raw_fw_ver,
			 struct ibv_query_device *cmd, size_t cmd_size)
{
	struct ibv_query_device_resp resp;

	IBV_INIT_CMD_RESP(cmd, cmd_size, QUERY_DEVICE, &resp, sizeof resp);

	if (write(context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	memset(device_attr->fw_ver, 0, sizeof device_attr->fw_ver);
	copy_query_dev_fields(device_attr, &resp, raw_fw_ver);

	return 0;
}