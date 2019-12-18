#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  token; } ;
struct ng_mesg {TYPE_1__ header; } ;
typedef  TYPE_3__* ng_btsocket_hci_raw_pcb_p ;
struct TYPE_8__ {int cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; TYPE_2__ header; } ;
struct TYPE_9__ {TYPE_5__* msg; int /*<<< orphan*/  token; int /*<<< orphan*/  pcb_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_HCI_COOKIE ; 
 int /*<<< orphan*/  NG_FREE_MSG (TYPE_5__*) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_PATH (int,int /*<<< orphan*/ ,struct ng_mesg*,char*,int /*<<< orphan*/ ) ; 
 int PCATCH ; 
 int PZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,int) ; 
 int hz ; 
 int msleep (TYPE_5__**,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_btsocket_hci_raw_get_token (int /*<<< orphan*/ *) ; 
 int ng_btsocket_hci_raw_ioctl_timeout ; 
 int /*<<< orphan*/  ng_btsocket_hci_raw_node ; 

__attribute__((used)) static int
ng_btsocket_hci_raw_send_sync_ngmsg(ng_btsocket_hci_raw_pcb_p pcb, char *path,
		int cmd, void *rsp, int rsplen)
{
	struct ng_mesg	*msg = NULL;
	int		 error = 0;

	mtx_assert(&pcb->pcb_mtx, MA_OWNED);

	NG_MKMESSAGE(msg, NGM_HCI_COOKIE, cmd, 0, M_NOWAIT);
	if (msg == NULL)
		return (ENOMEM);

	ng_btsocket_hci_raw_get_token(&msg->header.token);
	pcb->token = msg->header.token;
	pcb->msg = NULL;

	NG_SEND_MSG_PATH(error, ng_btsocket_hci_raw_node, msg, path, 0);
	if (error != 0) {
		pcb->token = 0;
		return (error);
	}

	error = msleep(&pcb->msg, &pcb->pcb_mtx, PZERO|PCATCH, "hcictl", 
			ng_btsocket_hci_raw_ioctl_timeout * hz);
	pcb->token = 0;

	if (error != 0)
		return (error);

	if (pcb->msg != NULL && pcb->msg->header.cmd == cmd)
		bcopy(pcb->msg->data, rsp, rsplen);
	else
		error = EINVAL;

	NG_FREE_MSG(pcb->msg); /* checks for != NULL */

	return (0);
}