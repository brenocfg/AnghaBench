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

/* Variables and functions */
#define  ALCHEMY_CPU_AU1000 133 
#define  ALCHEMY_CPU_AU1100 132 
#define  ALCHEMY_CPU_AU1200 131 
#define  ALCHEMY_CPU_AU1300 130 
#define  ALCHEMY_CPU_AU1500 129 
#define  ALCHEMY_CPU_AU1550 128 
 int /*<<< orphan*/  AU1000_OHCICFG ; 
 int /*<<< orphan*/  AU1000_USB_OHCI_PHYS_ADDR ; 
 int /*<<< orphan*/  AU1550_OHCICFG ; 
 int /*<<< orphan*/  AU1550_USB_OHCI_PHYS_ADDR ; 
 int ENODEV ; 
 int alchemy_get_cputype () ; 
 int /*<<< orphan*/  alchemy_usb_lock ; 
 int au1000_usb_control (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int au1200_usb_control (int,int) ; 
 int au1300_usb_control (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int alchemy_usb_control(int block, int enable)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&alchemy_usb_lock, flags);
	switch (alchemy_get_cputype()) {
	case ALCHEMY_CPU_AU1000:
	case ALCHEMY_CPU_AU1500:
	case ALCHEMY_CPU_AU1100:
		ret = au1000_usb_control(block, enable,
			AU1000_USB_OHCI_PHYS_ADDR, AU1000_OHCICFG);
		break;
	case ALCHEMY_CPU_AU1550:
		ret = au1000_usb_control(block, enable,
			AU1550_USB_OHCI_PHYS_ADDR, AU1550_OHCICFG);
		break;
	case ALCHEMY_CPU_AU1200:
		ret = au1200_usb_control(block, enable);
		break;
	case ALCHEMY_CPU_AU1300:
		ret = au1300_usb_control(block, enable);
		break;
	default:
		ret = -ENODEV;
	}
	spin_unlock_irqrestore(&alchemy_usb_lock, flags);
	return ret;
}