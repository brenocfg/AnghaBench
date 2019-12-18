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
typedef  scalar_t__ uint8_t ;
struct ibv_sa_path_rec {int dummy; } ;
struct ib_user_path_rec {int dummy; } ;
struct ib_ucm_lap {uintptr_t path; uintptr_t data; scalar_t__ len; int /*<<< orphan*/  id; } ;
struct ib_cm_id {TYPE_1__* device; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD (void*,struct ib_ucm_lap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENODATA ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_SEND_LAP ; 
 int /*<<< orphan*/  ibv_copy_path_rec_to_kern (struct ib_user_path_rec*,struct ibv_sa_path_rec*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_send_lap(struct ib_cm_id *cm_id,
		   struct ibv_sa_path_rec *alternate_path,
		   void *private_data,
		   uint8_t private_data_len)
{
	struct ib_user_path_rec abi_path;
	struct ib_ucm_lap *cmd;
	void *msg;
	int result;
	int size;

	CM_CREATE_MSG_CMD(msg, cmd, IB_USER_CM_CMD_SEND_LAP, size);
	cmd->id = cm_id->handle;

	ibv_copy_path_rec_to_kern(&abi_path, alternate_path);
	cmd->path = (uintptr_t) &abi_path;

	if (private_data && private_data_len) {
		cmd->data = (uintptr_t) private_data;
		cmd->len  = private_data_len;
	}

	result = write(cm_id->device->fd, msg, size);
	if (result != size)
		return (result >= 0) ? ERR(ENODATA) : -1;

	return 0;
}