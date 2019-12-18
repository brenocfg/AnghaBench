#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_18__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_17__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_20__ {int open_dev; int /*<<< orphan*/  dmamem; TYPE_3__* chan; int /*<<< orphan*/  timeout_handle; int /*<<< orphan*/  dcd_timeout_handle; int /*<<< orphan*/  devt; TYPE_13__ queue; int /*<<< orphan*/  ifp; TYPE_2__ hi_queue; TYPE_1__ lo_queue; int /*<<< orphan*/ * node; TYPE_8__* tty; scalar_t__ running; scalar_t__ lock; } ;
typedef  TYPE_4__ drv_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_21__ {scalar_t__ mode; TYPE_4__* sys; } ;
typedef  TYPE_5__ cx_chan_t ;
struct TYPE_22__ {size_t num; TYPE_5__* chan; } ;
typedef  TYPE_6__ cx_board_t ;
struct TYPE_23__ {int /*<<< orphan*/  cx_mtx; TYPE_6__* board; int /*<<< orphan*/  base_res; int /*<<< orphan*/  base_rid; int /*<<< orphan*/  drq_res; int /*<<< orphan*/  drq_rid; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  intrhand; } ;
typedef  TYPE_7__ bdrv_t ;
struct TYPE_24__ {int t_state; } ;
struct TYPE_19__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_LOCK (TYPE_7__*) ; 
 int /*<<< orphan*/  CX_UNLOCK (TYPE_7__*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IF_DRAIN (TYPE_13__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int NCHAN ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int TS_ISOPEN ; 
 scalar_t__ T_NONE ; 
 int /*<<< orphan*/ ** adapter ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx_bus_dma_mem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx_close_board (TYPE_6__*) ; 
 int /*<<< orphan*/  cx_led_off (TYPE_6__*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 TYPE_7__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_timo ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  sppp_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyfree (TYPE_8__*) ; 

__attribute__((used)) static int cx_detach (device_t dev)
{
	bdrv_t *bd = device_get_softc (dev);
	cx_board_t *b = bd->board;
	cx_chan_t *c;
	int s;
	
	KASSERT (mtx_initialized (&bd->cx_mtx), ("cx mutex not initialized"));

	s = splhigh ();
	CX_LOCK (bd);
	/* Check if the device is busy (open). */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || d->chan->type == T_NONE)
			continue;
		if (d->lock) {
			CX_UNLOCK (bd);
			splx (s);
			return EBUSY;
		}
		if (c->mode == M_ASYNC && d->tty && (d->tty->t_state & TS_ISOPEN) &&
		    (d->open_dev|0x2)) {
			CX_UNLOCK (bd);
			splx (s);
			return EBUSY;
		}
		if (d->running) {
			CX_UNLOCK (bd);
			splx (s);
			return EBUSY;
		}
	}

	/* Deactivate the timeout routine. And soft interrupt*/
	callout_stop (&led_timo[b->num]);

	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = c->sys;

		if (!d || d->chan->type == T_NONE)
			continue;

		callout_stop (&d->dcd_timeout_handle);
	}
	CX_UNLOCK (bd);
	bus_teardown_intr (dev, bd->irq_res, bd->intrhand);
	bus_release_resource (dev, SYS_RES_IRQ, bd->irq_rid, bd->irq_res);
	
	bus_release_resource (dev, SYS_RES_DRQ, bd->drq_rid, bd->drq_res);
	
	bus_release_resource (dev, SYS_RES_IOPORT, bd->base_rid, bd->base_res);

	CX_LOCK (bd);
	cx_close_board (b);

	/* Detach the interfaces, free buffer memory. */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || d->chan->type == T_NONE)
			continue;
			
		if (d->tty) {
			ttyfree (d->tty);
			d->tty = NULL;
		}

		callout_stop (&d->timeout_handle);
#ifdef NETGRAPH
		if (d->node) {
			ng_rmnode_self (d->node);
			NG_NODE_UNREF (d->node);
			d->node = NULL;
		}
		mtx_destroy (&d->lo_queue.ifq_mtx);
		mtx_destroy (&d->hi_queue.ifq_mtx);
#else
		/* Detach from the packet filter list of interfaces. */
		bpfdetach (d->ifp);
		/* Detach from the sync PPP list. */
		sppp_detach (d->ifp);

		if_detach (d->ifp);
		if_free(d->ifp);
		/* XXXRIK: check interconnection with irq handler */
		IF_DRAIN (&d->queue);
		mtx_destroy (&d->queue.ifq_mtx);
#endif		
		destroy_dev (d->devt);
	}

	cx_led_off (b);
	CX_UNLOCK (bd);
	callout_drain (&led_timo[b->num]);
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = c->sys;

		if (!d || d->chan->type == T_NONE)
			continue;

		callout_drain (&d->dcd_timeout_handle);
		callout_drain (&d->timeout_handle);
	}
	splx (s);
	
	s = splhigh ();
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (!d || d->chan->type == T_NONE)
			continue;
		
		/* Deallocate buffers. */
		cx_bus_dma_mem_free (&d->dmamem);
	}
	bd->board = NULL;
	adapter [b->num] = NULL;
	free (b, M_DEVBUF);
	splx (s);

	mtx_destroy (&bd->cx_mtx);
	
	return 0;	
}