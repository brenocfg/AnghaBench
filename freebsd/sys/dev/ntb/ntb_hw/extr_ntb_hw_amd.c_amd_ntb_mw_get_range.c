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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct amd_ntb_softc {TYPE_1__* hw_info; struct amd_ntb_pci_bar_info* bar_info; } ;
struct amd_ntb_pci_bar_info {size_t size; int /*<<< orphan*/  vbase; int /*<<< orphan*/  pbase; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {unsigned int mw_count; unsigned int bar_start_idx; int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int EINVAL ; 
 int QUIRK_MW0_32BIT ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amd_ntb_mw_get_range(device_t dev, unsigned mw_idx, vm_paddr_t *base,
    caddr_t *vbase, size_t *size, size_t *align, size_t *align_size,
    bus_addr_t *plimit)
{
	struct amd_ntb_softc *ntb = device_get_softc(dev);
	struct amd_ntb_pci_bar_info *bar_info;

	if (mw_idx < 0 || mw_idx >= ntb->hw_info->mw_count)
		return (EINVAL);

	bar_info = &ntb->bar_info[ntb->hw_info->bar_start_idx + mw_idx];

	if (base != NULL)
		*base = bar_info->pbase;

	if (vbase != NULL)
		*vbase = bar_info->vbase;

	if (align != NULL)
		*align = bar_info->size;

	if (size != NULL)
		*size = bar_info->size;

	if (align_size != NULL)
		*align_size = 1;

	if (plimit != NULL) {
		/*
		 * For Device ID 0x145B (which has 3 memory windows),
		 * memory window 0 use a 32-bit bar. The remaining
		 * cases all use 64-bit bar.
		 */
		if ((mw_idx == 0) && (ntb->hw_info->quirks & QUIRK_MW0_32BIT))
			*plimit = BUS_SPACE_MAXADDR_32BIT;
		else
			*plimit = BUS_SPACE_MAXADDR;
	}

	return (0);
}