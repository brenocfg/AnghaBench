#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ num_cpuirqs; } ;
struct bcm_bmips_softc {int /*<<< orphan*/  cfg; TYPE_1__ bcm_mips; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SIBA_CFG0_INTVEC ; 
 int /*<<< orphan*/  SIBA_CFG0_IPSFLAG ; 
 int SIBA_IPS_INT1_MASK ; 
 int SIBA_IPS_INT_MASK (scalar_t__) ; 
 int SIBA_IPS_INT_SHIFT (scalar_t__) ; 
 scalar_t__ SIBA_MAX_INTR ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bcm_bmips_mask_irq(struct bcm_bmips_softc *sc, u_int mips_irq, u_int ivec)
{
	KASSERT(ivec < SIBA_MAX_INTR, ("invalid sbflag# ivec"));
	KASSERT(mips_irq < sc->bcm_mips.num_cpuirqs, ("invalid MIPS IRQ %u",
	    mips_irq));

	if (mips_irq == 0) {
		uint32_t sbintvec;

		sbintvec = bus_read_4(sc->cfg, SIBA_CFG0_INTVEC);
		sbintvec &= ~(1 << ivec);
		bus_write_4(sc->cfg, SIBA_CFG0_INTVEC, sbintvec);
	} else {
		uint32_t ipsflag;

		/* Can we route this via ipsflag? */
		KASSERT(((1 << ivec) & SIBA_IPS_INT1_MASK) != 0,
		    ("cannot route high sbflag# ivec %u", ivec));

		ipsflag = bus_read_4(sc->cfg, SIBA_CFG0_IPSFLAG);
		ipsflag &= ~(
		    ((1 << ivec) << SIBA_IPS_INT_SHIFT(mips_irq)) &
		    SIBA_IPS_INT_MASK(mips_irq));
		bus_write_4(sc->cfg, SIBA_CFG0_IPSFLAG, ipsflag);
	}

}