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
struct memwin_init {int base; int /*<<< orphan*/  aperture; } ;
struct memwin {int mw_base; int /*<<< orphan*/  mw_lock; int /*<<< orphan*/  mw_aperture; scalar_t__ mw_curpos; } ;
struct adapter {struct memwin* memwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_MEM_ACCESS_BASE_WIN ; 
 int NUM_MEMWIN ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCIM_BAR_MEM_BASE ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int V_BIR (int /*<<< orphan*/ ) ; 
 int V_WINDOW (scalar_t__) ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  position_memwin (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int t4_hw_pci_read_cfg4 (struct adapter*,int /*<<< orphan*/ ) ; 
 struct memwin_init* t4_memwin ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 struct memwin_init* t5_memwin ; 

__attribute__((used)) static void
setup_memwin(struct adapter *sc)
{
	const struct memwin_init *mw_init;
	struct memwin *mw;
	int i;
	uint32_t bar0;

	if (is_t4(sc)) {
		/*
		 * Read low 32b of bar0 indirectly via the hardware backdoor
		 * mechanism.  Works from within PCI passthrough environments
		 * too, where rman_get_start() can return a different value.  We
		 * need to program the T4 memory window decoders with the actual
		 * addresses that will be coming across the PCIe link.
		 */
		bar0 = t4_hw_pci_read_cfg4(sc, PCIR_BAR(0));
		bar0 &= (uint32_t) PCIM_BAR_MEM_BASE;

		mw_init = &t4_memwin[0];
	} else {
		/* T5+ use the relative offset inside the PCIe BAR */
		bar0 = 0;

		mw_init = &t5_memwin[0];
	}

	for (i = 0, mw = &sc->memwin[0]; i < NUM_MEMWIN; i++, mw_init++, mw++) {
		rw_init(&mw->mw_lock, "memory window access");
		mw->mw_base = mw_init->base;
		mw->mw_aperture = mw_init->aperture;
		mw->mw_curpos = 0;
		t4_write_reg(sc,
		    PCIE_MEM_ACCESS_REG(A_PCIE_MEM_ACCESS_BASE_WIN, i),
		    (mw->mw_base + bar0) | V_BIR(0) |
		    V_WINDOW(ilog2(mw->mw_aperture) - 10));
		rw_wlock(&mw->mw_lock);
		position_memwin(sc, i, 0);
		rw_wunlock(&mw->mw_lock);
	}

	/* flush */
	t4_read_reg(sc, PCIE_MEM_ACCESS_REG(A_PCIE_MEM_ACCESS_BASE_WIN, 2));
}