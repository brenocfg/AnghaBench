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
typedef  int uint32_t ;
typedef  int u_int ;
struct resource {int dummy; } ;
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {scalar_t__ isrc_handlers; int isrc_flags; int /*<<< orphan*/  isrc_cpu; } ;
struct gic_v3_softc {int /*<<< orphan*/  gic_mtx; } ;
struct gic_v3_irqsrc {int gi_irq; int gi_pol; int gi_trig; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIST ; 
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ GICD_ICFGR (int) ; 
 scalar_t__ GICR_SGI_BASE_SIZE ; 
 int GIC_FIRST_PPI ; 
 int GIC_LAST_PPI ; 
 int GIC_LAST_SPI ; 
 int INTR_ISRCF_PPI ; 
 int INTR_POLARITY_CONFORM ; 
 int INTR_TRIGGER_CONFORM ; 
 int INTR_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REDIST ; 
 int /*<<< orphan*/  cpuid ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int do_gic_v3_map_intr (int /*<<< orphan*/ ,struct intr_map_data*,int*,int*,int*) ; 
 int gic_d_read (struct gic_v3_softc*,int,scalar_t__) ; 
 int /*<<< orphan*/  gic_d_write (struct gic_v3_softc*,int,scalar_t__,int) ; 
 int gic_r_read (struct gic_v3_softc*,int,scalar_t__) ; 
 int /*<<< orphan*/  gic_r_write (struct gic_v3_softc*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  gic_v3_bind_intr (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 int /*<<< orphan*/  gic_v3_wait_for_rwp (struct gic_v3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gic_v3_setup_intr(device_t dev, struct intr_irqsrc *isrc,
    struct resource *res, struct intr_map_data *data)
{
	struct gic_v3_softc *sc = device_get_softc(dev);
	struct gic_v3_irqsrc *gi = (struct gic_v3_irqsrc *)isrc;
	enum intr_trigger trig;
	enum intr_polarity pol;
	uint32_t reg;
	u_int irq;
	int error;

	if (data == NULL)
		return (ENOTSUP);

	error = do_gic_v3_map_intr(dev, data, &irq, &pol, &trig);
	if (error != 0)
		return (error);

	if (gi->gi_irq != irq || pol == INTR_POLARITY_CONFORM ||
	    trig == INTR_TRIGGER_CONFORM)
		return (EINVAL);

	/* Compare config if this is not first setup. */
	if (isrc->isrc_handlers != 0) {
		if (pol != gi->gi_pol || trig != gi->gi_trig)
			return (EINVAL);
		else
			return (0);
	}

	gi->gi_pol = pol;
	gi->gi_trig = trig;

	/*
	 * XXX - In case that per CPU interrupt is going to be enabled in time
	 *       when SMP is already started, we need some IPI call which
	 *       enables it on others CPUs. Further, it's more complicated as
	 *       pic_enable_source() and pic_disable_source() should act on
	 *       per CPU basis only. Thus, it should be solved here somehow.
	 */
	if (isrc->isrc_flags & INTR_ISRCF_PPI)
		CPU_SET(PCPU_GET(cpuid), &isrc->isrc_cpu);

	if (irq >= GIC_FIRST_PPI && irq <= GIC_LAST_SPI) {
		mtx_lock_spin(&sc->gic_mtx);

		/* Set the trigger and polarity */
		if (irq <= GIC_LAST_PPI)
			reg = gic_r_read(sc, 4,
			    GICR_SGI_BASE_SIZE + GICD_ICFGR(irq));
		else
			reg = gic_d_read(sc, 4, GICD_ICFGR(irq));
		if (trig == INTR_TRIGGER_LEVEL)
			reg &= ~(2 << ((irq % 16) * 2));
		else
			reg |= 2 << ((irq % 16) * 2);

		if (irq <= GIC_LAST_PPI) {
			gic_r_write(sc, 4,
			    GICR_SGI_BASE_SIZE + GICD_ICFGR(irq), reg);
			gic_v3_wait_for_rwp(sc, REDIST);
		} else {
			gic_d_write(sc, 4, GICD_ICFGR(irq), reg);
			gic_v3_wait_for_rwp(sc, DIST);
		}

		mtx_unlock_spin(&sc->gic_mtx);

		gic_v3_bind_intr(dev, isrc);
	}

	return (0);
}