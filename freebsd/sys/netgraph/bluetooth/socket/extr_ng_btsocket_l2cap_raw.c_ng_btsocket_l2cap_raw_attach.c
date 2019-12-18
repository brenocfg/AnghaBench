#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct socket {scalar_t__ so_type; scalar_t__ so_pcb; } ;
typedef  TYPE_1__* ng_btsocket_l2cap_raw_pcb_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  flags; struct socket* so; } ;

/* Variables and functions */
 int EISCONN ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_L2CAP_RAW ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_RAW_PRIVILEGED ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_RAW_RECVSPACE ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_RAW_SENDSPACE ; 
 int /*<<< orphan*/  PRIV_NETBLUETOOTH_RAW ; 
 scalar_t__ SOCK_RAW ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * ng_btsocket_l2cap_raw_node ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_raw_sockets ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_raw_sockets_mtx ; 
 scalar_t__ priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 TYPE_1__* so2l2cap_raw_pcb (struct socket*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ng_btsocket_l2cap_raw_attach(struct socket *so, int proto, struct thread *td)
{
	ng_btsocket_l2cap_raw_pcb_p	pcb = so2l2cap_raw_pcb(so);
	int				error;

	if (pcb != NULL)
		return (EISCONN);

	if (ng_btsocket_l2cap_raw_node == NULL) 
		return (EPROTONOSUPPORT);
	if (so->so_type != SOCK_RAW)
		return (ESOCKTNOSUPPORT);

	/* Reserve send and receive space if it is not reserved yet */
	error = soreserve(so, NG_BTSOCKET_L2CAP_RAW_SENDSPACE,
			NG_BTSOCKET_L2CAP_RAW_RECVSPACE);
	if (error != 0)
		return (error);

	/* Allocate the PCB */
        pcb = malloc(sizeof(*pcb),
		M_NETGRAPH_BTSOCKET_L2CAP_RAW, M_NOWAIT|M_ZERO);
        if (pcb == NULL)
                return (ENOMEM);

	/* Link the PCB and the socket */
	so->so_pcb = (caddr_t) pcb;
	pcb->so = so;

	if (priv_check(td, PRIV_NETBLUETOOTH_RAW) == 0)
		pcb->flags |= NG_BTSOCKET_L2CAP_RAW_PRIVILEGED;

	mtx_init(&pcb->pcb_mtx, "btsocks_l2cap_raw_pcb_mtx", NULL, MTX_DEF);

        /* Add the PCB to the list */
	mtx_lock(&ng_btsocket_l2cap_raw_sockets_mtx);
	LIST_INSERT_HEAD(&ng_btsocket_l2cap_raw_sockets, pcb, next);
	mtx_unlock(&ng_btsocket_l2cap_raw_sockets_mtx);

        return (0);
}