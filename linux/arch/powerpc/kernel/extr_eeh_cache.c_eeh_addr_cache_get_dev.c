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
struct eeh_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  piar_lock; } ;

/* Variables and functions */
 struct eeh_dev* __eeh_addr_cache_get_device (unsigned long) ; 
 TYPE_1__ pci_io_addr_cache_root ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct eeh_dev *eeh_addr_cache_get_dev(unsigned long addr)
{
	struct eeh_dev *edev;
	unsigned long flags;

	spin_lock_irqsave(&pci_io_addr_cache_root.piar_lock, flags);
	edev = __eeh_addr_cache_get_device(addr);
	spin_unlock_irqrestore(&pci_io_addr_cache_root.piar_lock, flags);
	return edev;
}