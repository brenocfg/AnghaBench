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
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CBBMEMBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_CBBMEMLIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_window (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_config (int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
print_cardbus_mem_window(int fd, struct pci_conf *p, int basereg, int limitreg,
    bool prefetch)
{

	print_window(basereg, prefetch ? "Prefetchable Memory" : "Memory", 32,
	    PCI_CBBMEMBASE(read_config(fd, &p->pc_sel, basereg, 4)),
	    PCI_CBBMEMLIMIT(read_config(fd, &p->pc_sel, limitreg, 4)));
}