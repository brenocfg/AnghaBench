#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_19__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_21__ {int /*<<< orphan*/  dmamem; int /*<<< orphan*/  timeout_handle; TYPE_10__* chan; int /*<<< orphan*/  devt; TYPE_1__ hi_queue; TYPE_15__ queue; int /*<<< orphan*/ * node; int /*<<< orphan*/  ifp; scalar_t__ running; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_22__ {int num; scalar_t__ sys; } ;
typedef  TYPE_3__ cp_chan_t ;
struct TYPE_23__ {size_t num; TYPE_3__* chan; int /*<<< orphan*/ * sys; } ;
typedef  TYPE_4__ cp_board_t ;
struct TYPE_24__ {int /*<<< orphan*/  cp_mtx; int /*<<< orphan*/  dmamem; int /*<<< orphan*/  cp_res; int /*<<< orphan*/  cp_irq; int /*<<< orphan*/  cp_intrhand; TYPE_4__* board; } ;
typedef  TYPE_5__ bdrv_t ;
struct TYPE_18__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  CP_UNLOCK (TYPE_5__*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IF_DRAIN (TYPE_15__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int NCHAN ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ ** adapter ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** channel ; 
 int /*<<< orphan*/  cp_bus_dma_mem_free (int /*<<< orphan*/ *) ; 
 int cp_destroy ; 
 int /*<<< orphan*/  cp_interrupt_poll (TYPE_4__*,int) ; 
 int /*<<< orphan*/  cp_led_off (TYPE_4__*) ; 
 int /*<<< orphan*/  cp_reset (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_dtr (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_rts (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_stop_chan (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_stop_e1 (TYPE_3__*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 TYPE_5__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_timo ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  sppp_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp_detach (device_t dev)
{
	bdrv_t *bd = device_get_softc (dev);
	cp_board_t *b = bd->board;
	cp_chan_t *c;
	int s;

	KASSERT (mtx_initialized (&bd->cp_mtx), ("cp mutex not initialized"));
	s = splimp ();
	CP_LOCK (bd);
	/* Check if the device is busy (open). */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (! d || ! d->chan->type)
			continue;
		if (d->running) {
			CP_UNLOCK (bd);
			splx (s);
			return EBUSY;
		}
	}

	/* Ok, we can unload driver */
	/* At first we should stop all channels */
	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (! d || ! d->chan->type)
			continue;

		cp_stop_chan (c);
		cp_stop_e1 (c);
		cp_set_dtr (d->chan, 0);
		cp_set_rts (d->chan, 0);
	}

	/* Reset the adapter. */
	cp_destroy = 1;
	cp_interrupt_poll (b, 1);
	cp_led_off (b);
	cp_reset (b, 0 ,0);
	callout_stop (&led_timo[b->num]);

	/* Disable the interrupt request. */
	bus_teardown_intr (dev, bd->cp_irq, bd->cp_intrhand);

	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (! d || ! d->chan->type)
			continue;
		callout_stop (&d->timeout_handle);
#ifndef NETGRAPH
		/* Detach from the packet filter list of interfaces. */
		bpfdetach (d->ifp);

		/* Detach from the sync PPP list. */
		sppp_detach (d->ifp);

		/* Detach from the system list of interfaces. */
		if_detach (d->ifp);
		if_free (d->ifp);
		IF_DRAIN (&d->queue);
		mtx_destroy (&d->queue.ifq_mtx);
#else
		if (d->node) {
			ng_rmnode_self (d->node);
			NG_NODE_UNREF (d->node);
			d->node = NULL;
		}
		mtx_destroy (&d->queue.ifq_mtx);
		mtx_destroy (&d->hi_queue.ifq_mtx);
#endif
		destroy_dev (d->devt);
	}

	b->sys = NULL;
	CP_UNLOCK (bd);

	bus_release_resource (dev, SYS_RES_IRQ, 0, bd->cp_irq);
	bus_release_resource (dev, SYS_RES_MEMORY, PCIR_BAR(0), bd->cp_res);

	CP_LOCK (bd);
	cp_led_off (b);
	CP_UNLOCK (bd);
	callout_drain (&led_timo[b->num]);
	splx (s);

	for (c = b->chan; c < b->chan + NCHAN; ++c) {
		drv_t *d = (drv_t*) c->sys;

		if (! d || ! d->chan->type)
			continue;
		callout_drain (&d->timeout_handle);
		channel [b->num*NCHAN + c->num] = NULL;
		/* Deallocate buffers. */
		cp_bus_dma_mem_free (&d->dmamem);
	}
	adapter [b->num] = NULL;
	cp_bus_dma_mem_free (&bd->dmamem);
	free (b, M_DEVBUF);
	mtx_destroy (&bd->cp_mtx);
	return 0;
}