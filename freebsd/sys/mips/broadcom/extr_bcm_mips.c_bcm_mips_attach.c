#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct intr_pic {int dummy; } ;
struct bcm_mips_softc {size_t num_cpuirqs; size_t timer_irq; TYPE_1__* cpuirqs; TYPE_1__* isrcs; int /*<<< orphan*/  dev; } ;
typedef  size_t rman_res_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int irq_rid; int /*<<< orphan*/  isrc; } ;

/* Variables and functions */
 size_t BCM_MIPS_IRQ_SHARED ; 
 int /*<<< orphan*/  BCM_MIPS_LOCK_DESTROY (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  BCM_MIPS_LOCK_INIT (struct bcm_mips_softc*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  bcm_mips_fini_cpuirq (struct bcm_mips_softc*,TYPE_1__*) ; 
 int bcm_mips_init_cpuirq (struct bcm_mips_softc*,TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int bcm_mips_init_cpuirq_unavail (struct bcm_mips_softc*,TYPE_1__*) ; 
 uintptr_t bcm_mips_pic_xref (struct bcm_mips_softc*) ; 
 int bcm_mips_register_isrcs (struct bcm_mips_softc*) ; 
 size_t bhnd_get_intr_count (int /*<<< orphan*/ ) ; 
 struct bcm_mips_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  intr_isrc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intr_pic* intr_pic_register (int /*<<< orphan*/ ,uintptr_t) ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 

int
bcm_mips_attach(device_t dev, u_int num_cpuirqs, u_int timer_irq,
    driver_filter_t filter)
{
	struct bcm_mips_softc	*sc;
	struct intr_pic		*pic;
	uintptr_t		 xref;
	u_int			 irq_rid;
	rman_res_t		 irq;
	int			 error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->num_cpuirqs = num_cpuirqs;
	sc->timer_irq = timer_irq;

	/* Must not exceed the actual size of our fixed IRQ array */
	if (sc->num_cpuirqs > nitems(sc->cpuirqs)) {
		device_printf(dev, "%u nirqs exceeds maximum supported %zu",
		    sc->num_cpuirqs, nitems(sc->cpuirqs));
		return (ENXIO);
	}

	pic = NULL;
	xref = bcm_mips_pic_xref(sc);

	BCM_MIPS_LOCK_INIT(sc);

	/* Register our interrupt sources */
	if ((error = bcm_mips_register_isrcs(sc))) {
		BCM_MIPS_LOCK_DESTROY(sc);
		return (error);
	}

	/* Initialize our CPU interrupt state */
	irq_rid = bhnd_get_intr_count(dev); /* last bhnd-assigned RID + 1 */
	irq = 0;
	for (u_int i = 0; i < sc->num_cpuirqs; i++) {
		/* Must not overflow signed resource ID representation */
		if (irq_rid >= INT_MAX) {
			device_printf(dev, "exhausted IRQ resource IDs\n");
			error = ENOMEM;
			goto failed;
		}

		if (irq == sc->timer_irq) {
			/* Mark the CPU timer's IRQ as unavailable */
			error = bcm_mips_init_cpuirq_unavail(sc,
			    &sc->cpuirqs[i]);
		} else {
			/* Initialize state */
			error = bcm_mips_init_cpuirq(sc, &sc->cpuirqs[i],
			    irq_rid, irq, filter);
		}

		if (error)
			goto failed;

		/* Increment IRQ and resource ID for next allocation */
		irq_rid++;
		irq++;
	}

	/* Sanity check; our shared IRQ must be available */
	if (sc->num_cpuirqs <= BCM_MIPS_IRQ_SHARED)
		panic("missing shared interrupt %d\n", BCM_MIPS_IRQ_SHARED);

	if (sc->cpuirqs[BCM_MIPS_IRQ_SHARED].irq_rid == -1)
		panic("shared interrupt %d unavailable", BCM_MIPS_IRQ_SHARED);

	/* Register PIC */
	if ((pic = intr_pic_register(dev, xref)) == NULL) {
		device_printf(dev, "error registering PIC\n");
		error = ENXIO;
		goto failed;
	}

	return (0);

failed:
	/* Deregister PIC before performing any other cleanup */
	if (pic != NULL)
		intr_pic_deregister(dev, 0);

	/* Deregister all interrupt sources */
	for (size_t i = 0; i < nitems(sc->isrcs); i++)
		intr_isrc_deregister(&sc->isrcs[i].isrc);

	/* Free our MIPS CPU interrupt handler state */
	for (u_int i = 0; i < sc->num_cpuirqs; i++)
		bcm_mips_fini_cpuirq(sc, &sc->cpuirqs[i]);

	BCM_MIPS_LOCK_DESTROY(sc);
	return (error);
}