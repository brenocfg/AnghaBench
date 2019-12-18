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
struct drm_irq_busid {int busnum; scalar_t__ devnum; scalar_t__ funcnum; int /*<<< orphan*/  irq; } ;
struct drm_device {int pci_bus; scalar_t__ pci_slot; scalar_t__ pci_func; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int drm_get_pci_domain (struct drm_device*) ; 

__attribute__((used)) static int drm_pci_irq_by_busid(struct drm_device *dev, struct drm_irq_busid *p)
{
	if ((p->busnum >> 8) != drm_get_pci_domain(dev) ||
	    (p->busnum & 0xff) != dev->pci_bus ||
	    p->devnum != dev->pci_slot || p->funcnum != dev->pci_func)
		return -EINVAL;

	p->irq = dev->irq;

	DRM_DEBUG("%d:%d:%d => IRQ %d\n", p->busnum, p->devnum, p->funcnum,
		  p->irq);
	return 0;
}