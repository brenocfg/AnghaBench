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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct vmctx {int dummy; } ;
struct TYPE_3__ {int pba_offset; int pba_size; int table_offset; int table_count; scalar_t__ enabled; struct msix_table_entry* table; int /*<<< orphan*/ * pba_page_offset; int /*<<< orphan*/ * pba_page; } ;
struct pci_devinst {TYPE_1__ pi_msix; } ;
struct TYPE_4__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; } ;
struct passthru_softc {TYPE_2__ psc_sel; struct pci_devinst* psc_pi; } ;
struct msix_table_entry {int vector_control; int /*<<< orphan*/  msg_data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int MSIX_TABLE_ENTRY_SIZE ; 
 int PCIM_MSIX_VCTRL_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_setup_pptdev_msix (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
msix_table_write(struct vmctx *ctx, int vcpu, struct passthru_softc *sc,
		 uint64_t offset, int size, uint64_t data)
{
	struct pci_devinst *pi;
	struct msix_table_entry *entry;
	uint8_t *dest8;
	uint16_t *dest16;
	uint32_t *dest32;
	uint64_t *dest64;
	size_t entry_offset;
	uint32_t vector_control;
	int index;

	pi = sc->psc_pi;
	if (pi->pi_msix.pba_page != NULL && offset >= pi->pi_msix.pba_offset &&
	    offset < pi->pi_msix.pba_offset + pi->pi_msix.pba_size) {
		switch(size) {
		case 1:
			dest8 = (uint8_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			*dest8 = data;
			break;
		case 2:
			dest16 = (uint16_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			*dest16 = data;
			break;
		case 4:
			dest32 = (uint32_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			*dest32 = data;
			break;
		case 8:
			dest64 = (uint64_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			*dest64 = data;
			break;
		default:
			break;
		}
		return;
	}

	if (offset < pi->pi_msix.table_offset)
		return;

	offset -= pi->pi_msix.table_offset;
	index = offset / MSIX_TABLE_ENTRY_SIZE;
	if (index >= pi->pi_msix.table_count)
		return;

	entry = &pi->pi_msix.table[index];
	entry_offset = offset % MSIX_TABLE_ENTRY_SIZE;

	/* Only 4 byte naturally-aligned writes are supported */
	assert(size == 4);
	assert(entry_offset % 4 == 0);

	vector_control = entry->vector_control;
	dest32 = (uint32_t *)((void *)entry + entry_offset);
	*dest32 = data;
	/* If MSI-X hasn't been enabled, do nothing */
	if (pi->pi_msix.enabled) {
		/* If the entry is masked, don't set it up */
		if ((entry->vector_control & PCIM_MSIX_VCTRL_MASK) == 0 ||
		    (vector_control & PCIM_MSIX_VCTRL_MASK) == 0) {
			(void)vm_setup_pptdev_msix(ctx, vcpu,
			    sc->psc_sel.pc_bus, sc->psc_sel.pc_dev,
			    sc->psc_sel.pc_func, index, entry->addr,
			    entry->msg_data, entry->vector_control);
		}
	}
}