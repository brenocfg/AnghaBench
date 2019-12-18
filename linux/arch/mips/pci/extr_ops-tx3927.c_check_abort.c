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
struct TYPE_2__ {int pcistat; int pcistatim; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int /*<<< orphan*/  iob () ; 
 TYPE_1__* tx3927_pcicptr ; 

__attribute__((used)) static inline int check_abort(void)
{
	if (tx3927_pcicptr->pcistat & PCI_STATUS_REC_MASTER_ABORT) {
		tx3927_pcicptr->pcistat |= PCI_STATUS_REC_MASTER_ABORT;
		tx3927_pcicptr->pcistatim |= PCI_STATUS_REC_MASTER_ABORT;
		/* flush write buffer */
		iob();
		return PCIBIOS_DEVICE_NOT_FOUND;
	}
	return PCIBIOS_SUCCESSFUL;
}