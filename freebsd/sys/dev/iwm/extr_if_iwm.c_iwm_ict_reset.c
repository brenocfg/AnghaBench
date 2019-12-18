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
struct TYPE_2__ {int paddr; int /*<<< orphan*/  vaddr; } ;
struct iwm_softc {int /*<<< orphan*/  sc_flags; TYPE_1__ ict_dma; scalar_t__ ict_cur; } ;

/* Variables and functions */
 int IWM_CSR_DRAM_INIT_TBL_WRAP_CHECK ; 
 int IWM_CSR_DRAM_INIT_TBL_WRITE_POINTER ; 
 int IWM_CSR_DRAM_INT_TBL_ENABLE ; 
 int /*<<< orphan*/  IWM_CSR_DRAM_INT_TBL_REG ; 
 int /*<<< orphan*/  IWM_CSR_INT ; 
 int /*<<< orphan*/  IWM_FLAG_USE_ICT ; 
 int IWM_ICT_PADDR_SHIFT ; 
 int /*<<< orphan*/  IWM_ICT_SIZE ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwm_disable_interrupts (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_enable_interrupts (struct iwm_softc*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwm_ict_reset(struct iwm_softc *sc)
{
	iwm_disable_interrupts(sc);

	/* Reset ICT table. */
	memset(sc->ict_dma.vaddr, 0, IWM_ICT_SIZE);
	sc->ict_cur = 0;

	/* Set physical address of ICT table (4KB aligned). */
	IWM_WRITE(sc, IWM_CSR_DRAM_INT_TBL_REG,
	    IWM_CSR_DRAM_INT_TBL_ENABLE
	    | IWM_CSR_DRAM_INIT_TBL_WRITE_POINTER
	    | IWM_CSR_DRAM_INIT_TBL_WRAP_CHECK
	    | sc->ict_dma.paddr >> IWM_ICT_PADDR_SHIFT);

	/* Switch to ICT interrupt mode in driver. */
	sc->sc_flags |= IWM_FLAG_USE_ICT;

	/* Re-enable interrupts. */
	IWM_WRITE(sc, IWM_CSR_INT, ~0);
	iwm_enable_interrupts(sc);
}