#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct range {int start; int end; } ;
struct TYPE_3__ {unsigned int bus; unsigned int slot; int vendor; int device; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ BASE_VALID (int) ; 
 int FAM10H_PCI_MMCONF_BASE ; 
 int MMCONF_MASK ; 
 int MMCONF_SIZE ; 
 int MMCONF_UNIT ; 
 int MSR_K8_SYSCFG ; 
 int MSR_K8_TOP_MEM2 ; 
 int PCI_VENDOR_ID ; 
 int /*<<< orphan*/  cmp_range ; 
 int /*<<< orphan*/  early_pci_allowed () ; 
 int fam10h_pci_mmconf_base ; 
 int max (int,unsigned long long) ; 
 TYPE_1__* pci_probes ; 
 int /*<<< orphan*/  rdmsrl (int,int) ; 
 int read_pci_config (unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  sort (struct range*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_fam10h_pci_mmconf_base(void)
{
	int i;
	unsigned bus;
	unsigned slot;
	int found;

	u64 val;
	u32 address;
	u64 tom2;
	u64 base = FAM10H_PCI_MMCONF_BASE;

	int hi_mmio_num;
	struct range range[8];

	/* only try to get setting from BSP */
	if (fam10h_pci_mmconf_base)
		return;

	if (!early_pci_allowed())
		return;

	found = 0;
	for (i = 0; i < ARRAY_SIZE(pci_probes); i++) {
		u32 id;
		u16 device;
		u16 vendor;

		bus = pci_probes[i].bus;
		slot = pci_probes[i].slot;
		id = read_pci_config(bus, slot, 0, PCI_VENDOR_ID);

		vendor = id & 0xffff;
		device = (id>>16) & 0xffff;
		if (pci_probes[i].vendor == vendor &&
		    pci_probes[i].device == device) {
			found = 1;
			break;
		}
	}

	if (!found)
		return;

	/* SYS_CFG */
	address = MSR_K8_SYSCFG;
	rdmsrl(address, val);

	/* TOP_MEM2 is not enabled? */
	if (!(val & (1<<21))) {
		tom2 = 1ULL << 32;
	} else {
		/* TOP_MEM2 */
		address = MSR_K8_TOP_MEM2;
		rdmsrl(address, val);
		tom2 = max(val & 0xffffff800000ULL, 1ULL << 32);
	}

	if (base <= tom2)
		base = (tom2 + 2 * MMCONF_UNIT - 1) & MMCONF_MASK;

	/*
	 * need to check if the range is in the high mmio range that is
	 * above 4G
	 */
	hi_mmio_num = 0;
	for (i = 0; i < 8; i++) {
		u32 reg;
		u64 start;
		u64 end;
		reg = read_pci_config(bus, slot, 1, 0x80 + (i << 3));
		if (!(reg & 3))
			continue;

		start = (u64)(reg & 0xffffff00) << 8; /* 39:16 on 31:8*/
		reg = read_pci_config(bus, slot, 1, 0x84 + (i << 3));
		end = ((u64)(reg & 0xffffff00) << 8) | 0xffff; /* 39:16 on 31:8*/

		if (end < tom2)
			continue;

		range[hi_mmio_num].start = start;
		range[hi_mmio_num].end = end;
		hi_mmio_num++;
	}

	if (!hi_mmio_num)
		goto out;

	/* sort the range */
	sort(range, hi_mmio_num, sizeof(struct range), cmp_range, NULL);

	if (range[hi_mmio_num - 1].end < base)
		goto out;
	if (range[0].start > base + MMCONF_SIZE)
		goto out;

	/* need to find one window */
	base = (range[0].start & MMCONF_MASK) - MMCONF_UNIT;
	if ((base > tom2) && BASE_VALID(base))
		goto out;
	base = (range[hi_mmio_num - 1].end + MMCONF_UNIT) & MMCONF_MASK;
	if (BASE_VALID(base))
		goto out;
	/* need to find window between ranges */
	for (i = 1; i < hi_mmio_num; i++) {
		base = (range[i - 1].end + MMCONF_UNIT) & MMCONF_MASK;
		val = range[i].start & MMCONF_MASK;
		if (val >= base + MMCONF_SIZE && BASE_VALID(base))
			goto out;
	}
	return;

out:
	fam10h_pci_mmconf_base = base;
}