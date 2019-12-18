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
struct ata_pci_controller {struct ata_intel_data* chipset_data; } ;
struct ata_intel_data {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ATAPCI ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ata_intel_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ata_intel_chipdeinit(device_t dev)
{
	struct ata_pci_controller *ctlr = device_get_softc(dev);
	struct ata_intel_data *data;

	data = ctlr->chipset_data;
	mtx_destroy(&data->lock);
	free(data, M_ATAPCI);
	ctlr->chipset_data = NULL;
	return (0);
}