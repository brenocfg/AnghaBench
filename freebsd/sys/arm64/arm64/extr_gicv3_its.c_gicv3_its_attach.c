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
typedef  int uint32_t ;
struct gicv3_its_softc {int sc_irq_length; int sc_irq_base; TYPE_1__* sc_irqs; int /*<<< orphan*/  sc_irq_alloc; int /*<<< orphan*/  sc_its_dev_list; int /*<<< orphan*/ ** sc_its_cols; int /*<<< orphan*/  sc_cpus; int /*<<< orphan*/  sc_its_cmd_lock; int /*<<< orphan*/  sc_its_dev_lock; int /*<<< orphan*/ * sc_its_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int iidr_mask; int iidr; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  desc; } ;
struct TYPE_4__ {int gi_irq; int /*<<< orphan*/  gi_isrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int GIC_FIRST_LPI ; 
 int /*<<< orphan*/  GITS_CTLR ; 
 int GITS_CTLR_EN ; 
 int /*<<< orphan*/  GITS_IIDR ; 
 int MAXMEMDOM ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int M_FIRSTFIT ; 
 int /*<<< orphan*/  M_GICV3_ITS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_cpus ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * cpuset_domain ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int gic_its_read_4 (struct gicv3_its_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_its_write_4 (struct gicv3_its_softc*,int /*<<< orphan*/ ,int) ; 
 int gicv3_get_nirqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gicv3_its_cmdq_init (struct gicv3_its_softc*) ; 
 int /*<<< orphan*/  gicv3_its_conftable_init (struct gicv3_its_softc*) ; 
 int /*<<< orphan*/  gicv3_its_pendtables_init (struct gicv3_its_softc*) ; 
 int gicv3_its_table_init (int /*<<< orphan*/ ,struct gicv3_its_softc*) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  its_init_cpu (int /*<<< orphan*/ ,struct gicv3_its_softc*) ; 
 TYPE_2__* its_quirks ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_maxid ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nitems (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_create (char*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
gicv3_its_attach(device_t dev)
{
	struct gicv3_its_softc *sc;
	const char *name;
	uint32_t iidr;
	int domain, err, i, rid;

	sc = device_get_softc(dev);

	sc->sc_irq_length = gicv3_get_nirqs(dev);
	sc->sc_irq_base = GIC_FIRST_LPI;
	sc->sc_irq_base += device_get_unit(dev) * sc->sc_irq_length;

	rid = 0;
	sc->sc_its_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_its_res == NULL) {
		device_printf(dev, "Could not allocate memory\n");
		return (ENXIO);
	}

	iidr = gic_its_read_4(sc, GITS_IIDR);
	for (i = 0; i < nitems(its_quirks); i++) {
		if ((iidr & its_quirks[i].iidr_mask) == its_quirks[i].iidr) {
			if (bootverbose) {
				device_printf(dev, "Applying %s\n",
				    its_quirks[i].desc);
			}
			its_quirks[i].func(dev);
			break;
		}
	}

	/* Allocate the private tables */
	err = gicv3_its_table_init(dev, sc);
	if (err != 0)
		return (err);

	/* Protects access to the device list */
	mtx_init(&sc->sc_its_dev_lock, "ITS device lock", NULL, MTX_SPIN);

	/* Protects access to the ITS command circular buffer. */
	mtx_init(&sc->sc_its_cmd_lock, "ITS cmd lock", NULL, MTX_SPIN);

	CPU_ZERO(&sc->sc_cpus);
	if (bus_get_domain(dev, &domain) == 0) {
		if (domain < MAXMEMDOM)
			CPU_COPY(&cpuset_domain[domain], &sc->sc_cpus);
	} else {
		CPU_COPY(&all_cpus, &sc->sc_cpus);
	}

	/* Allocate the command circular buffer */
	gicv3_its_cmdq_init(sc);

	/* Allocate the per-CPU collections */
	for (int cpu = 0; cpu <= mp_maxid; cpu++)
		if (CPU_ISSET(cpu, &sc->sc_cpus) != 0)
			sc->sc_its_cols[cpu] = malloc(
			    sizeof(*sc->sc_its_cols[0]), M_GICV3_ITS,
			    M_WAITOK | M_ZERO);
		else
			sc->sc_its_cols[cpu] = NULL;

	/* Enable the ITS */
	gic_its_write_4(sc, GITS_CTLR,
	    gic_its_read_4(sc, GITS_CTLR) | GITS_CTLR_EN);

	/* Create the LPI configuration table */
	gicv3_its_conftable_init(sc);

	/* And the pending tebles */
	gicv3_its_pendtables_init(sc);

	/* Enable LPIs on this CPU */
	its_init_cpu(dev, sc);

	TAILQ_INIT(&sc->sc_its_dev_list);

	/*
	 * Create the vmem object to allocate INTRNG IRQs from. We try to
	 * use all IRQs not already used by the GICv3.
	 * XXX: This assumes there are no other interrupt controllers in the
	 * system.
	 */
	sc->sc_irq_alloc = vmem_create("GICv3 ITS IRQs", 0,
	    gicv3_get_nirqs(dev), 1, 1, M_FIRSTFIT | M_WAITOK);

	sc->sc_irqs = malloc(sizeof(*sc->sc_irqs) * sc->sc_irq_length,
	    M_GICV3_ITS, M_WAITOK | M_ZERO);
	name = device_get_nameunit(dev);
	for (i = 0; i < sc->sc_irq_length; i++) {
		sc->sc_irqs[i].gi_irq = i;
		err = intr_isrc_register(&sc->sc_irqs[i].gi_isrc, dev, 0,
		    "%s,%u", name, i);
	}

	return (0);
}