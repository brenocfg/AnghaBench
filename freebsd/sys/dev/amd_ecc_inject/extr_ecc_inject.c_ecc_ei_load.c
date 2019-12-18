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

/* Variables and functions */
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 int DRAM_ECC_EN ; 
 int ENXIO ; 
 int /*<<< orphan*/  NB_MCA_CFG ; 
 int /*<<< orphan*/  cpu_id ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/ * nbdev ; 
 int /*<<< orphan*/ * pci_find_bsf (int /*<<< orphan*/ ,int,int) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ecc_ei_load(void)
{
	uint32_t val;

	if (cpu_vendor_id != CPU_VENDOR_AMD || CPUID_TO_FAMILY(cpu_id) < 0x10) {
		printf("DRAM ECC error injection is not supported\n");
		return (ENXIO);
	}
	nbdev = pci_find_bsf(0, 24, 3);
	if (nbdev == NULL) {
		printf("Couldn't find NB PCI device\n");
		return (ENXIO);
	}
	val = pci_read_config(nbdev, NB_MCA_CFG, 4);
	if ((val & DRAM_ECC_EN) == 0) {
		printf("DRAM ECC is not supported or disabled\n");
		return (ENXIO);
	}
	printf("DRAM ECC error injection support loaded\n");
	return (0);
}