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
struct ntb_hw_info {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_hw_info* intel_ntb_get_device_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_probe(device_t device)
{
	struct ntb_hw_info *p;

	p = intel_ntb_get_device_info(pci_get_devid(device));
	if (p == NULL)
		return (ENXIO);

	device_set_desc(device, p->desc);
	return (0);
}