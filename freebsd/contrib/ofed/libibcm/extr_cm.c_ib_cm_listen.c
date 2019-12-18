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
struct ib_ucm_listen {void* service_mask; void* service_id; int /*<<< orphan*/  id; } ;
struct ib_cm_id {TYPE_1__* device; int /*<<< orphan*/  handle; } ;
typedef  void* __be64 ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD (void*,struct ib_ucm_listen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENODATA ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_LISTEN ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_listen(struct ib_cm_id *cm_id,
		 __be64 service_id,
		 __be64 service_mask)
{
	struct ib_ucm_listen *cmd;
	void *msg;
	int result;
	int size;
	
	CM_CREATE_MSG_CMD(msg, cmd, IB_USER_CM_CMD_LISTEN, size);
	cmd->id           = cm_id->handle;
	cmd->service_id   = service_id;
	cmd->service_mask = service_mask;

	result = write(cm_id->device->fd, msg, size);
	if (result != size)
		return (result >= 0) ? ERR(ENODATA) : -1;

	return 0;
}