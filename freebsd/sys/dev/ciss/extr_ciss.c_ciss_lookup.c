#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ subvendor; scalar_t__ subdevice; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 TYPE_1__* ciss_vendor_data ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_lookup(device_t dev)
{
    int 	i;

    for (i = 0; ciss_vendor_data[i].desc != NULL; i++)
	if ((pci_get_subvendor(dev) == ciss_vendor_data[i].subvendor) &&
	    (pci_get_subdevice(dev) == ciss_vendor_data[i].subdevice)) {
	    return(i);
	}
    return(-1);
}