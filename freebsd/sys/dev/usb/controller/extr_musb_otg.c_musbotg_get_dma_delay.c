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
struct usb_device {int /*<<< orphan*/  bus; } ;
struct musbotg_softc {scalar_t__ sc_mode; } ;

/* Variables and functions */
 scalar_t__ MUSB2_HOST_MODE ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
musbotg_get_dma_delay(struct usb_device *udev, uint32_t *pus)
{
	struct musbotg_softc *sc = MUSBOTG_BUS2SC(udev->bus);

	if (sc->sc_mode == MUSB2_HOST_MODE)
	        *pus = 2000;                   /* microseconds */
	else
		*pus = 0;
}