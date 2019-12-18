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
struct ntb_softc {scalar_t__ b2b_off; int /*<<< orphan*/  device; struct ntb_pci_bar_info* bar_info; } ;
struct ntb_pci_bar_info {int /*<<< orphan*/  ssz_off; int /*<<< orphan*/  psz_off; } ;
typedef  enum ntb_bar { ____Placeholder_ntb_bar } ntb_bar ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int NTB_B2B_BAR_3 ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
xeon_reset_sbar_size(struct ntb_softc *ntb, enum ntb_bar idx,
    enum ntb_bar regbar)
{
	struct ntb_pci_bar_info *bar;
	uint8_t bar_sz;

	if (!HAS_FEATURE(ntb, NTB_SPLIT_BAR) && idx >= NTB_B2B_BAR_3)
		return;

	bar = &ntb->bar_info[idx];
	bar_sz = pci_read_config(ntb->device, bar->psz_off, 1);
	if (idx == regbar) {
		if (ntb->b2b_off != 0)
			bar_sz--;
		else
			bar_sz = 0;
	}
	pci_write_config(ntb->device, bar->ssz_off, bar_sz, 1);
	bar_sz = pci_read_config(ntb->device, bar->ssz_off, 1);
	(void)bar_sz;
}