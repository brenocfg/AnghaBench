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
struct TYPE_2__ {int /*<<< orphan*/  xfer; } ;
struct uaudio_softc {TYPE_1__ sc_hid; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAUDIO_HID_N_TRANSFER ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uaudio_hid_detach(struct uaudio_softc *sc)
{
	usbd_transfer_unsetup(sc->sc_hid.xfer, UAUDIO_HID_N_TRANSFER);
}