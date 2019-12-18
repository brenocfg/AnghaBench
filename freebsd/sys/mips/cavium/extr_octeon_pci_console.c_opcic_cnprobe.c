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
struct opcic_softc {scalar_t__ sc_base_addr; scalar_t__ sc_flags; } ;
struct cvmx_bootmem_named_block_desc {scalar_t__ base_addr; } ;
struct consdev {int /*<<< orphan*/  cn_pri; int /*<<< orphan*/  cn_name; struct opcic_softc* cn_arg; } ;
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int /*<<< orphan*/  CN_REMOTE ; 
#define  CVMX_BOARD_TYPE_CUST_RADISYS_RSYS4GBE 128 
 char* OCTEON_PCI_CONSOLE_BLOCK_NAME ; 
 scalar_t__ OPCIC_FLAG_RSYS ; 
 int RB_SERIAL ; 
 int boothowto ; 
 struct cvmx_bootmem_named_block_desc* cvmx_bootmem_find_named_block (char*) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 struct opcic_softc opcic_instance ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,struct opcic_softc*) ; 

__attribute__((used)) static void
opcic_cnprobe(struct consdev *cp)
{
	const struct cvmx_bootmem_named_block_desc *pci_console_block;
	struct opcic_softc *sc;

	sc = &opcic_instance;
	sc->sc_flags = 0;
	sc->sc_base_addr = 0;

	cp->cn_pri = CN_DEAD;

	switch (cvmx_sysinfo_get()->board_type) {
#ifdef OCTEON_VENDOR_RADISYS
	case CVMX_BOARD_TYPE_CUST_RADISYS_RSYS4GBE:
		pci_console_block =
		    cvmx_bootmem_find_named_block("rsys_gbl_memory");
		if (pci_console_block != NULL) {
			sc->sc_flags |= OPCIC_FLAG_RSYS;
			sc->sc_base_addr = pci_console_block->base_addr;
			break;
		}
#endif
	default:
		pci_console_block =
		    cvmx_bootmem_find_named_block(OCTEON_PCI_CONSOLE_BLOCK_NAME);
		if (pci_console_block == NULL)
			return;
		sc->sc_base_addr = pci_console_block->base_addr;
		break;
	}

	cp->cn_arg = sc;
	snprintf(cp->cn_name, sizeof cp->cn_name, "opcic@%p", cp->cn_arg);
	cp->cn_pri = (boothowto & RB_SERIAL) ? CN_REMOTE : CN_NORMAL;
}