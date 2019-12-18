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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCIM_MSIXCTRL_MSIX_ENABLE ; 
 int PCIM_MSIXCTRL_TABLE_SIZE ; 
 int PCIM_MSIX_BIR_MASK ; 
 int PCIR_BAR (int) ; 
 scalar_t__ PCIR_MSIX_CTRL ; 
 scalar_t__ PCIR_MSIX_PBA ; 
 scalar_t__ PCIR_MSIX_TABLE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_msix(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint32_t pba_offset, table_offset, val;
	int msgnum, pba_bar, table_bar;
	uint16_t ctrl;

	ctrl = read_config(fd, &p->pc_sel, ptr + PCIR_MSIX_CTRL, 2);
	msgnum = (ctrl & PCIM_MSIXCTRL_TABLE_SIZE) + 1;

	val = read_config(fd, &p->pc_sel, ptr + PCIR_MSIX_TABLE, 4);
	table_bar = PCIR_BAR(val & PCIM_MSIX_BIR_MASK);
	table_offset = val & ~PCIM_MSIX_BIR_MASK;

	val = read_config(fd, &p->pc_sel, ptr + PCIR_MSIX_PBA, 4);
	pba_bar = PCIR_BAR(val & PCIM_MSIX_BIR_MASK);
	pba_offset = val & ~PCIM_MSIX_BIR_MASK;

	printf("MSI-X supports %d message%s%s\n", msgnum,
	    (msgnum == 1) ? "" : "s",
	    (ctrl & PCIM_MSIXCTRL_MSIX_ENABLE) ? ", enabled" : "");

	printf("                 ");
	printf("Table in map 0x%x[0x%x], PBA in map 0x%x[0x%x]",
	    table_bar, table_offset, pba_bar, pba_offset);
}