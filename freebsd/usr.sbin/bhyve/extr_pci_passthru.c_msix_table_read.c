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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int pba_offset; int pba_size; int table_offset; int table_count; struct msix_table_entry* table; int /*<<< orphan*/ * pba_page_offset; int /*<<< orphan*/ * pba_page; } ;
struct pci_devinst {TYPE_1__ pi_msix; } ;
struct passthru_softc {struct pci_devinst* psc_pi; } ;
struct msix_table_entry {int dummy; } ;

/* Variables and functions */
 int MSIX_TABLE_ENTRY_SIZE ; 

__attribute__((used)) static uint64_t
msix_table_read(struct passthru_softc *sc, uint64_t offset, int size)
{
	struct pci_devinst *pi;
	struct msix_table_entry *entry;
	uint8_t *src8;
	uint16_t *src16;
	uint32_t *src32;
	uint64_t *src64;
	uint64_t data;
	size_t entry_offset;
	int index;

	pi = sc->psc_pi;
	if (pi->pi_msix.pba_page != NULL && offset >= pi->pi_msix.pba_offset &&
	    offset < pi->pi_msix.pba_offset + pi->pi_msix.pba_size) {
		switch(size) {
		case 1:
			src8 = (uint8_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			data = *src8;
			break;
		case 2:
			src16 = (uint16_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			data = *src16;
			break;
		case 4:
			src32 = (uint32_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			data = *src32;
			break;
		case 8:
			src64 = (uint64_t *)(pi->pi_msix.pba_page + offset -
			    pi->pi_msix.pba_page_offset);
			data = *src64;
			break;
		default:
			return (-1);
		}
		return (data);
	}

	if (offset < pi->pi_msix.table_offset)
		return (-1);

	offset -= pi->pi_msix.table_offset;
	index = offset / MSIX_TABLE_ENTRY_SIZE;
	if (index >= pi->pi_msix.table_count)
		return (-1);

	entry = &pi->pi_msix.table[index];
	entry_offset = offset % MSIX_TABLE_ENTRY_SIZE;

	switch(size) {
	case 1:
		src8 = (uint8_t *)((void *)entry + entry_offset);
		data = *src8;
		break;
	case 2:
		src16 = (uint16_t *)((void *)entry + entry_offset);
		data = *src16;
		break;
	case 4:
		src32 = (uint32_t *)((void *)entry + entry_offset);
		data = *src32;
		break;
	case 8:
		src64 = (uint64_t *)((void *)entry + entry_offset);
		data = *src64;
		break;
	default:
		return (-1);
	}

	return (data);
}