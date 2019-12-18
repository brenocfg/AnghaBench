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
struct palmas_usb {int /*<<< orphan*/  id_irq; scalar_t__ enable_id_detection; int /*<<< orphan*/  vbus_irq; scalar_t__ enable_vbus_detection; int /*<<< orphan*/  palmas; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_USB_ID_CTRL_SET ; 
 int PALMAS_USB_ID_CTRL_SET_ID_ACT_COMP ; 
 int /*<<< orphan*/  PALMAS_USB_ID_INT_EN_HI_SET ; 
 int PALMAS_USB_ID_INT_EN_HI_SET_ID_FLOAT ; 
 int PALMAS_USB_ID_INT_EN_HI_SET_ID_GND ; 
 int /*<<< orphan*/  PALMAS_USB_OTG_BASE ; 
 int /*<<< orphan*/  PALMAS_USB_VBUS_CTRL_SET ; 
 int PALMAS_USB_VBUS_CTRL_SET_VBUS_ACT_COMP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  palmas_id_irq_handler (int /*<<< orphan*/ ,struct palmas_usb*) ; 
 int /*<<< orphan*/  palmas_vbus_irq_handler (int /*<<< orphan*/ ,struct palmas_usb*) ; 
 int /*<<< orphan*/  palmas_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void palmas_enable_irq(struct palmas_usb *palmas_usb)
{
	palmas_write(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
		PALMAS_USB_VBUS_CTRL_SET,
		PALMAS_USB_VBUS_CTRL_SET_VBUS_ACT_COMP);

	if (palmas_usb->enable_id_detection) {
		palmas_write(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			     PALMAS_USB_ID_CTRL_SET,
			     PALMAS_USB_ID_CTRL_SET_ID_ACT_COMP);

		palmas_write(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			     PALMAS_USB_ID_INT_EN_HI_SET,
			     PALMAS_USB_ID_INT_EN_HI_SET_ID_GND |
			     PALMAS_USB_ID_INT_EN_HI_SET_ID_FLOAT);
	}

	if (palmas_usb->enable_vbus_detection)
		palmas_vbus_irq_handler(palmas_usb->vbus_irq, palmas_usb);

	/* cold plug for host mode needs this delay */
	if (palmas_usb->enable_id_detection) {
		msleep(30);
		palmas_id_irq_handler(palmas_usb->id_irq, palmas_usb);
	}
}