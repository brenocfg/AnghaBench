#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; int flags; } ;
struct pci_dev {struct pci_controller* sysdata; } ;
struct pci_controller {TYPE_2__* mem_resource; TYPE_1__* io_resource; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {int start; } ;
struct TYPE_3__ {int start; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int PCIBIOS_MIN_IO ; 
 int PCIBIOS_MIN_MEM ; 

resource_size_t
pcibios_align_resource(void *data, const struct resource *res,
		       resource_size_t size, resource_size_t align)
{
	struct pci_dev *dev = data;
	struct pci_controller *hose = dev->sysdata;
	resource_size_t start = res->start;

	if (res->flags & IORESOURCE_IO) {
		/* Make sure we start at our min on all hoses */
		if (start < PCIBIOS_MIN_IO + hose->io_resource->start)
			start = PCIBIOS_MIN_IO + hose->io_resource->start;

		/*
		 * Put everything into 0x00-0xff region modulo 0x400
		 */
		if (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	} else if (res->flags & IORESOURCE_MEM) {
		/* Make sure we start at our min on all hoses */
		if (start < PCIBIOS_MIN_MEM + hose->mem_resource->start)
			start = PCIBIOS_MIN_MEM + hose->mem_resource->start;
	}

	return start;
}