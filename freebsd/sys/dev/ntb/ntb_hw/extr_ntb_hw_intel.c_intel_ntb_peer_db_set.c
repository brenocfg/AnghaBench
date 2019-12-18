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
typedef  int uint64_t ;
struct ntb_softc {TYPE_2__* peer_reg; TYPE_1__* peer_msix_data; struct ntb_pci_bar_info* peer_lapic_bar; } ;
struct ntb_pci_bar_info {int /*<<< orphan*/  pci_bus_handle; int /*<<< orphan*/  pci_bus_tag; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  db_bell; } ;
struct TYPE_3__ {int /*<<< orphan*/  nmd_data; int /*<<< orphan*/  nmd_ofs; } ;

/* Variables and functions */
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 int /*<<< orphan*/  NTB_SDOORBELL_LOCKUP ; 
 unsigned int XEON_NONLINK_DB_MSIX_BITS ; 
 int /*<<< orphan*/  XEON_PDOORBELL_OFFSET ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_iowrite (struct ntb_softc*,int /*<<< orphan*/ ,int) ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intel_ntb_db_vector_mask (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  intel_ntb_mw_write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
intel_ntb_peer_db_set(device_t dev, uint64_t bit)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)) {
		struct ntb_pci_bar_info *lapic;
		unsigned i;

		lapic = ntb->peer_lapic_bar;

		for (i = 0; i < XEON_NONLINK_DB_MSIX_BITS; i++) {
			if ((bit & intel_ntb_db_vector_mask(dev, i)) != 0)
				bus_space_write_4(lapic->pci_bus_tag,
				    lapic->pci_bus_handle,
				    ntb->peer_msix_data[i].nmd_ofs,
				    ntb->peer_msix_data[i].nmd_data);
		}
		return;
	}

	if (HAS_FEATURE(ntb, NTB_SDOORBELL_LOCKUP)) {
		intel_ntb_mw_write(2, XEON_PDOORBELL_OFFSET, bit);
		return;
	}

	db_iowrite(ntb, ntb->peer_reg->db_bell, bit);
}