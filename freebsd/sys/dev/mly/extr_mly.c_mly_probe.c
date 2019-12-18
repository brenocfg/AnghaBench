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
struct mly_ident {scalar_t__ vendor; scalar_t__ device; scalar_t__ subvendor; scalar_t__ subdevice; int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mly_ident* mly_identifiers ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_probe(device_t dev)
{
    struct mly_ident	*m;

    debug_called(1);

    for (m = mly_identifiers; m->vendor != 0; m++) {
	if ((m->vendor == pci_get_vendor(dev)) &&
	    (m->device == pci_get_device(dev)) &&
	    ((m->subvendor == 0) || ((m->subvendor == pci_get_subvendor(dev)) &&
				     (m->subdevice == pci_get_subdevice(dev))))) {
	    
	    device_set_desc(dev, m->desc);
	    return(BUS_PROBE_DEFAULT);	/* allow room to be overridden */
	}
    }
    return(ENXIO);
}