#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct intr_config_hook {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sc_odma; int /*<<< orphan*/  sc_dev; } ;
struct i2s_softc {int node; int soundnode; TYPE_1__ aoa; int /*<<< orphan*/ * reg; int /*<<< orphan*/  port_mtx; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {struct i2s_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int aoa_attach (struct i2s_softc*) ; 
 int /*<<< orphan*/  aoa_interrupt ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ config_intrhook_establish (TYPE_2__*) ; 
 TYPE_2__* i2s_delayed_attach ; 
 int /*<<< orphan*/  i2s_postattach ; 
 int i2s_setup (struct i2s_softc*,int,int,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* of_find_firstchild_byname (int,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int powerpc_config_intr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  snd_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2s_softc*,void**) ; 

__attribute__((used)) static int
i2s_attach(device_t self)
{
	struct i2s_softc 	*sc;
	struct resource 	*dbdma_irq;
	void			*dbdma_ih;
	int 			 rid, oirq, err;
	phandle_t 		 port;
	
	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);

	sc->aoa.sc_dev = self;
	sc->node = ofw_bus_get_node(self);

	port = of_find_firstchild_byname(sc->node, "i2s-a");
	if (port == -1)
		return (ENXIO);
	sc->soundnode = of_find_firstchild_byname(port, "sound");
	if (sc->soundnode == -1)
		return (ENXIO);
 
	mtx_init(&sc->port_mtx, "port_mtx", NULL, MTX_DEF);

	/* Map the controller register space. */
	rid = 0;
	sc->reg = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->reg == NULL)
		return ENXIO;

	/* Map the DBDMA channel register space. */
	rid = 1;
	sc->aoa.sc_odma = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid, 
	    RF_ACTIVE);
	if (sc->aoa.sc_odma == NULL)
		return ENXIO;

	/* Establish the DBDMA channel edge-triggered interrupt. */
	rid = 1;
	dbdma_irq = bus_alloc_resource_any(self, SYS_RES_IRQ, 
	    &rid, RF_SHAREABLE | RF_ACTIVE);
	if (dbdma_irq == NULL)
		return (ENXIO);

	/* Now initialize the controller. */
	err = i2s_setup(sc, 44100, 16, 64);
	if (err != 0)
		return (err);

	snd_setup_intr(self, dbdma_irq, INTR_MPSAFE, aoa_interrupt,
	    sc, &dbdma_ih);

	oirq = rman_get_start(dbdma_irq);
	err = powerpc_config_intr(oirq, INTR_TRIGGER_EDGE, INTR_POLARITY_LOW);
	if (err != 0)
		return (err);

	/*
	 * Register a hook for delayed attach in order to allow
	 * the I2C controller to attach.
	 */
	if ((i2s_delayed_attach = malloc(sizeof(struct intr_config_hook), 
	    M_TEMP, M_WAITOK | M_ZERO)) == NULL)
		return (ENOMEM);

	i2s_delayed_attach->ich_func = i2s_postattach;
	i2s_delayed_attach->ich_arg = sc;

	if (config_intrhook_establish(i2s_delayed_attach) != 0)
		return (ENOMEM);

	return (aoa_attach(sc));
}