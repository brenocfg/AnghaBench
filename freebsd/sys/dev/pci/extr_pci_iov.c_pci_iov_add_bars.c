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
typedef  scalar_t__ uint64_t ;
struct pcicfg_iov {struct pci_iov_bar* iov_bar; } ;
struct pci_iov_bar {int bar_size; int /*<<< orphan*/  bar_shift; int /*<<< orphan*/ * res; } ;
struct TYPE_3__ {int index; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ vf; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int PCIR_MAX_BAR_0 ; 
 int /*<<< orphan*/  pci_add_bar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_iov_add_bars(struct pcicfg_iov *iov, struct pci_devinfo *dinfo)
{
	struct pci_iov_bar *bar;
	uint64_t bar_start;
	int i;

	for (i = 0; i <= PCIR_MAX_BAR_0; i++) {
		bar = &iov->iov_bar[i];
		if (bar->res != NULL) {
			bar_start = rman_get_start(bar->res) +
			    dinfo->cfg.vf.index * bar->bar_size;

			pci_add_bar(dinfo->cfg.dev, PCIR_BAR(i), bar_start,
			    bar->bar_shift);
		}
	}
}