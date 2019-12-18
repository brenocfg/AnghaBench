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
typedef  int uint32_t ;
struct usb_bus {int dummy; } ;
struct saf1761_otg_softc {int dummy; } ;

/* Variables and functions */
 struct saf1761_otg_softc* SAF1761_OTG_BUS2SC (struct usb_bus*) ; 
#define  USB_HW_POWER_RESUME 130 
#define  USB_HW_POWER_SHUTDOWN 129 
#define  USB_HW_POWER_SUSPEND 128 
 int /*<<< orphan*/  saf1761_otg_resume (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_suspend (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_uninit (struct saf1761_otg_softc*) ; 

__attribute__((used)) static void
saf1761_otg_set_hw_power_sleep(struct usb_bus *bus, uint32_t state)
{
	struct saf1761_otg_softc *sc = SAF1761_OTG_BUS2SC(bus);

	switch (state) {
	case USB_HW_POWER_SUSPEND:
		saf1761_otg_suspend(sc);
		break;
	case USB_HW_POWER_SHUTDOWN:
		saf1761_otg_uninit(sc);
		break;
	case USB_HW_POWER_RESUME:
		saf1761_otg_resume(sc);
		break;
	default:
		break;
	}
}