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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  fixc1_nforce2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixwsc_natoma (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fixup_pci_probe(device_t dev)
{
    switch (pci_get_devid(dev)) {
    case 0x12378086:		/* Intel 82440FX (Natoma) */
	fixwsc_natoma(dev);
	break;
    case 0x01e010de:		/* nVidia nForce2 */
	fixc1_nforce2(dev);
	break;
    }
    return(ENXIO);
}