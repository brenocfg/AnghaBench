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
struct verbs_xrcd {int dummy; } ;
struct verbs_qp {int dummy; } ;
struct ibv_qp_init_attr_ex {int comp_mask; } ;
struct ibv_create_qp_resp_v4 {int dummy; } ;
struct ibv_create_qp_resp_v3 {int dummy; } ;
struct ibv_create_qp_resp {int dummy; } ;
struct ibv_create_qp_common {int dummy; } ;
struct ibv_create_qp {int /*<<< orphan*/  user_handle; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_QP ; 
 int ENOSYS ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_create_qp*,size_t,int /*<<< orphan*/ ,struct ibv_create_qp_resp*,size_t) ; 
 int IBV_QP_INIT_ATTR_PD ; 
 int IBV_QP_INIT_ATTR_XRCD ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_qp_resp*,size_t) ; 
 int abi_ver ; 
 int create_qp_ex_common (struct verbs_qp*,struct ibv_qp_init_attr_ex*,struct verbs_xrcd*,struct ibv_create_qp_common*) ; 
 int /*<<< orphan*/  create_qp_handle_resp_common (struct ibv_context*,struct verbs_qp*,struct ibv_qp_init_attr_ex*,struct ibv_create_qp_resp*,struct verbs_xrcd*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_create_qp*,size_t) ; 

int ibv_cmd_create_qp_ex(struct ibv_context *context,
			 struct verbs_qp *qp, int vqp_sz,
			 struct ibv_qp_init_attr_ex *attr_ex,
			 struct ibv_create_qp *cmd, size_t cmd_size,
			 struct ibv_create_qp_resp *resp, size_t resp_size)
{
	struct verbs_xrcd *vxrcd = NULL;
	int err;

	IBV_INIT_CMD_RESP(cmd, cmd_size, CREATE_QP, resp, resp_size);

	if (attr_ex->comp_mask > (IBV_QP_INIT_ATTR_XRCD | IBV_QP_INIT_ATTR_PD))
		return ENOSYS;

	err = create_qp_ex_common(qp, attr_ex, vxrcd,
				  (struct ibv_create_qp_common *)&cmd->user_handle);
	if (err)
		return err;

	if (write(context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void)VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	if (abi_ver == 4) {
		struct ibv_create_qp_resp_v4 *resp_v4 =
			(struct ibv_create_qp_resp_v4 *)resp;

		memmove((void *)resp + sizeof *resp,
			(void *)resp_v4 + sizeof *resp_v4,
			resp_size - sizeof *resp);
	} else if (abi_ver <= 3) {
		struct ibv_create_qp_resp_v3 *resp_v3 =
			(struct ibv_create_qp_resp_v3 *)resp;

		memmove((void *)resp + sizeof *resp,
			(void *)resp_v3 + sizeof *resp_v3,
			resp_size - sizeof *resp);
	}

	create_qp_handle_resp_common(context, qp, attr_ex, resp, vxrcd, vqp_sz);

	return 0;
}