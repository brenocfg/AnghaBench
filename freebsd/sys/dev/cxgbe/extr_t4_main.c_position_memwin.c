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
struct memwin {int mw_curpos; int /*<<< orphan*/  mw_lock; } ;
struct adapter {int /*<<< orphan*/  pf; struct memwin* memwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_MEM_ACCESS_OFFSET ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NUM_MEMWIN ; 
 int PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int V_PFNUM (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 

__attribute__((used)) static void
position_memwin(struct adapter *sc, int idx, uint32_t addr)
{
	struct memwin *mw;
	uint32_t pf;
	uint32_t reg;

	MPASS(idx >= 0 && idx < NUM_MEMWIN);
	mw = &sc->memwin[idx];
	rw_assert(&mw->mw_lock, RA_WLOCKED);

	if (is_t4(sc)) {
		pf = 0;
		mw->mw_curpos = addr & ~0xf;	/* start must be 16B aligned */
	} else {
		pf = V_PFNUM(sc->pf);
		mw->mw_curpos = addr & ~0x7f;	/* start must be 128B aligned */
	}
	reg = PCIE_MEM_ACCESS_REG(A_PCIE_MEM_ACCESS_OFFSET, idx);
	t4_write_reg(sc, reg, mw->mw_curpos | pf);
	t4_read_reg(sc, reg);	/* flush */
}