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
struct vga_resource {int /*<<< orphan*/ * vr_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  PCIM_HDRTYPE_BRIDGE 129 
#define  PCIM_HDRTYPE_CARDBUS 128 
 int PCIR_BIOS ; 
 int PCIR_BIOS_1 ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VGA_PCI_BIOS_SHADOW_SIZE ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 struct vga_resource* lookup_res (int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rman_get_virtual (int /*<<< orphan*/ *) ; 
 scalar_t__ vga_pci_is_boot_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_pci_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
vga_pci_unmap_bios(device_t dev, void *bios)
{
	struct vga_resource *vr;
	int rid;

	if (bios == NULL) {
		return;
	}

#if defined(__amd64__) || defined(__i386__)
	if (vga_pci_is_boot_display(dev)) {
		/* We mapped the BIOS shadow copy located at 0xC0000. */
		pmap_unmapdev((vm_offset_t)bios, VGA_PCI_BIOS_SHADOW_SIZE);

		return;
	}
#endif
	switch(pci_read_config(dev, PCIR_HDRTYPE, 1)) {
	case PCIM_HDRTYPE_BRIDGE:
		rid = PCIR_BIOS_1;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		rid = 0;
		break;
	default:
		rid = PCIR_BIOS;
		break;
	}
	if (rid == 0)
		return;
	/*
	 * Look up the PCIR_BIOS resource in our softc.  It should match
	 * the address we returned previously.
	 */
	vr = lookup_res(device_get_softc(dev), rid);
	KASSERT(vr->vr_res != NULL, ("vga_pci_unmap_bios: bios not mapped"));
	KASSERT(rman_get_virtual(vr->vr_res) == bios,
	    ("vga_pci_unmap_bios: mismatch"));
	vga_pci_release_resource(dev, NULL, SYS_RES_MEMORY, rid,
	    vr->vr_res);
}