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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/ * PCI_CRP_AD_CBE ; 
 int /*<<< orphan*/ * PCI_CRP_RDATA ; 
 int /*<<< orphan*/  ixp4xx_pci_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void crp_read(u32 ad_cbe, u32 *data)
{
	unsigned long flags;
	raw_spin_lock_irqsave(&ixp4xx_pci_lock, flags);
	*PCI_CRP_AD_CBE = ad_cbe;
	*data = *PCI_CRP_RDATA;
	raw_spin_unlock_irqrestore(&ixp4xx_pci_lock, flags);
}