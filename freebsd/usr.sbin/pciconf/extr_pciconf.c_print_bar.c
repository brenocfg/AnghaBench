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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;
struct pci_bar_io {int pbi_reg; int pbi_base; scalar_t__ pbi_enabled; scalar_t__ pbi_length; int /*<<< orphan*/  pbi_sel; } ;

/* Variables and functions */
 int PCIM_BAR_IO_BASE ; 
#define  PCIM_BAR_MEM_1MB 130 
#define  PCIM_BAR_MEM_32 129 
#define  PCIM_BAR_MEM_64 128 
 int PCIM_BAR_MEM_PREFETCH ; 
 int PCIM_BAR_MEM_TYPE ; 
 int /*<<< orphan*/  PCIOCGETBAR ; 
 scalar_t__ PCI_BAR_IO (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pci_bar_io*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

void
print_bar(int fd, struct pci_conf *p, const char *label, uint16_t bar_offset)
{
	uint64_t base;
	const char *type;
	struct pci_bar_io bar;
	int range;

	bar.pbi_sel = p->pc_sel;
	bar.pbi_reg = bar_offset;
	if (ioctl(fd, PCIOCGETBAR, &bar) < 0)
		return;
	if (PCI_BAR_IO(bar.pbi_base)) {
		type = "I/O Port";
		range = 32;
		base = bar.pbi_base & PCIM_BAR_IO_BASE;
	} else {
		if (bar.pbi_base & PCIM_BAR_MEM_PREFETCH)
			type = "Prefetchable Memory";
		else
			type = "Memory";
		switch (bar.pbi_base & PCIM_BAR_MEM_TYPE) {
		case PCIM_BAR_MEM_32:
			range = 32;
			break;
		case PCIM_BAR_MEM_1MB:
			range = 20;
			break;
		case PCIM_BAR_MEM_64:
			range = 64;
			break;
		default:
			range = -1;
		}
		base = bar.pbi_base & ~((uint64_t)0xf);
	}
	printf("    %s[%02x] = type %s, range %2d, base %#jx, ",
	    label, bar_offset, type, range, (uintmax_t)base);
	printf("size %ju, %s\n", (uintmax_t)bar.pbi_length,
	    bar.pbi_enabled ? "enabled" : "disabled");
}