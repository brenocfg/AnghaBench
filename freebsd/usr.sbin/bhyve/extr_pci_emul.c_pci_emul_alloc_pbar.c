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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct pci_devinst {TYPE_1__* pi_bar; } ;
typedef  enum pcibar_type { ____Placeholder_pcibar_type } pcibar_type ;
struct TYPE_2__ {int type; int addr; int size; } ;

/* Variables and functions */
#define  PCIBAR_IO 131 
#define  PCIBAR_MEM32 130 
#define  PCIBAR_MEM64 129 
 int PCIBAR_MEMHI64 ; 
#define  PCIBAR_NONE 128 
 int PCIM_BAR_IO_BASE ; 
 int PCIM_BAR_IO_SPACE ; 
 int PCIM_BAR_MEM_32 ; 
 int PCIM_BAR_MEM_64 ; 
 int PCIM_BAR_MEM_BASE ; 
 int PCIM_BAR_MEM_PREFETCH ; 
 int PCIM_BAR_MEM_SPACE ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int PCI_BARMAX ; 
 int PCI_EMUL_IOLIMIT ; 
 int PCI_EMUL_MEMLIMIT32 ; 
 int PCI_EMUL_MEMLIMIT64 ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long flsl (int) ; 
 int pci_emul_alloc_resource (int*,int,int,int*) ; 
 int pci_emul_iobase ; 
 int pci_emul_membase32 ; 
 int pci_emul_membase64 ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata32 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  register_bar (struct pci_devinst*,int) ; 

int
pci_emul_alloc_pbar(struct pci_devinst *pdi, int idx, uint64_t hostbase,
		    enum pcibar_type type, uint64_t size)
{
	int error;
	uint64_t *baseptr, limit, addr, mask, lobits, bar;
	uint16_t cmd, enbit;

	assert(idx >= 0 && idx <= PCI_BARMAX);

	if ((size & (size - 1)) != 0)
		size = 1UL << flsl(size);	/* round up to a power of 2 */

	/* Enforce minimum BAR sizes required by the PCI standard */
	if (type == PCIBAR_IO) {
		if (size < 4)
			size = 4;
	} else {
		if (size < 16)
			size = 16;
	}

	switch (type) {
	case PCIBAR_NONE:
		baseptr = NULL;
		addr = mask = lobits = enbit = 0;
		break;
	case PCIBAR_IO:
		baseptr = &pci_emul_iobase;
		limit = PCI_EMUL_IOLIMIT;
		mask = PCIM_BAR_IO_BASE;
		lobits = PCIM_BAR_IO_SPACE;
		enbit = PCIM_CMD_PORTEN;
		break;
	case PCIBAR_MEM64:
		/*
		 * XXX
		 * Some drivers do not work well if the 64-bit BAR is allocated
		 * above 4GB. Allow for this by allocating small requests under
		 * 4GB unless then allocation size is larger than some arbitrary
		 * number (32MB currently).
		 */
		if (size > 32 * 1024 * 1024) {
			/*
			 * XXX special case for device requiring peer-peer DMA
			 */
			if (size == 0x100000000UL)
				baseptr = &hostbase;
			else
				baseptr = &pci_emul_membase64;
			limit = PCI_EMUL_MEMLIMIT64;
			mask = PCIM_BAR_MEM_BASE;
			lobits = PCIM_BAR_MEM_SPACE | PCIM_BAR_MEM_64 |
				 PCIM_BAR_MEM_PREFETCH;
		} else {
			baseptr = &pci_emul_membase32;
			limit = PCI_EMUL_MEMLIMIT32;
			mask = PCIM_BAR_MEM_BASE;
			lobits = PCIM_BAR_MEM_SPACE | PCIM_BAR_MEM_64;
		}
		enbit = PCIM_CMD_MEMEN;
		break;
	case PCIBAR_MEM32:
		baseptr = &pci_emul_membase32;
		limit = PCI_EMUL_MEMLIMIT32;
		mask = PCIM_BAR_MEM_BASE;
		lobits = PCIM_BAR_MEM_SPACE | PCIM_BAR_MEM_32;
		enbit = PCIM_CMD_MEMEN;
		break;
	default:
		printf("pci_emul_alloc_base: invalid bar type %d\n", type);
		assert(0);
	}

	if (baseptr != NULL) {
		error = pci_emul_alloc_resource(baseptr, limit, size, &addr);
		if (error != 0)
			return (error);
	}

	pdi->pi_bar[idx].type = type;
	pdi->pi_bar[idx].addr = addr;
	pdi->pi_bar[idx].size = size;

	/* Initialize the BAR register in config space */
	bar = (addr & mask) | lobits;
	pci_set_cfgdata32(pdi, PCIR_BAR(idx), bar);

	if (type == PCIBAR_MEM64) {
		assert(idx + 1 <= PCI_BARMAX);
		pdi->pi_bar[idx + 1].type = PCIBAR_MEMHI64;
		pci_set_cfgdata32(pdi, PCIR_BAR(idx + 1), bar >> 32);
	}

	cmd = pci_get_cfgdata16(pdi, PCIR_COMMAND);
	if ((cmd & enbit) != enbit)
		pci_set_cfgdata16(pdi, PCIR_COMMAND, cmd | enbit);
	register_bar(pdi, idx);

	return (0);
}