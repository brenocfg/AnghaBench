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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ BT_MBI_UNIT_GFX ; 
 int EPERM ; 
 int MBI_MASK_HI ; 
 int MBI_MASK_LO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iosf_mbi_form_mcr (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  iosf_mbi_lock ; 
 int iosf_mbi_pci_write_mdr (int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int iosf_mbi_write(u8 port, u8 opcode, u32 offset, u32 mdr)
{
	u32 mcr, mcrx;
	unsigned long flags;
	int ret;

	/* Access to the GFX unit is handled by GPU code */
	if (port == BT_MBI_UNIT_GFX) {
		WARN_ON(1);
		return -EPERM;
	}

	mcr = iosf_mbi_form_mcr(opcode, port, offset & MBI_MASK_LO);
	mcrx = offset & MBI_MASK_HI;

	spin_lock_irqsave(&iosf_mbi_lock, flags);
	ret = iosf_mbi_pci_write_mdr(mcrx, mcr, mdr);
	spin_unlock_irqrestore(&iosf_mbi_lock, flags);

	return ret;
}