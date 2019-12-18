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
typedef  scalar_t__ uint32_t ;
struct ntb_hw_info {scalar_t__ device_id; } ;

/* Variables and functions */
 size_t nitems (struct ntb_hw_info*) ; 
 struct ntb_hw_info* pci_ids ; 

__attribute__((used)) static struct ntb_hw_info *
intel_ntb_get_device_info(uint32_t device_id)
{
	struct ntb_hw_info *ep;

	for (ep = pci_ids; ep < &pci_ids[nitems(pci_ids)]; ep++) {
		if (ep->device_id == device_id)
			return (ep);
	}
	return (NULL);
}