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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ bIfaceIndex; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct g_audio_softc {int sc_noise_rem; int** sc_data_len; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_mode; int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 int G_AUDIO_BUFSIZE ; 
 int G_AUDIO_FRAMES ; 
 size_t G_AUDIO_ISOC0_RD ; 
 size_t G_AUDIO_ISOC0_WR ; 
 size_t G_AUDIO_ISOC1_RD ; 
 size_t G_AUDIO_ISOC1_WR ; 
 int /*<<< orphan*/  G_AUDIO_MODE_SILENT ; 
 int /*<<< orphan*/  G_AUDIO_N_TRANSFER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct g_audio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_audio_config ; 
 int /*<<< orphan*/  g_audio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_audio_timeout_reset (struct g_audio_softc*) ; 
 int /*<<< orphan*/  g_audio_watchdog_reset (struct g_audio_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_set_alt_interface_index (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_audio_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_audio_attach(device_t dev)
{
	struct g_audio_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	int error;
	int i;
	uint8_t iface_index[3];

	DPRINTFN(11, "\n");

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "g_audio", NULL, MTX_DEF);

	usb_callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);
	usb_callout_init_mtx(&sc->sc_watchdog, &sc->sc_mtx, 0);

	sc->sc_mode = G_AUDIO_MODE_SILENT;

	sc->sc_noise_rem = 1;

	for (i = 0; i != G_AUDIO_FRAMES; i++) {
		sc->sc_data_len[0][i] = G_AUDIO_BUFSIZE / G_AUDIO_FRAMES;
		sc->sc_data_len[1][i] = G_AUDIO_BUFSIZE / G_AUDIO_FRAMES;
	}

	iface_index[0] = uaa->info.bIfaceIndex;
	iface_index[1] = uaa->info.bIfaceIndex + 1;
	iface_index[2] = uaa->info.bIfaceIndex + 2;

	error = usbd_set_alt_interface_index(uaa->device, iface_index[1], 1);
	if (error) {
		DPRINTF("alt iface setting error=%s\n", usbd_errstr(error));
		goto detach;
	}
	error = usbd_set_alt_interface_index(uaa->device, iface_index[2], 1);
	if (error) {
		DPRINTF("alt iface setting error=%s\n", usbd_errstr(error));
		goto detach;
	}
	error = usbd_transfer_setup(uaa->device,
	    iface_index, sc->sc_xfer, g_audio_config,
	    G_AUDIO_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		DPRINTF("error=%s\n", usbd_errstr(error));
		goto detach;
	}
	usbd_set_parent_iface(uaa->device, iface_index[1], iface_index[0]);
	usbd_set_parent_iface(uaa->device, iface_index[2], iface_index[0]);

	mtx_lock(&sc->sc_mtx);

	usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC0_RD]);
	usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC1_RD]);

	usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC0_WR]);
	usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC1_WR]);

	g_audio_timeout_reset(sc);

	g_audio_watchdog_reset(sc);

	mtx_unlock(&sc->sc_mtx);

	return (0);			/* success */

detach:
	g_audio_detach(dev);

	return (ENXIO);			/* error */
}