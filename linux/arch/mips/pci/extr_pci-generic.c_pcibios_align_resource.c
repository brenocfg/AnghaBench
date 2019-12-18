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
struct resource {int start; int flags; } ;
struct pci_host_bridge {int (* align_resource ) (struct pci_dev*,struct resource const*,int,int,int) ;} ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 struct pci_host_bridge* pci_find_host_bridge (int /*<<< orphan*/ ) ; 
 int stub1 (struct pci_dev*,struct resource const*,int,int,int) ; 

resource_size_t pcibios_align_resource(void *data, const struct resource *res,
				resource_size_t size, resource_size_t align)
{
	struct pci_dev *dev = data;
	resource_size_t start = res->start;
	struct pci_host_bridge *host_bridge;

	if (res->flags & IORESOURCE_IO && start & 0x300)
		start = (start + 0x3ff) & ~0x3ff;

	start = (start + align - 1) & ~(align - 1);

	host_bridge = pci_find_host_bridge(dev->bus);

	if (host_bridge->align_resource)
		return host_bridge->align_resource(dev, res,
				start, size, align);

	return start;
}