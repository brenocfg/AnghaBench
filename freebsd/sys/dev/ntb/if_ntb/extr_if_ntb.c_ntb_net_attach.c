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
struct ntb_queue_handlers {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ntb_net_queue {int /*<<< orphan*/ * qp; int /*<<< orphan*/  queue_full; int /*<<< orphan*/  tx_tq; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  br; int /*<<< orphan*/ * ifp; struct ntb_net_ctx* sc; } ;
struct ntb_net_ctx {int num_queues; struct ntb_net_queue* queues; int /*<<< orphan*/  media; scalar_t__ mtu; int /*<<< orphan*/  eaddr; int /*<<< orphan*/ * ifp; } ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_HWCSUM_IPV6 ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LINKSTATE ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NTB_MEDIATYPE ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ntb_net_queue*) ; 
 int /*<<< orphan*/  buf_ring_alloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_random_local_eui48 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ntb_net_ctx* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ether_ifattach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_if_ntb_num_queues ; 
 int /*<<< orphan*/ * if_gethandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilities (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setcapenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setinitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  if_setqflushfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsoftc (int /*<<< orphan*/ *,struct ntb_net_ctx*) ; 
 int /*<<< orphan*/  if_settransmitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ imin (scalar_t__,int /*<<< orphan*/ ) ; 
 struct ntb_net_queue* malloc (int,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_handle_tx ; 
 int /*<<< orphan*/  ntb_ifmedia_sts ; 
 int /*<<< orphan*/  ntb_ifmedia_upd ; 
 int /*<<< orphan*/  ntb_ioctl ; 
 int /*<<< orphan*/  ntb_net_event_handler ; 
 int /*<<< orphan*/  ntb_net_init ; 
 int /*<<< orphan*/  ntb_net_rx_handler ; 
 int /*<<< orphan*/  ntb_net_tx_handler ; 
 int /*<<< orphan*/  ntb_qflush ; 
 int /*<<< orphan*/  ntb_transmit ; 
 int /*<<< orphan*/ * ntb_transport_create_queue (int /*<<< orphan*/ ,int,struct ntb_queue_handlers*,struct ntb_net_queue*) ; 
 int /*<<< orphan*/  ntb_transport_link_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_transport_max_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_transport_queue_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
ntb_net_attach(device_t dev)
{
	struct ntb_net_ctx *sc = device_get_softc(dev);
	struct ntb_net_queue *q;
	if_t ifp;
	struct ntb_queue_handlers handlers = { ntb_net_rx_handler,
	    ntb_net_tx_handler, ntb_net_event_handler };
	int i;

	ifp = sc->ifp = if_gethandle(IFT_ETHER);
	if (ifp == NULL) {
		printf("ntb: Cannot allocate ifnet structure\n");
		return (ENOMEM);
	}
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	if_setdev(ifp, dev);

	sc->num_queues = min(g_if_ntb_num_queues,
	    ntb_transport_queue_count(dev));
	sc->queues = malloc(sc->num_queues * sizeof(struct ntb_net_queue),
	    M_DEVBUF, M_WAITOK | M_ZERO);
	sc->mtu = INT_MAX;
	for (i = 0; i < sc->num_queues; i++) {
		q = &sc->queues[i];
		q->sc = sc;
		q->ifp = ifp;
		q->qp = ntb_transport_create_queue(dev, i, &handlers, q);
		if (q->qp == NULL)
			break;
		sc->mtu = imin(sc->mtu, ntb_transport_max_size(q->qp));
		mtx_init(&q->tx_lock, "ntb tx", NULL, MTX_DEF);
		q->br = buf_ring_alloc(4096, M_DEVBUF, M_WAITOK, &q->tx_lock);
		TASK_INIT(&q->tx_task, 0, ntb_handle_tx, q);
		q->tx_tq = taskqueue_create_fast("ntb_txq", M_NOWAIT,
		    taskqueue_thread_enqueue, &q->tx_tq);
		taskqueue_start_threads(&q->tx_tq, 1, PI_NET, "%s txq%d",
		    device_get_nameunit(dev), i);
		callout_init(&q->queue_full, 1);
	}
	sc->num_queues = i;
	device_printf(dev, "%d queue(s)\n", sc->num_queues);

	if_setinitfn(ifp, ntb_net_init);
	if_setsoftc(ifp, sc);
	if_setflags(ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);
	if_setioctlfn(ifp, ntb_ioctl);
	if_settransmitfn(ifp, ntb_transmit);
	if_setqflushfn(ifp, ntb_qflush);
	create_random_local_eui48(sc->eaddr);
	ether_ifattach(ifp, sc->eaddr);
	if_setcapabilities(ifp, IFCAP_HWCSUM | IFCAP_HWCSUM_IPV6 |
	    IFCAP_JUMBO_MTU | IFCAP_LINKSTATE);
	if_setcapenable(ifp, IFCAP_JUMBO_MTU | IFCAP_LINKSTATE);
	if_setmtu(ifp, sc->mtu - ETHER_HDR_LEN);

	ifmedia_init(&sc->media, IFM_IMASK, ntb_ifmedia_upd,
	    ntb_ifmedia_sts);
	ifmedia_add(&sc->media, NTB_MEDIATYPE, 0, NULL);
	ifmedia_set(&sc->media, NTB_MEDIATYPE);

	for (i = 0; i < sc->num_queues; i++)
		ntb_transport_link_up(sc->queues[i].qp);
	return (0);
}