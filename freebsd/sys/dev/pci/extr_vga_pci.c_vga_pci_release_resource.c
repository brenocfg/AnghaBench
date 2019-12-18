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
struct vga_resource {int vr_refs; struct resource* vr_res; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int bus_release_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 struct vga_resource* lookup_res (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vga_pci_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct vga_resource *vr;
	int error;

	switch (type) {
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		/*
		 * For BARs, we release the resource from the PCI bus
		 * when the last child reference goes away.
		 */
		vr = lookup_res(device_get_softc(dev), rid);
		if (vr == NULL)
			return (EINVAL);
		if (vr->vr_res == NULL)
			return (EINVAL);
		KASSERT(vr->vr_res == r, ("vga_pci resource mismatch"));
		if (vr->vr_refs > 1) {
			vr->vr_refs--;
			return (0);
		}
		KASSERT(vr->vr_refs > 0,
		    ("vga_pci resource reference count underflow"));
		error = bus_release_resource(dev, type, rid, r);
		if (error == 0) {
			vr->vr_res = NULL;
			vr->vr_refs = 0;
		}
		return (error);
	}

	return (bus_release_resource(dev, type, rid, r));
}