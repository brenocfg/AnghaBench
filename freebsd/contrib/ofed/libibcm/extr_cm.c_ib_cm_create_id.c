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
struct ib_ucm_create_id_resp {int /*<<< orphan*/  id; } ;
struct ib_ucm_create_id {uintptr_t uid; } ;
struct ib_cm_id {int /*<<< orphan*/  handle; } ;
struct ib_cm_device {int /*<<< orphan*/  fd; } ;
struct cm_id_private {struct ib_cm_id id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD_RESP (void*,struct ib_ucm_create_id*,struct ib_ucm_create_id_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_CREATE_ID ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ib_ucm_create_id_resp*,int) ; 
 struct cm_id_private* ib_cm_alloc_id (struct ib_cm_device*,void*) ; 
 int /*<<< orphan*/  ib_cm_free_id (struct cm_id_private*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_create_id(struct ib_cm_device *device,
		    struct ib_cm_id **cm_id, void *context)
{
	struct ib_ucm_create_id_resp *resp;
	struct ib_ucm_create_id *cmd;
	struct cm_id_private *cm_id_priv;
	void *msg;
	int result;
	int size;

	cm_id_priv = ib_cm_alloc_id(device, context);
	if (!cm_id_priv)
		return ERR(ENOMEM);

	CM_CREATE_MSG_CMD_RESP(msg, cmd, resp, IB_USER_CM_CMD_CREATE_ID, size);
	cmd->uid = (uintptr_t) cm_id_priv;

	result = write(device->fd, msg, size);
	if (result != size)
		goto err;

	VALGRIND_MAKE_MEM_DEFINED(resp, sizeof *resp);

	cm_id_priv->id.handle = resp->id;
	*cm_id = &cm_id_priv->id;
	return 0;

err:	ib_cm_free_id(cm_id_priv);
	return result;
}