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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ uint64_t ;
struct ntb_softc {scalar_t__ b2b_mw_idx; TYPE_2__* reg; struct ntb_pci_bar_info* bar_info; TYPE_1__* peer_reg; } ;
struct ntb_pci_bar_info {scalar_t__ pci_bus_tag; scalar_t__ pci_bus_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  db_size; } ;
struct TYPE_3__ {scalar_t__ db_bell; } ;

/* Variables and functions */
 scalar_t__ B2B_MW_DISABLED ; 
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t NTB_CONFIG_BAR ; 
 int /*<<< orphan*/  NTB_SDOORBELL_LOCKUP ; 
 scalar_t__ X86_BUS_SPACE_IO ; 
 scalar_t__ XEON_PDOORBELL_OFFSET ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t intel_ntb_mw_to_bar (struct ntb_softc*,scalar_t__) ; 

__attribute__((used)) static int
intel_ntb_peer_db_addr(device_t dev, bus_addr_t *db_addr, vm_size_t *db_size)
{
	struct ntb_softc *ntb = device_get_softc(dev);
	struct ntb_pci_bar_info *bar;
	uint64_t regoff;

	KASSERT((db_addr != NULL && db_size != NULL), ("must be non-NULL"));

	if (!HAS_FEATURE(ntb, NTB_SDOORBELL_LOCKUP)) {
		bar = &ntb->bar_info[NTB_CONFIG_BAR];
		regoff = ntb->peer_reg->db_bell;
	} else {
		KASSERT(ntb->b2b_mw_idx != B2B_MW_DISABLED,
		    ("invalid b2b idx"));

		bar = &ntb->bar_info[intel_ntb_mw_to_bar(ntb, ntb->b2b_mw_idx)];
		regoff = XEON_PDOORBELL_OFFSET;
	}
	KASSERT(bar->pci_bus_tag != X86_BUS_SPACE_IO, ("uh oh"));

	/* HACK: Specific to current x86 bus implementation. */
	*db_addr = ((uint64_t)bar->pci_bus_handle + regoff);
	*db_size = ntb->reg->db_size;
	return (0);
}