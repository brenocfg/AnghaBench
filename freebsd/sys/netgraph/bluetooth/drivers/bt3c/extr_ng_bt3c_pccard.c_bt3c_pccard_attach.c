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
typedef  int /*<<< orphan*/  device_t ;
typedef  TYPE_3__* bt3c_softc_p ;
struct TYPE_8__ {int /*<<< orphan*/  ifq_mtx; int /*<<< orphan*/  ifq_maxlen; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifq_mtx; int /*<<< orphan*/  ifq_maxlen; } ;
struct TYPE_9__ {int want; scalar_t__ iobase_rid; int /*<<< orphan*/ * iobase; scalar_t__ irq_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * irq_cookie; int /*<<< orphan*/ * ith; int /*<<< orphan*/ * node; int /*<<< orphan*/  state; TYPE_2__ outq; TYPE_1__ inq; int /*<<< orphan*/  debug; int /*<<< orphan*/  dev; int /*<<< orphan*/  ioh; int /*<<< orphan*/  iot; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT3C_DEFAULTQLEN ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NG_BT3C_W4_PKT_IND ; 
 int /*<<< orphan*/  NG_BT3C_WARN_LEVEL ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SWI_TTY ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bt3c_intr ; 
 int /*<<< orphan*/  bt3c_swi_intr ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ng_make_node_common (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ng_name_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ swi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  swi_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_intr_event ; 
 int /*<<< orphan*/  typestruct ; 

__attribute__((used)) static int
bt3c_pccard_attach(device_t dev)
{
	bt3c_softc_p	sc = (bt3c_softc_p) device_get_softc(dev);

	/* Allocate I/O ports */
	sc->iobase_rid = 0;
	sc->iobase = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
			&sc->iobase_rid, 8, RF_ACTIVE);
	if (sc->iobase == NULL) {
		device_printf(dev, "Could not allocate I/O ports\n");
		goto bad;
	}
	sc->iot = rman_get_bustag(sc->iobase);
	sc->ioh = rman_get_bushandle(sc->iobase);

	/* Allocate IRQ */
	sc->irq_rid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irq_rid,
			RF_ACTIVE);
	if (sc->irq == NULL) {
		device_printf(dev, "Could not allocate IRQ\n");
		goto bad;
	}

	sc->irq_cookie = NULL;
	if (bus_setup_intr(dev, sc->irq, INTR_TYPE_TTY, NULL, bt3c_intr, sc,
			&sc->irq_cookie) != 0) {
		device_printf(dev, "Could not setup ISR\n");
		goto bad;
	}

	/* Attach handler to TTY SWI thread */
	sc->ith = NULL;
	if (swi_add(&tty_intr_event, device_get_nameunit(dev),
			bt3c_swi_intr, sc, SWI_TTY, 0, &sc->ith) < 0) {
		device_printf(dev, "Could not setup SWI ISR\n");
		goto bad;
	}

	/* Create Netgraph node */
	if (ng_make_node_common(&typestruct, &sc->node) != 0) {
		device_printf(dev, "Could not create Netgraph node\n");
		sc->node = NULL;
		goto bad;
	}

	/* Name Netgraph node */
	if (ng_name_node(sc->node, device_get_nameunit(dev)) != 0) {
		device_printf(dev, "Could not name Netgraph node\n");
		NG_NODE_UNREF(sc->node);
		sc->node = NULL;
		goto bad;
	}

	sc->dev = dev;
	sc->debug = NG_BT3C_WARN_LEVEL;

	sc->inq.ifq_maxlen = sc->outq.ifq_maxlen = BT3C_DEFAULTQLEN;
	mtx_init(&sc->inq.ifq_mtx, "BT3C inq", NULL, MTX_DEF);
	mtx_init(&sc->outq.ifq_mtx, "BT3C outq", NULL, MTX_DEF);

	sc->state = NG_BT3C_W4_PKT_IND;
	sc->want = 1;

	NG_NODE_SET_PRIVATE(sc->node, sc);

	return (0);
bad:
	if (sc->ith != NULL) {
		swi_remove(sc->ith);
		sc->ith = NULL;
	}

	if (sc->irq != NULL) {
		if (sc->irq_cookie != NULL)
			bus_teardown_intr(dev, sc->irq, sc->irq_cookie);

		bus_release_resource(dev, SYS_RES_IRQ,
			sc->irq_rid, sc->irq);

		sc->irq = NULL;
		sc->irq_rid = 0;
	}

	if (sc->iobase != NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT,
			sc->iobase_rid, sc->iobase);

		sc->iobase = NULL;
		sc->iobase_rid = 0;
	}

	return (ENXIO);
}