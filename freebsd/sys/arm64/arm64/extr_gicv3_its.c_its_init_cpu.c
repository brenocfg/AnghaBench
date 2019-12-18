#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  size_t u_int ;
struct redist_pcpu {int lpi_enabled; int /*<<< orphan*/  res; } ;
struct gicv3_its_softc {TYPE_1__** sc_its_cols; int /*<<< orphan*/  sc_cpus; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {size_t col_id; int /*<<< orphan*/  col_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GICR_TYPER ; 
 int /*<<< orphan*/  GICR_TYPER_CPUNUM (int /*<<< orphan*/ ) ; 
 int GICR_TYPER_PLPIS ; 
 int /*<<< orphan*/  GITS_TYPER ; 
 int GITS_TYPER_PTA ; 
 size_t PCPU_GET (size_t) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int gic_its_read_8 (struct gicv3_its_softc*,int /*<<< orphan*/ ) ; 
 int gic_r_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_r_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct redist_pcpu* gicv3_get_redist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_cmd_invall (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  its_cmd_mapc (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  its_init_cpu_lpi (int /*<<< orphan*/ ,struct gicv3_its_softc*) ; 
 int /*<<< orphan*/  rman_get_virtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
its_init_cpu(device_t dev, struct gicv3_its_softc *sc)
{
	device_t gicv3;
	vm_paddr_t target;
	u_int cpuid;
	struct redist_pcpu *rpcpu;

	gicv3 = device_get_parent(dev);
	cpuid = PCPU_GET(cpuid);
	if (!CPU_ISSET(cpuid, &sc->sc_cpus))
		return (0);

	/* Check if the ITS is enabled on this CPU */
	if ((gic_r_read_4(gicv3, GICR_TYPER) & GICR_TYPER_PLPIS) == 0)
		return (ENXIO);

	rpcpu = gicv3_get_redist(dev);

	/* Do per-cpu LPI init once */
	if (!rpcpu->lpi_enabled) {
		its_init_cpu_lpi(dev, sc);
		rpcpu->lpi_enabled = true;
	}

	if ((gic_its_read_8(sc, GITS_TYPER) & GITS_TYPER_PTA) != 0) {
		/* This ITS wants the redistributor physical address */
		target = vtophys(rman_get_virtual(&rpcpu->res));
	} else {
		/* This ITS wants the unique processor number */
		target = GICR_TYPER_CPUNUM(gic_r_read_8(gicv3, GICR_TYPER));
	}

	sc->sc_its_cols[cpuid]->col_target = target;
	sc->sc_its_cols[cpuid]->col_id = cpuid;

	its_cmd_mapc(dev, sc->sc_its_cols[cpuid], 1);
	its_cmd_invall(dev, sc->sc_its_cols[cpuid]);

	return (0);
}