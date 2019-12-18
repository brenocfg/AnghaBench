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
typedef  int uint8_t ;
struct cuda_softc {int sc_rtc; int /*<<< orphan*/  adb_bus; int /*<<< orphan*/  sc_state; int /*<<< orphan*/ * sc_pkts; int /*<<< orphan*/  sc_freeq; int /*<<< orphan*/  sc_outq; int /*<<< orphan*/  sc_inq; scalar_t__ sc_autopoll; scalar_t__ sc_polling; scalar_t__ sc_waiting; scalar_t__ sc_received; scalar_t__ sc_sent; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/ * sc_irq; scalar_t__ sc_irqrid; int /*<<< orphan*/ * sc_memr; scalar_t__ sc_memrid; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CUDA_IDLE ; 
 int volatile CUDA_MAXPACKETS ; 
 int /*<<< orphan*/  CUDA_NOTREADY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cuda_softc*,int /*<<< orphan*/ ) ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int /*<<< orphan*/  OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cuda_clear_tip (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_idle (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_intr ; 
 int cuda_read_reg (struct cuda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_shutdown ; 
 int /*<<< orphan*/  cuda_tip (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_toggle_ack (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_write_reg (struct cuda_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct cuda_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_q ; 
 int /*<<< orphan*/  shutdown_final ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  vACR ; 
 int /*<<< orphan*/  vDirB ; 
 int /*<<< orphan*/  vIER ; 
 int /*<<< orphan*/  vSR ; 
 int vSR_OUT ; 

__attribute__((used)) static int
cuda_attach(device_t dev)
{
	struct cuda_softc *sc;

	volatile int i;
	uint8_t reg;
	phandle_t node,child;
	
	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	
	sc->sc_memrid = 0;
	sc->sc_memr = bus_alloc_resource_any(dev, SYS_RES_MEMORY, 
	    &sc->sc_memrid, RF_ACTIVE);

	if (sc->sc_memr == NULL) {
		device_printf(dev, "Could not alloc mem resource!\n");
		return (ENXIO);
	}

	sc->sc_irqrid = 0;
	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irqrid,
            	RF_ACTIVE);
        if (sc->sc_irq == NULL) {
                device_printf(dev, "could not allocate interrupt\n");
                bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_memrid,
                    sc->sc_memr);
                return (ENXIO);
        }

	if (bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_MISC | INTR_MPSAFE 
	    | INTR_ENTROPY, NULL, cuda_intr, dev, &sc->sc_ih) != 0) {
                device_printf(dev, "could not setup interrupt\n");
                bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_memrid,
                    sc->sc_memr);
                bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqrid,
                    sc->sc_irq);
                return (ENXIO);
        }

	mtx_init(&sc->sc_mutex,"cuda",NULL,MTX_DEF | MTX_RECURSE);

	sc->sc_sent = 0;
	sc->sc_received = 0;
	sc->sc_waiting = 0;
	sc->sc_polling = 0;
	sc->sc_state = CUDA_NOTREADY;
	sc->sc_autopoll = 0;
	sc->sc_rtc = -1;

	STAILQ_INIT(&sc->sc_inq);
	STAILQ_INIT(&sc->sc_outq);
	STAILQ_INIT(&sc->sc_freeq);

	for (i = 0; i < CUDA_MAXPACKETS; i++)
		STAILQ_INSERT_TAIL(&sc->sc_freeq, &sc->sc_pkts[i], pkt_q);

	/* Init CUDA */

	reg = cuda_read_reg(sc, vDirB);
	reg |= 0x30;	/* register B bits 4 and 5: outputs */
	cuda_write_reg(sc, vDirB, reg);

	reg = cuda_read_reg(sc, vDirB);
	reg &= 0xf7;	/* register B bit 3: input */
	cuda_write_reg(sc, vDirB, reg);

	reg = cuda_read_reg(sc, vACR);
	reg &= ~vSR_OUT;	/* make sure SR is set to IN */
	cuda_write_reg(sc, vACR, reg);

	cuda_write_reg(sc, vACR, (cuda_read_reg(sc, vACR) | 0x0c) & ~0x10);

	sc->sc_state = CUDA_IDLE;	/* used by all types of hardware */

	cuda_write_reg(sc, vIER, 0x84); /* make sure VIA interrupts are on */

	cuda_idle(sc);	/* reset ADB */

	/* Reset CUDA */

	i = cuda_read_reg(sc, vSR);	/* clear interrupt */
	cuda_write_reg(sc, vIER, 0x04); /* no interrupts while clearing */
	cuda_idle(sc);	/* reset state to idle */
	DELAY(150);
	cuda_tip(sc);	/* signal start of frame */
	DELAY(150);
	cuda_toggle_ack(sc);
	DELAY(150);
	cuda_clear_tip(sc);
	DELAY(150);
	cuda_idle(sc);	/* back to idle state */
	i = cuda_read_reg(sc, vSR);	/* clear interrupt */
	cuda_write_reg(sc, vIER, 0x84);	/* ints ok now */

	/* Initialize child buses (ADB) */
	node = ofw_bus_get_node(dev);

	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		char name[32];

		memset(name, 0, sizeof(name));
		OF_getprop(child, "name", name, sizeof(name));

		if (bootverbose)
			device_printf(dev, "CUDA child <%s>\n",name);

		if (strncmp(name, "adb", 4) == 0) {
			sc->adb_bus = device_add_child(dev,"adb",-1);
		}
	}

	clock_register(dev, 1000);
	EVENTHANDLER_REGISTER(shutdown_final, cuda_shutdown, sc,
	    SHUTDOWN_PRI_LAST);

	return (bus_generic_attach(dev));
}