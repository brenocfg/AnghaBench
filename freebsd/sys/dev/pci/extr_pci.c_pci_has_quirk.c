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
struct pci_quirk {scalar_t__ devid; int type; } ;

/* Variables and functions */
 struct pci_quirk* pci_quirks ; 

__attribute__((used)) static int
pci_has_quirk(uint32_t devid, int quirk)
{
	const struct pci_quirk *q;

	for (q = &pci_quirks[0]; q->devid; q++) {
		if (q->devid == devid && q->type == quirk)
			return (1);
	}
	return (0);
}