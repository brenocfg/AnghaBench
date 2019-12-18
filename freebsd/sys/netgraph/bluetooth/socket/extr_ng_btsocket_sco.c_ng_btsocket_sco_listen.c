#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct socket {int dummy; } ;
typedef  TYPE_1__* ng_btsocket_sco_pcb_p ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  NG_HCI_BDADDR_ANY ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_sco_node ; 
 TYPE_1__* so2sco_pcb (struct socket*) ; 
 int /*<<< orphan*/  solisten_proto (struct socket*,int) ; 
 int solisten_proto_check (struct socket*) ; 

int
ng_btsocket_sco_listen(struct socket *so, int backlog, struct thread *td)
{
	ng_btsocket_sco_pcb_p	pcb = so2sco_pcb(so);
	int			error;

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_sco_node == NULL)
		return (EINVAL);

	SOCK_LOCK(so);
	mtx_lock(&pcb->pcb_mtx);

	error = solisten_proto_check(so);
	if (error != 0)
		goto out;
#if 0
	if (bcmp(&pcb->src, NG_HCI_BDADDR_ANY, sizeof(bdaddr_t)) == 0) {
		error = EDESTADDRREQ;
		goto out;
	}
#endif
	solisten_proto(so, backlog);
out:
	mtx_unlock(&pcb->pcb_mtx);
	SOCK_UNLOCK(so);

	return (error);
}