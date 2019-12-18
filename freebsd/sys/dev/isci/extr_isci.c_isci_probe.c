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
typedef  scalar_t__ u_int32_t ;
struct _pcsid {scalar_t__ type; scalar_t__ desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 struct _pcsid* pci_ids ; 

__attribute__((used)) static int
isci_probe (device_t device)
{
	u_int32_t	type = pci_get_devid(device);
	struct _pcsid	*ep = pci_ids;

	while (ep->type && ep->type != type)
		++ep;

	if (ep->desc)
	{
		device_set_desc(device, ep->desc);
		return (BUS_PROBE_DEFAULT);
	}
	else
		return (ENXIO);
}