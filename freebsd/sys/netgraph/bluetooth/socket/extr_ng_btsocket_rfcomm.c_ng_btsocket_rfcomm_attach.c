#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_8__ {scalar_t__ sb_hiwat; } ;
struct TYPE_7__ {scalar_t__ sb_hiwat; } ;
struct socket {scalar_t__ so_type; scalar_t__ so_pcb; TYPE_2__ so_rcv; TYPE_1__ so_snd; } ;
typedef  TYPE_3__* ng_btsocket_rfcomm_pcb_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_9__ {int lmodem; int rmodem; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  timo; int /*<<< orphan*/  rx_cred; scalar_t__ tx_cred; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; struct socket* so; } ;

/* Variables and functions */
 int BLUETOOTH_PROTO_RFCOMM ; 
 int EISCONN ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_RFCOMM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_DLC_CFC ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_DLC_CLOSED ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_RECVSPACE ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_SENDSPACE ; 
 int /*<<< orphan*/  RFCOMM_DEFAULT_CREDITS ; 
 int /*<<< orphan*/  RFCOMM_DEFAULT_MTU ; 
 int RFCOMM_MODEM_DV ; 
 int RFCOMM_MODEM_RTC ; 
 int RFCOMM_MODEM_RTR ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sockets ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sockets_mtx ; 
 TYPE_3__* so2rfcomm_pcb (struct socket*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ng_btsocket_rfcomm_attach(struct socket *so, int proto, struct thread *td)
{
	ng_btsocket_rfcomm_pcb_p	pcb = so2rfcomm_pcb(so);
	int				error;

	/* Check socket and protocol */
	if (so->so_type != SOCK_STREAM)
		return (ESOCKTNOSUPPORT);

#if 0 /* XXX sonewconn() calls "pru_attach" with proto == 0 */
	if (proto != 0) 
		if (proto != BLUETOOTH_PROTO_RFCOMM)
			return (EPROTONOSUPPORT);
#endif /* XXX */

	if (pcb != NULL)
		return (EISCONN);

	/* Reserve send and receive space if it is not reserved yet */
	if ((so->so_snd.sb_hiwat == 0) || (so->so_rcv.sb_hiwat == 0)) {
		error = soreserve(so, NG_BTSOCKET_RFCOMM_SENDSPACE,
					NG_BTSOCKET_RFCOMM_RECVSPACE);
		if (error != 0)
			return (error);
	}

	/* Allocate the PCB */
        pcb = malloc(sizeof(*pcb),
		M_NETGRAPH_BTSOCKET_RFCOMM, M_NOWAIT | M_ZERO);
        if (pcb == NULL)
                return (ENOMEM);

	/* Link the PCB and the socket */
	so->so_pcb = (caddr_t) pcb;
	pcb->so = so;

	/* Initialize PCB */
	pcb->state = NG_BTSOCKET_RFCOMM_DLC_CLOSED;
	pcb->flags = NG_BTSOCKET_RFCOMM_DLC_CFC;

	pcb->lmodem =
	pcb->rmodem = (RFCOMM_MODEM_RTC | RFCOMM_MODEM_RTR | RFCOMM_MODEM_DV);

	pcb->mtu = RFCOMM_DEFAULT_MTU;
	pcb->tx_cred = 0;
	pcb->rx_cred = RFCOMM_DEFAULT_CREDITS;

	mtx_init(&pcb->pcb_mtx, "btsocks_rfcomm_pcb_mtx", NULL, MTX_DEF);
	callout_init_mtx(&pcb->timo, &pcb->pcb_mtx, 0);

	/* Add the PCB to the list */
	mtx_lock(&ng_btsocket_rfcomm_sockets_mtx);
	LIST_INSERT_HEAD(&ng_btsocket_rfcomm_sockets, pcb, next);
	mtx_unlock(&ng_btsocket_rfcomm_sockets_mtx);

        return (0);
}