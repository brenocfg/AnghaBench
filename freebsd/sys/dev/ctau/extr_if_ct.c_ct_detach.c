#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_15__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_17__ {int /*<<< orphan*/  dmamem; int /*<<< orphan*/  timeout_handle; TYPE_2__* chan; int /*<<< orphan*/  devt; TYPE_11__ queue; int /*<<< orphan*/  ifp; TYPE_1__ hi_queue; int /*<<< orphan*/ * node; scalar_t__ running; } ;
typedef  TYPE_3__ drv_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_18__ {scalar_t__ sys; } ;
typedef  TYPE_4__ ct_chan_t ;
struct TYPE_19__ {size_t num; TYPE_4__* chan; } ;
typedef  TYPE_5__ ct_board_t ;
struct TYPE_20__ {int /*<<< orphan*/  ct_mtx; TYPE_5__* board; int /*<<< orphan*/  base_res; int /*<<< orphan*/  base_rid; int /*<<< orphan*/  drq_res; int /*<<< orphan*/  drq_rid; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  intrhand; } ;
typedef  TYPE_6__ bdrv_t ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  CT_UNLOCK (TYPE_6__*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IF_DRAIN (TYPE_11__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int NCHAN ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ ** adapter ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_bus_dma_mem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_close_board (TYPE_5__*) ; 
 int /*<<< orphan*/  ct_led_off (TYPE_5__*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 TYPE_6__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_timo ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  sppp_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_detach (device_t dev)
{
	bdrv_t *bd = device_get_softc (dev);
	ct_board_t *b = bd->board;
	ct_chan_t *c;
	int s;
	
	KASSERT (mtx_initialized (&bd->ct_mtx), ("ct mutex not initialized"));

	s = splimp ();
	CT_LOCK (bd);
	/* Check if the device is busy (open). */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || !d->chan->type)
			continue;

		if (d->running) {
			CT_UNLOCK (bd);
			splx (s);
			return EBUSY;
		}
	}

	/* Deactivate the timeout routine. */
	callout_stop (&led_timo[b->num]);

	CT_UNLOCK (bd);
	
	bus_teardown_intr (dev, bd->irq_res, bd->intrhand);
	bus_release_resource (dev, SYS_RES_IRQ, bd->irq_rid, bd->irq_res);
	
	bus_release_resource (dev, SYS_RES_DRQ, bd->drq_rid, bd->drq_res);
	
	bus_release_resource (dev, SYS_RES_IOPORT, bd->base_rid, bd->base_res);

	CT_LOCK (bd);
	ct_close_board (b);
	CT_UNLOCK (bd);

	/* Detach the interfaces, free buffer memory. */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || !d->chan->type)
			continue;

		callout_stop (&d->timeout_handle);
#ifdef NETGRAPH
		if (d->node) {
			ng_rmnode_self (d->node);
			NG_NODE_UNREF (d->node);
			d->node = NULL;
		}
		mtx_destroy (&d->queue.ifq_mtx);
		mtx_destroy (&d->hi_queue.ifq_mtx);
#else
		/* Detach from the packet filter list of interfaces. */
		bpfdetach (d->ifp);

		/* Detach from the sync PPP list. */
		sppp_detach (d->ifp);

		if_detach (d->ifp);
		if_free (d->ifp);
		IF_DRAIN (&d->queue);
		mtx_destroy (&d->queue.ifq_mtx);
#endif		
		destroy_dev (d->devt);
	}

	CT_LOCK (bd);
	ct_led_off (b);
	CT_UNLOCK (bd);
	callout_drain (&led_timo[b->num]);
	splx (s);
	
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || !d->chan->type)
			continue;
		callout_drain(&d->timeout_handle);
		
		/* Deallocate buffers. */
		ct_bus_dma_mem_free (&d->dmamem);
	}
	bd->board = NULL;
	adapter [b->num] = NULL;
	free (b, M_DEVBUF);
	
	mtx_destroy (&bd->ct_mtx);

	return 0;	
}