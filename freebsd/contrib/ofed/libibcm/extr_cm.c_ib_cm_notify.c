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
struct ib_ucm_notify {int event; int /*<<< orphan*/  id; } ;
struct ib_cm_id {TYPE_1__* device; int /*<<< orphan*/  handle; } ;
typedef  enum ibv_event_type { ____Placeholder_ibv_event_type } ibv_event_type ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD (void*,struct ib_ucm_notify*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODATA ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int IBV_EVENT_COMM_EST ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_NOTIFY ; 
 int abi_ver ; 
 int cm_establish (struct ib_cm_id*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_notify(struct ib_cm_id *cm_id, enum ibv_event_type event)
{
	struct ib_ucm_notify *cmd;
	void *msg;
	int result;
	int size;
	
	if (abi_ver == 4) {
		if (event == IBV_EVENT_COMM_EST)
			return cm_establish(cm_id);
		else
			return ERR(EINVAL);
	}

	CM_CREATE_MSG_CMD(msg, cmd, IB_USER_CM_CMD_NOTIFY, size);
	cmd->id = cm_id->handle;
	cmd->event = event;

	result = write(cm_id->device->fd, msg, size);
	if (result != size)
		return (result >= 0) ? ERR(ENODATA) : -1;

	return 0;
}