#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  size_t u_int ;
struct intr_irqsrc {int dummy; } ;
struct TYPE_3__ {int nregions; int /*<<< orphan*/ ** regions; } ;
struct gic_v3_softc {int gic_nirqs; int gic_idbits; void* gic_pidr2; TYPE_2__* gic_irqs; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** gic_res; TYPE_1__ gic_redists; int /*<<< orphan*/ * gic_dist; int /*<<< orphan*/  gic_mtx; int /*<<< orphan*/  gic_registered; } ;
typedef  int (* gic_v3_initseq_t ) (struct gic_v3_softc*) ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t gi_irq; struct intr_irqsrc gi_isrc; int /*<<< orphan*/  gi_trig; int /*<<< orphan*/  gi_pol; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GICD_PIDR2 ; 
 int /*<<< orphan*/  GICD_TYPER ; 
 int GICD_TYPER_IDBITS (void*) ; 
 int GICD_TYPER_I_NUM (void*) ; 
 size_t GIC_FIRST_PPI ; 
 size_t GIC_FIRST_SGI ; 
 size_t GIC_FIRST_SPI ; 
 int GIC_I_NUM_MAX ; 
 size_t GIC_LAST_PPI ; 
 size_t GIC_LAST_SGI ; 
 int /*<<< orphan*/  INTR_ISRCF_IPI ; 
 int /*<<< orphan*/  INTR_ISRCF_PPI ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_CONFORM ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_GIC_V3 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* gic_d_read (struct gic_v3_softc*,int,int /*<<< orphan*/ ) ; 
 int gic_v3_primary_init (struct gic_v3_softc*) ; 
 int intr_isrc_register (struct intr_irqsrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct gic_v3_softc*) ; 

int
gic_v3_attach(device_t dev)
{
	struct gic_v3_softc *sc;
	gic_v3_initseq_t *init_func;
	uint32_t typer;
	int rid;
	int err;
	size_t i;
	u_int irq;
	const char *name;

	sc = device_get_softc(dev);
	sc->gic_registered = FALSE;
	sc->dev = dev;
	err = 0;

	/* Initialize mutex */
	mtx_init(&sc->gic_mtx, "GICv3 lock", NULL, MTX_SPIN);

	/*
	 * Allocate array of struct resource.
	 * One entry for Distributor and all remaining for Re-Distributor.
	 */
	sc->gic_res = malloc(
	    sizeof(*sc->gic_res) * (sc->gic_redists.nregions + 1),
	    M_GIC_V3, M_WAITOK);

	/* Now allocate corresponding resources */
	for (i = 0, rid = 0; i < (sc->gic_redists.nregions + 1); i++, rid++) {
		sc->gic_res[rid] = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		    &rid, RF_ACTIVE);
		if (sc->gic_res[rid] == NULL)
			return (ENXIO);
	}

	/*
	 * Distributor interface
	 */
	sc->gic_dist = sc->gic_res[0];

	/*
	 * Re-Dristributor interface
	 */
	/* Allocate space under region descriptions */
	sc->gic_redists.regions = malloc(
	    sizeof(*sc->gic_redists.regions) * sc->gic_redists.nregions,
	    M_GIC_V3, M_WAITOK);

	/* Fill-up bus_space information for each region. */
	for (i = 0, rid = 1; i < sc->gic_redists.nregions; i++, rid++)
		sc->gic_redists.regions[i] = sc->gic_res[rid];

	/* Get the number of supported SPI interrupts */
	typer = gic_d_read(sc, 4, GICD_TYPER);
	sc->gic_nirqs = GICD_TYPER_I_NUM(typer);
	if (sc->gic_nirqs > GIC_I_NUM_MAX)
		sc->gic_nirqs = GIC_I_NUM_MAX;

	sc->gic_irqs = malloc(sizeof(*sc->gic_irqs) * sc->gic_nirqs,
	    M_GIC_V3, M_WAITOK | M_ZERO);
	name = device_get_nameunit(dev);
	for (irq = 0; irq < sc->gic_nirqs; irq++) {
		struct intr_irqsrc *isrc;

		sc->gic_irqs[irq].gi_irq = irq;
		sc->gic_irqs[irq].gi_pol = INTR_POLARITY_CONFORM;
		sc->gic_irqs[irq].gi_trig = INTR_TRIGGER_CONFORM;

		isrc = &sc->gic_irqs[irq].gi_isrc;
		if (irq <= GIC_LAST_SGI) {
			err = intr_isrc_register(isrc, sc->dev,
			    INTR_ISRCF_IPI, "%s,i%u", name, irq - GIC_FIRST_SGI);
		} else if (irq <= GIC_LAST_PPI) {
			err = intr_isrc_register(isrc, sc->dev,
			    INTR_ISRCF_PPI, "%s,p%u", name, irq - GIC_FIRST_PPI);
		} else {
			err = intr_isrc_register(isrc, sc->dev, 0,
			    "%s,s%u", name, irq - GIC_FIRST_SPI);
		}
		if (err != 0) {
			/* XXX call intr_isrc_deregister() */
			free(sc->gic_irqs, M_DEVBUF);
			return (err);
		}
	}

	/*
	 * Read the Peripheral ID2 register. This is an implementation
	 * defined register, but seems to be implemented in all GICv3
	 * parts and Linux expects it to be there.
	 */
	sc->gic_pidr2 = gic_d_read(sc, 4, GICD_PIDR2);

	/* Get the number of supported interrupt identifier bits */
	sc->gic_idbits = GICD_TYPER_IDBITS(typer);

	if (bootverbose) {
		device_printf(dev, "SPIs: %u, IDs: %u\n",
		    sc->gic_nirqs, (1 << sc->gic_idbits) - 1);
	}

	/* Train init sequence for boot CPU */
	for (init_func = gic_v3_primary_init; *init_func != NULL; init_func++) {
		err = (*init_func)(sc);
		if (err != 0)
			return (err);
	}

	return (0);
}