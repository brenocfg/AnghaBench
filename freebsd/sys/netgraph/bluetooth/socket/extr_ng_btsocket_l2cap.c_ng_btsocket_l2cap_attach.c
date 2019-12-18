#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct thread {int dummy; } ;
struct TYPE_9__ {scalar_t__ sb_hiwat; } ;
struct TYPE_8__ {scalar_t__ sb_hiwat; } ;
struct socket {scalar_t__ so_type; scalar_t__ so_pcb; TYPE_2__ so_rcv; TYPE_1__ so_snd; } ;
typedef  TYPE_3__* ng_btsocket_l2cap_pcb_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_11__ {int flags; int token_rate; int token_bucket_size; int peak_bandwidth; int latency; int delay_variation; int /*<<< orphan*/  service_type; } ;
struct TYPE_10__ {scalar_t__ token; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  timo; int /*<<< orphan*/  link_timo; int /*<<< orphan*/  flush_timo; int /*<<< orphan*/  oflow; TYPE_6__ iflow; int /*<<< orphan*/  omtu; int /*<<< orphan*/  imtu; int /*<<< orphan*/  state; struct socket* so; } ;

/* Variables and functions */
 int BLUETOOTH_PROTO_L2CAP ; 
 int EISCONN ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_L2CAP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_CLOSED ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_RECVSPACE ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_SENDSPACE ; 
 int /*<<< orphan*/  NG_HCI_SERVICE_TYPE_BEST_EFFORT ; 
 int /*<<< orphan*/  NG_L2CAP_FLUSH_TIMO_DEFAULT ; 
 int /*<<< orphan*/  NG_L2CAP_LINK_TIMO_DEFAULT ; 
 int /*<<< orphan*/  NG_L2CAP_MTU_DEFAULT ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  bcopy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * ng_btsocket_l2cap_node ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_sockets ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_sockets_mtx ; 
 TYPE_3__* so2l2cap_pcb (struct socket*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ng_btsocket_l2cap_attach(struct socket *so, int proto, struct thread *td)
{
	static u_int32_t	token = 0;
	ng_btsocket_l2cap_pcb_p	pcb = so2l2cap_pcb(so);
	int			error;

	/* Check socket and protocol */
	if (ng_btsocket_l2cap_node == NULL) 
		return (EPROTONOSUPPORT);
	if (so->so_type != SOCK_SEQPACKET)
		return (ESOCKTNOSUPPORT);

#if 0 /* XXX sonewconn() calls "pru_attach" with proto == 0 */
	if (proto != 0) 
		if (proto != BLUETOOTH_PROTO_L2CAP)
			return (EPROTONOSUPPORT);
#endif /* XXX */

	if (pcb != NULL)
		return (EISCONN);

	/* Reserve send and receive space if it is not reserved yet */
	if ((so->so_snd.sb_hiwat == 0) || (so->so_rcv.sb_hiwat == 0)) {
		error = soreserve(so, NG_BTSOCKET_L2CAP_SENDSPACE,
					NG_BTSOCKET_L2CAP_RECVSPACE);
		if (error != 0)
			return (error);
	}

	/* Allocate the PCB */
        pcb = malloc(sizeof(*pcb),
		M_NETGRAPH_BTSOCKET_L2CAP, M_NOWAIT | M_ZERO);
        if (pcb == NULL)
                return (ENOMEM);

	/* Link the PCB and the socket */
	so->so_pcb = (caddr_t) pcb;
	pcb->so = so;
	pcb->state = NG_BTSOCKET_L2CAP_CLOSED;

	/* Initialize PCB */
	pcb->imtu = pcb->omtu = NG_L2CAP_MTU_DEFAULT;

	/* Default flow */
	pcb->iflow.flags = 0x0;
	pcb->iflow.service_type = NG_HCI_SERVICE_TYPE_BEST_EFFORT;
	pcb->iflow.token_rate = 0xffffffff; /* maximum */
	pcb->iflow.token_bucket_size = 0xffffffff; /* maximum */
	pcb->iflow.peak_bandwidth = 0x00000000; /* maximum */
	pcb->iflow.latency = 0xffffffff; /* don't care */
	pcb->iflow.delay_variation = 0xffffffff; /* don't care */

	bcopy(&pcb->iflow, &pcb->oflow, sizeof(pcb->oflow));

	pcb->flush_timo = NG_L2CAP_FLUSH_TIMO_DEFAULT;
	pcb->link_timo = NG_L2CAP_LINK_TIMO_DEFAULT;

	/*
	 * XXX Mark PCB mutex as DUPOK to prevent "duplicated lock of
	 * the same type" message. When accepting new L2CAP connection 
	 * ng_btsocket_l2cap_process_l2ca_con_ind() holds both PCB mutexes 
	 * for "old" (accepting) PCB and "new" (created) PCB.
	 */
		
	mtx_init(&pcb->pcb_mtx, "btsocks_l2cap_pcb_mtx", NULL,
		MTX_DEF|MTX_DUPOK);
	callout_init_mtx(&pcb->timo, &pcb->pcb_mtx, 0);

        /*
	 * Add the PCB to the list
	 * 
	 * XXX FIXME VERY IMPORTANT!
	 *
	 * This is totally FUBAR. We could get here in two cases:
	 *
	 * 1) When user calls socket()
	 * 2) When we need to accept new incoming connection and call 
	 *    sonewconn()
	 *
	 * In the first case we must acquire ng_btsocket_l2cap_sockets_mtx.
	 * In the second case we hold ng_btsocket_l2cap_sockets_mtx already.
	 * So we now need to distinguish between these cases. From reading
	 * /sys/kern/uipc_socket.c we can find out that sonewconn() calls
	 * pru_attach with proto == 0 and td == NULL. For now use this fact
	 * to figure out if we were called from socket() or from sonewconn().
	 */

	if (td != NULL)
		mtx_lock(&ng_btsocket_l2cap_sockets_mtx);
	else
		mtx_assert(&ng_btsocket_l2cap_sockets_mtx, MA_OWNED);
	
	/* Set PCB token. Use ng_btsocket_l2cap_sockets_mtx for protection */
	if (++ token == 0)
		token ++;

	pcb->token = token;

	LIST_INSERT_HEAD(&ng_btsocket_l2cap_sockets, pcb, next);

	if (td != NULL)
		mtx_unlock(&ng_btsocket_l2cap_sockets_mtx);

        return (0);
}