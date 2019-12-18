#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_controller_count ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* get_supported_device_id ) (int,TYPE_1__*) ;struct TYPE_8__* next; } ;
struct TYPE_7__ {scalar_t__ vid; scalar_t__ did; } ;
typedef  TYPE_1__ PCI_ID ;
typedef  TYPE_2__ HIM ;

/* Variables and functions */
 TYPE_2__* him_list ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HIM *hpt_match(device_t dev, int scan)
{
	PCI_ID pci_id;
	HIM *him;
	int i;

	for (him = him_list; him; him = him->next) {
		for (i=0; him->get_supported_device_id(i, &pci_id); i++) {
			if (scan && him->get_controller_count)
				him->get_controller_count(&pci_id,0,0);
			if ((pci_get_vendor(dev) == pci_id.vid) &&
				(pci_get_device(dev) == pci_id.did)){
				return (him);
			}
		}
	}
	return (NULL);
}