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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct pcicfg_msix {int msix_msgnum; int /*<<< orphan*/  msix_table_res; scalar_t__ msix_table_offset; } ;
struct TYPE_2__ {struct pcicfg_msix msix; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCIM_MSIX_VCTRL_MASK ; 
 scalar_t__ bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

void
pci_mask_msix(device_t dev, u_int index)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	struct pcicfg_msix *msix = &dinfo->cfg.msix;
	uint32_t offset, val;

	KASSERT(msix->msix_msgnum > index, ("bogus index"));
	offset = msix->msix_table_offset + index * 16 + 12;
	val = bus_read_4(msix->msix_table_res, offset);
	val |= PCIM_MSIX_VCTRL_MASK;

	/*
	 * Some devices (e.g. Samsung PM961) do not support reads of this
	 * register, so always write the new value.
	 */
	bus_write_4(msix->msix_table_res, offset, val);
}