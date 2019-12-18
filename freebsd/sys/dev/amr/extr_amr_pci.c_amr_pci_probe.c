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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  LSI_DESC_PCI ; 
 int /*<<< orphan*/ * amr_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amr_pci_probe(device_t dev)
{

    debug_called(1);

    if (amr_find_ident(dev) != NULL) {
	device_set_desc(dev, LSI_DESC_PCI);
	return(BUS_PROBE_DEFAULT);
    }
    return(ENXIO);
}