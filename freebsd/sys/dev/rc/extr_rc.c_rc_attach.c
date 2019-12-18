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
typedef  int u_int ;
struct tty {int /*<<< orphan*/  t_stop; int /*<<< orphan*/  t_close; int /*<<< orphan*/  t_break; int /*<<< orphan*/  t_modem; int /*<<< orphan*/  t_param; int /*<<< orphan*/  t_oproc; struct rc_chans* t_sc; } ;
struct rc_softc {int sc_unit; int /*<<< orphan*/  sc_swicookie; int /*<<< orphan*/  sc_hwicookie; int /*<<< orphan*/ * sc_irq; struct rc_chans* sc_channels; int /*<<< orphan*/  sc_irqrid; int /*<<< orphan*/ ** sc_port; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; int /*<<< orphan*/  sc_dev; } ;
struct rc_chans {int rc_chan; struct tty* rc_tp; int /*<<< orphan*/  rc_dtrcallout; int /*<<< orphan*/  rc_obuf; int /*<<< orphan*/  rc_obufend; int /*<<< orphan*/  rc_optr; int /*<<< orphan*/ * rc_ibuf; int /*<<< orphan*/ * rc_hiwat; int /*<<< orphan*/ * rc_bufend; int /*<<< orphan*/ * rc_iptr; struct rc_softc* rc_rcb; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CD180_GFRCR ; 
 int CD180_NCHAN ; 
 int /*<<< orphan*/  CD180_PPRH ; 
 int /*<<< orphan*/  CD180_PPRL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int IOBASE_ADDRS ; 
 size_t RC_IBUFSIZE ; 
 size_t RC_IHIGHWATER ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SWI_TTY ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TS_CALLOUT ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int* iobase_addrs ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_break ; 
 int /*<<< orphan*/  rc_close ; 
 int /*<<< orphan*/  rc_intr ; 
 int /*<<< orphan*/  rc_modem ; 
 int /*<<< orphan*/  rc_param ; 
 int /*<<< orphan*/  rc_pollcard ; 
 int /*<<< orphan*/  rc_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_start ; 
 int /*<<< orphan*/  rc_stop ; 
 scalar_t__ rc_test (struct rc_softc*) ; 
 int rcin (struct rc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcout (struct rc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swi_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct rc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_intr_event ; 
 struct tty* ttyalloc () ; 
 int /*<<< orphan*/  ttycreate (struct tty*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rc_attach(device_t dev)
{
 	struct rc_chans *rc;
	struct tty *tp;
	struct rc_softc *sc;
	u_int port;
	int base, chan, error, i, x;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	/*
	 * We need to have IO ports.  Lots of them.  We need
	 * the following ranges relative to the base port:
	 * 0x0    -   0x10
	 * 0x400  -  0x410
	 * 0x800  -  0x810
	 * 0xc00  -  0xc10
	 * 0x1400 - 0x1410
	 * 0x1800 - 0x1810
	 * 0x1c00 - 0x1c10
	 * 0x2000 - 0x2010
	 * 0x3000 - 0x3010
	 * 0x3400 - 0x3410
	 * 0x3800 - 0x3810
	 * 0x3c00 - 0x3c10
	 * 0x4000 - 0x4010
	 * 0x8000 - 0x8010
	 */
	port = isa_get_port(dev);
	for (i = 0; i < IOBASE_ADDRS; i++)
		if (bus_set_resource(dev, SYS_RES_IOPORT, i,
		    port + iobase_addrs[i], 0x10) != 0)
			return (ENXIO);
	error = ENOMEM;
	for (i = 0; i < IOBASE_ADDRS; i++) {
		x = i;
		sc->sc_port[i] = bus_alloc_resource_anywhere(dev,
		    SYS_RES_IOPORT, &x, 0x10, RF_ACTIVE);
		if (x != i) {
			device_printf(dev, "ioport %d was rid %d\n", i, x);
			goto fail;
		}
		if (sc->sc_port[i] == NULL) {
			device_printf(dev, "failed to alloc ioports %x-%x\n",
			    port + iobase_addrs[i],
			    port + iobase_addrs[i] + 0x10);
			goto fail;
		}
	}
	sc->sc_bt = rman_get_bustag(sc->sc_port[0]);
	sc->sc_bh = rman_get_bushandle(sc->sc_port[0]);

	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irqrid,
	    RF_ACTIVE);
	if (sc->sc_irq == NULL) {
		device_printf(dev, "failed to alloc IRQ\n");
		goto fail;
	}

	/*
	 * Now do some actual tests to make sure it works.
	 */
	error = ENXIO;
	rcout(sc, CD180_PPRL, 0x22); /* Random values to Prescale reg. */
	rcout(sc, CD180_PPRH, 0x11);
	if (rcin(sc, CD180_PPRL) != 0x22 || rcin(sc, CD180_PPRH) != 0x11)
		goto fail;
	if (rc_test(sc))
		goto fail;

	/*
	 * Ok, start actually hooking things up.
	 */
	sc->sc_unit = device_get_unit(dev);
	/*sc->sc_chipid = 0x10 + device_get_unit(dev);*/
	device_printf(dev, "%d chans, firmware rev. %c\n",
		CD180_NCHAN, (rcin(sc, CD180_GFRCR) & 0xF) + 'A');
	rc = sc->sc_channels;
	base = CD180_NCHAN * sc->sc_unit;
	for (chan = 0; chan < CD180_NCHAN; chan++, rc++) {
		rc->rc_rcb     = sc;
		rc->rc_chan    = chan;
		rc->rc_iptr    = rc->rc_ibuf;
		rc->rc_bufend  = &rc->rc_ibuf[RC_IBUFSIZE];
		rc->rc_hiwat   = &rc->rc_ibuf[RC_IHIGHWATER];
		rc->rc_optr    = rc->rc_obufend  = rc->rc_obuf;
		callout_init(&rc->rc_dtrcallout, 0);
		tp = rc->rc_tp = ttyalloc();
		tp->t_sc = rc;
		tp->t_oproc   = rc_start;
		tp->t_param   = rc_param;
		tp->t_modem   = rc_modem;
		tp->t_break   = rc_break;
		tp->t_close   = rc_close;
		tp->t_stop    = rc_stop;
		ttycreate(tp, TS_CALLOUT, "m%d", chan + base);
	}

	error = bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_TTY, NULL, rc_intr,
	    sc, &sc->sc_hwicookie);
	if (error) {
		device_printf(dev, "failed to register interrupt handler\n");
		goto fail;
	}
		
	swi_add(&tty_intr_event, "rc", rc_pollcard, sc, SWI_TTY, 0,
	    &sc->sc_swicookie);
	return (0);

fail:
	rc_release_resources(dev);
	return (error);
}