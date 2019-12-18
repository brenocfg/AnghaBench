#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pvi_vendor_id; scalar_t__ pvi_device_id; scalar_t__ pvi_subvendor_id; scalar_t__ pvi_subdevice_id; scalar_t__ pvi_rev_id; int /*<<< orphan*/  pvi_name; } ;
typedef  TYPE_1__ pci_vendor_info_t ;
typedef  TYPE_2__* if_shared_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {scalar_t__ isc_magic; TYPE_1__* isc_vendor_info; int /*<<< orphan*/  (* isc_parse_devinfo ) (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 TYPE_2__* DEVICE_REGISTER (int /*<<< orphan*/ ) ; 
 int ENOTSUP ; 
 int ENXIO ; 
 scalar_t__ IFLIB_MAGIC ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

int
iflib_device_probe(device_t dev)
{
	const pci_vendor_info_t *ent;
	if_shared_ctx_t sctx;
	uint16_t pci_device_id, pci_rev_id, pci_subdevice_id, pci_subvendor_id;
	uint16_t pci_vendor_id;

	if ((sctx = DEVICE_REGISTER(dev)) == NULL || sctx->isc_magic != IFLIB_MAGIC)
		return (ENOTSUP);

	pci_vendor_id = pci_get_vendor(dev);
	pci_device_id = pci_get_device(dev);
	pci_subvendor_id = pci_get_subvendor(dev);
	pci_subdevice_id = pci_get_subdevice(dev);
	pci_rev_id = pci_get_revid(dev);
	if (sctx->isc_parse_devinfo != NULL)
		sctx->isc_parse_devinfo(&pci_device_id, &pci_subvendor_id, &pci_subdevice_id, &pci_rev_id);

	ent = sctx->isc_vendor_info;
	while (ent->pvi_vendor_id != 0) {
		if (pci_vendor_id != ent->pvi_vendor_id) {
			ent++;
			continue;
		}
		if ((pci_device_id == ent->pvi_device_id) &&
		    ((pci_subvendor_id == ent->pvi_subvendor_id) ||
		     (ent->pvi_subvendor_id == 0)) &&
		    ((pci_subdevice_id == ent->pvi_subdevice_id) ||
		     (ent->pvi_subdevice_id == 0)) &&
		    ((pci_rev_id == ent->pvi_rev_id) ||
		     (ent->pvi_rev_id == 0))) {

			device_set_desc_copy(dev, ent->pvi_name);
			/* this needs to be changed to zero if the bus probing code
			 * ever stops re-probing on best match because the sctx
			 * may have its values over written by register calls
			 * in subsequent probes
			 */
			return (BUS_PROBE_DEFAULT);
		}
		ent++;
	}
	return (ENXIO);
}