#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  size_t uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vmctx {int dummy; } ;
struct TYPE_6__ {scalar_t__ table_offset; int table_count; int table_bar; int pba_bar; scalar_t__ pba_offset; scalar_t__ pba_size; scalar_t__ pba_page_offset; int /*<<< orphan*/ * pba_page; } ;
struct pci_devinst {TYPE_3__ pi_msix; TYPE_2__* pi_bar; } ;
struct TYPE_4__ {int pc_bus; int pc_dev; int pc_func; } ;
struct passthru_softc {TYPE_1__ psc_sel; struct pci_devinst* psc_pi; } ;
struct TYPE_5__ {scalar_t__ addr; size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int MSIX_TABLE_ENTRY_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memfd ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_msix_pba_bar (struct pci_devinst*) ; 
 scalar_t__ pci_msix_table_bar (struct pci_devinst*) ; 
 scalar_t__ rounddown2 (scalar_t__,int) ; 
 scalar_t__ roundup2 (scalar_t__,int) ; 
 int vm_map_pptdev_mmio (struct vmctx*,int,int,int,scalar_t__,size_t,size_t) ; 
 int /*<<< orphan*/  warn (char*,int,int,int) ; 

__attribute__((used)) static int
init_msix_table(struct vmctx *ctx, struct passthru_softc *sc, uint64_t base)
{
	int b, s, f;
	int error, idx;
	size_t len, remaining;
	uint32_t table_size, table_offset;
	uint32_t pba_size, pba_offset;
	vm_paddr_t start;
	struct pci_devinst *pi = sc->psc_pi;

	assert(pci_msix_table_bar(pi) >= 0 && pci_msix_pba_bar(pi) >= 0);

	b = sc->psc_sel.pc_bus;
	s = sc->psc_sel.pc_dev;
	f = sc->psc_sel.pc_func;

	/* 
	 * If the MSI-X table BAR maps memory intended for
	 * other uses, it is at least assured that the table 
	 * either resides in its own page within the region, 
	 * or it resides in a page shared with only the PBA.
	 */
	table_offset = rounddown2(pi->pi_msix.table_offset, 4096);

	table_size = pi->pi_msix.table_offset - table_offset;
	table_size += pi->pi_msix.table_count * MSIX_TABLE_ENTRY_SIZE;
	table_size = roundup2(table_size, 4096);

	idx = pi->pi_msix.table_bar;
	start = pi->pi_bar[idx].addr;
	remaining = pi->pi_bar[idx].size;

	if (pi->pi_msix.pba_bar == pi->pi_msix.table_bar) {
		pba_offset = pi->pi_msix.pba_offset;
		pba_size = pi->pi_msix.pba_size;
		if (pba_offset >= table_offset + table_size ||
		    table_offset >= pba_offset + pba_size) {
			/*
			 * If the PBA does not share a page with the MSI-x
			 * tables, no PBA emulation is required.
			 */
			pi->pi_msix.pba_page = NULL;
			pi->pi_msix.pba_page_offset = 0;
		} else {
			/*
			 * The PBA overlaps with either the first or last
			 * page of the MSI-X table region.  Map the
			 * appropriate page.
			 */
			if (pba_offset <= table_offset)
				pi->pi_msix.pba_page_offset = table_offset;
			else
				pi->pi_msix.pba_page_offset = table_offset +
				    table_size - 4096;
			pi->pi_msix.pba_page = mmap(NULL, 4096, PROT_READ |
			    PROT_WRITE, MAP_SHARED, memfd, start +
			    pi->pi_msix.pba_page_offset);
			if (pi->pi_msix.pba_page == MAP_FAILED) {
				warn(
			    "Failed to map PBA page for MSI-X on %d/%d/%d",
				    b, s, f);
				return (-1);
			}
		}
	}

	/* Map everything before the MSI-X table */
	if (table_offset > 0) {
		len = table_offset;
		error = vm_map_pptdev_mmio(ctx, b, s, f, start, len, base);
		if (error)
			return (error);

		base += len;
		start += len;
		remaining -= len;
	}

	/* Skip the MSI-X table */
	base += table_size;
	start += table_size;
	remaining -= table_size;

	/* Map everything beyond the end of the MSI-X table */
	if (remaining > 0) {
		len = remaining;
		error = vm_map_pptdev_mmio(ctx, b, s, f, start, len, base);
		if (error)
			return (error);
	}

	return (0);
}