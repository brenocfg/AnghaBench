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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ vm_memattr_t ;
struct amd_ntb_softc {TYPE_1__* hw_info; struct amd_ntb_pci_bar_info* bar_info; } ;
struct amd_ntb_pci_bar_info {scalar_t__ map_mode; int /*<<< orphan*/  size; scalar_t__ vbase; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {unsigned int mw_count; unsigned int bar_start_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pmap_change_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
amd_ntb_mw_set_wc(device_t dev, unsigned int mw_idx, vm_memattr_t mode)
{
	struct amd_ntb_softc *ntb = device_get_softc(dev);
	struct amd_ntb_pci_bar_info *bar_info;
	int rc;

	if (mw_idx < 0 || mw_idx >= ntb->hw_info->mw_count)
		return (EINVAL);

	bar_info = &ntb->bar_info[ntb->hw_info->bar_start_idx + mw_idx];
	if (mode == bar_info->map_mode)
		return (0);

	rc = pmap_change_attr((vm_offset_t)bar_info->vbase, bar_info->size, mode);
	if (rc == 0)
		bar_info->map_mode = mode;

	return (rc);
}