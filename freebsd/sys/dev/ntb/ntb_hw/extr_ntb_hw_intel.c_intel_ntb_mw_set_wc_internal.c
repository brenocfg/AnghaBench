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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ntb_softc {struct ntb_pci_bar_info* bar_info; } ;
struct ntb_pci_bar_info {int /*<<< orphan*/  map_mode; int /*<<< orphan*/  size; scalar_t__ vbase; } ;

/* Variables and functions */
 size_t intel_ntb_mw_to_bar (struct ntb_softc*,unsigned int) ; 
 int pmap_change_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_mw_set_wc_internal(struct ntb_softc *ntb, unsigned idx, vm_memattr_t mode)
{
	struct ntb_pci_bar_info *bar;
	int rc;

	bar = &ntb->bar_info[intel_ntb_mw_to_bar(ntb, idx)];
	if (bar->map_mode == mode)
		return (0);

	rc = pmap_change_attr((vm_offset_t)bar->vbase, bar->size, mode);
	if (rc == 0)
		bar->map_mode = mode;

	return (rc);
}