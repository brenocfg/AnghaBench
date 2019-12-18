#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ibv_rwq_ind_table_init_attr {scalar_t__ comp_mask; int log_ind_tbl_size; TYPE_1__** ind_tbl; } ;
struct ibv_rwq_ind_table {struct ibv_context* context; int /*<<< orphan*/  ind_tbl_num; int /*<<< orphan*/  ind_tbl_handle; } ;
struct ibv_create_rwq_ind_table_resp {size_t response_length; int /*<<< orphan*/  ind_tbl_num; int /*<<< orphan*/  ind_tbl_handle; } ;
struct ibv_create_rwq_ind_table {int log_ind_tbl_size; scalar_t__ comp_mask; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;
struct TYPE_2__ {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_RWQ_IND_TBL ; 
 int EINVAL ; 
 scalar_t__ IBV_CREATE_IND_TABLE_RESERVED ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP_EX_V (struct ibv_create_rwq_ind_table*,size_t,size_t,int /*<<< orphan*/ ,struct ibv_create_rwq_ind_table_resp*,size_t,size_t) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_rwq_ind_table_resp*,size_t) ; 
 int errno ; 
 int write (int /*<<< orphan*/ ,struct ibv_create_rwq_ind_table*,size_t) ; 

int ibv_cmd_create_rwq_ind_table(struct ibv_context *context,
				 struct ibv_rwq_ind_table_init_attr *init_attr,
				 struct ibv_rwq_ind_table *rwq_ind_table,
				 struct ibv_create_rwq_ind_table *cmd,
				 size_t cmd_core_size,
				 size_t cmd_size,
				 struct ibv_create_rwq_ind_table_resp *resp,
				 size_t resp_core_size,
				 size_t resp_size)
{
	int err, i;
	uint32_t required_tbl_size, alloc_tbl_size;
	uint32_t *tbl_start;
	int num_tbl_entries;

	if (init_attr->comp_mask >= IBV_CREATE_IND_TABLE_RESERVED)
		return EINVAL;

	alloc_tbl_size = cmd_core_size - sizeof(*cmd);
	num_tbl_entries = 1 << init_attr->log_ind_tbl_size;

	/* Data must be u64 aligned */
	required_tbl_size = (num_tbl_entries * sizeof(uint32_t)) < sizeof(uint64_t) ?
			sizeof(uint64_t) : (num_tbl_entries * sizeof(uint32_t));

	if (alloc_tbl_size < required_tbl_size)
		return EINVAL;

	tbl_start = (uint32_t *)((uint8_t *)cmd + sizeof(*cmd));
	for (i = 0; i < num_tbl_entries; i++)
		tbl_start[i] = init_attr->ind_tbl[i]->handle;

	IBV_INIT_CMD_RESP_EX_V(cmd, cmd_core_size, cmd_size,
			       CREATE_RWQ_IND_TBL, resp,
			       resp_core_size, resp_size);
	cmd->log_ind_tbl_size = init_attr->log_ind_tbl_size;
	cmd->comp_mask = 0;

	err = write(context->cmd_fd, cmd, cmd_size);
	if (err != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	if (resp->response_length < resp_core_size)
		return EINVAL;

	rwq_ind_table->ind_tbl_handle = resp->ind_tbl_handle;
	rwq_ind_table->ind_tbl_num = resp->ind_tbl_num;
	rwq_ind_table->context = context;
	return 0;
}