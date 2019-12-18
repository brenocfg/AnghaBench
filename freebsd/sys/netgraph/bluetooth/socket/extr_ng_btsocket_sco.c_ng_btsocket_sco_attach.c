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
typedef  TYPE_3__* ng_btsocket_sco_pcb_p ;
typedef  scalar_t__ caddr_t ;
struct TYPE_9__ {int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  timo; int /*<<< orphan*/  state; struct socket* so; } ;

/* Variables and functions */
 int BLUETOOTH_PROTO_SCO ; 
 int EISCONN ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_SCO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_BTSOCKET_SCO_CLOSED ; 
 int /*<<< orphan*/  NG_BTSOCKET_SCO_RECVSPACE ; 
 int /*<<< orphan*/  NG_BTSOCKET_SCO_SENDSPACE ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * ng_btsocket_sco_node ; 
 int /*<<< orphan*/  ng_btsocket_sco_sockets ; 
 int /*<<< orphan*/  ng_btsocket_sco_sockets_mtx ; 
 TYPE_3__* so2sco_pcb (struct socket*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ng_btsocket_sco_attach(struct socket *so, int proto, struct thread *td)
{
	ng_btsocket_sco_pcb_p	pcb = so2sco_pcb(so);
	int			error;

	/* Check socket and protocol */
	if (ng_btsocket_sco_node == NULL) 
		return (EPROTONOSUPPORT);
	if (so->so_type != SOCK_SEQPACKET)
		return (ESOCKTNOSUPPORT);

#if 0 /* XXX sonewconn() calls "pru_attach" with proto == 0 */
	if (proto != 0) 
		if (proto != BLUETOOTH_PROTO_SCO)
			return (EPROTONOSUPPORT);
#endif /* XXX */

	if (pcb != NULL)
		return (EISCONN);

	/* Reserve send and receive space if it is not reserved yet */
	if ((so->so_snd.sb_hiwat == 0) || (so->so_rcv.sb_hiwat == 0)) {
		error = soreserve(so, NG_BTSOCKET_SCO_SENDSPACE,
					NG_BTSOCKET_SCO_RECVSPACE);
		if (error != 0)
			return (error);
	}

	/* Allocate the PCB */
        pcb = malloc(sizeof(*pcb),
		M_NETGRAPH_BTSOCKET_SCO, M_NOWAIT | M_ZERO);
        if (pcb == NULL)
                return (ENOMEM);

	/* Link the PCB and the socket */
	so->so_pcb = (caddr_t) pcb;
	pcb->so = so;
	pcb->state = NG_BTSOCKET_SCO_CLOSED;

	callout_init(&pcb->timo, 1);

	/*
	 * Mark PCB mutex as DUPOK to prevent "duplicated lock of
	 * the same type" message. When accepting new SCO connection 
	 * ng_btsocket_sco_process_lp_con_ind() holds both PCB mutexes 
	 * for "old" (accepting) PCB and "new" (created) PCB.
	 */
		
	mtx_init(&pcb->pcb_mtx, "btsocks_sco_pcb_mtx", NULL,
		MTX_DEF|MTX_DUPOK);

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
	 * In the first case we must acquire ng_btsocket_sco_sockets_mtx.
	 * In the second case we hold ng_btsocket_sco_sockets_mtx already.
	 * So we now need to distinguish between these cases. From reading
	 * /sys/kern/uipc_socket2.c we can find out that sonewconn() calls
	 * pru_attach with proto == 0 and td == NULL. For now use this fact
	 * to figure out if we were called from socket() or from sonewconn().
	 */

	if (td != NULL)
		mtx_lock(&ng_btsocket_sco_sockets_mtx);
	else
		mtx_assert(&ng_btsocket_sco_sockets_mtx, MA_OWNED);

	LIST_INSERT_HEAD(&ng_btsocket_sco_sockets, pcb, next);

	if (td != NULL)
		mtx_unlock(&ng_btsocket_sco_sockets_mtx);

        return (0);
}