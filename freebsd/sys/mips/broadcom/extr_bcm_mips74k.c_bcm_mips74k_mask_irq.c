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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ num_cpuirqs; } ;
struct bcm_mips74k_softc {int /*<<< orphan*/  mem; TYPE_1__ bcm_mips; } ;

/* Variables and functions */
 scalar_t__ BCMA_OOB_NUM_BUSLINES ; 
 int /*<<< orphan*/  BCM_MIPS74K_INTR_SEL (scalar_t__) ; 
 int /*<<< orphan*/  BCM_MIPS74K_INTR_SEL_FLAG (scalar_t__) ; 
 scalar_t__ BCM_MIPS74K_NUM_INTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_mips74k_mask_irq(struct bcm_mips74k_softc *sc, u_int mips_irq, u_int ivec)
{
	uint32_t oobsel;

	KASSERT(mips_irq < sc->bcm_mips.num_cpuirqs, ("invalid MIPS IRQ %u",
	    mips_irq));
	KASSERT(mips_irq < BCM_MIPS74K_NUM_INTR, ("unsupported MIPS IRQ %u",
	    mips_irq));
	KASSERT(ivec < BCMA_OOB_NUM_BUSLINES, ("invalid backplane ivec"));

	oobsel = bus_read_4(sc->mem, BCM_MIPS74K_INTR_SEL(mips_irq));
	oobsel &= ~(BCM_MIPS74K_INTR_SEL_FLAG(ivec));
	bus_write_4(sc->mem, BCM_MIPS74K_INTR_SEL(mips_irq), oobsel);
}