#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int fb_bpp; int fb_depth; int fb_width; int fb_stride; uintptr_t fb_vbase; int /*<<< orphan*/ * setblankmode; struct udl_softc* fb_priv; scalar_t__ fb_pbase; scalar_t__ fb_height; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_name; } ;
struct udl_softc {int sc_def_chip; int sc_chip; int sc_def_mode; int sc_cur_mode; int /*<<< orphan*/ * sc_fbdev; TYPE_2__ sc_fb_info; scalar_t__ sc_fb_addr; int /*<<< orphan*/  sc_fb_size; int /*<<< orphan*/  sc_cmd_buf_free; struct udl_cmd_buf* sc_cmd_buf_temp; int /*<<< orphan*/  sc_cmd_buf_pending; int /*<<< orphan*/ * sc_xfer_head; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_cv; } ;
struct udl_cmd_buf {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int DLMAX ; 
 int DLUNK ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 size_t UDL_BULK_WRITE_0 ; 
 size_t UDL_BULK_WRITE_1 ; 
 int UDL_CMD_MAX_BUFFERS ; 
 int /*<<< orphan*/  UDL_LOCK (struct udl_softc*) ; 
 int UDL_MAX_MODES ; 
 int /*<<< orphan*/  UDL_N_TRANSFER ; 
 int /*<<< orphan*/  UDL_UNLOCK (struct udl_softc*) ; 
 int USB_ERR_NORMAL_COMPLETION ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct udl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udl_callout (struct udl_softc*) ; 
 int /*<<< orphan*/  udl_config ; 
 int /*<<< orphan*/  udl_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udl_fb_setblankmode ; 
 int /*<<< orphan*/  udl_fbmem_alloc (struct udl_softc*) ; 
 scalar_t__ udl_get_fb_height (struct udl_softc*) ; 
 scalar_t__ udl_get_fb_hz (struct udl_softc*) ; 
 int udl_get_fb_width (struct udl_softc*) ; 
 int udl_init_chip (struct udl_softc*) ; 
 int /*<<< orphan*/  udl_init_resolution (struct udl_softc*) ; 
 TYPE_3__* udl_modes ; 
 int /*<<< orphan*/  udl_select_chip (struct udl_softc*,struct usb_attach_arg*) ; 
 int /*<<< orphan*/  udl_select_mode (struct udl_softc*) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udl_attach(device_t dev)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid *tree = device_get_sysctl_tree(dev);
	struct udl_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	int error;
	int i;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "UDL lock", NULL, MTX_DEF);
	cv_init(&sc->sc_cv, "UDLCV");
	callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);
	sc->sc_udev = uaa->device;

	error = usbd_transfer_setup(uaa->device, &uaa->info.bIfaceIndex,
	    sc->sc_xfer, udl_config, UDL_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		DPRINTF("usbd_transfer_setup error=%s\n", usbd_errstr(error));
		goto detach;
	}
	usbd_xfer_set_priv(sc->sc_xfer[UDL_BULK_WRITE_0], &sc->sc_xfer_head[0]);
	usbd_xfer_set_priv(sc->sc_xfer[UDL_BULK_WRITE_1], &sc->sc_xfer_head[1]);

	TAILQ_INIT(&sc->sc_xfer_head[0]);
	TAILQ_INIT(&sc->sc_xfer_head[1]);
	TAILQ_INIT(&sc->sc_cmd_buf_free);
	TAILQ_INIT(&sc->sc_cmd_buf_pending);

	sc->sc_def_chip = -1;
	sc->sc_chip = USB_GET_DRIVER_INFO(uaa);
	sc->sc_def_mode = -1;
	sc->sc_cur_mode = UDL_MAX_MODES;

	/* Allow chip ID to be overwritten */
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "chipid_force",
	    CTLFLAG_RWTUN, &sc->sc_def_chip, 0, "chip ID");

	/* Export current chip ID */
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "chipid",
	    CTLFLAG_RD, &sc->sc_chip, 0, "chip ID");

	if (sc->sc_def_chip > -1 && sc->sc_def_chip <= DLMAX) {
		device_printf(dev, "Forcing chip ID to 0x%04x\n", sc->sc_def_chip);
		sc->sc_chip = sc->sc_def_chip;
	}
	/*
	 * The product might have more than one chip
	 */
	if (sc->sc_chip == DLUNK)
		udl_select_chip(sc, uaa);

	for (i = 0; i != UDL_CMD_MAX_BUFFERS; i++) {
		struct udl_cmd_buf *cb = &sc->sc_cmd_buf_temp[i];

		TAILQ_INSERT_TAIL(&sc->sc_cmd_buf_free, cb, entry);
	}

	/*
	 * Initialize chip.
	 */
	error = udl_init_chip(sc);
	if (error != USB_ERR_NORMAL_COMPLETION)
		goto detach;

	/*
	 * Select edid mode.
	 */
	udl_select_mode(sc);

	/* Allow default mode to be overwritten */
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "mode_force",
	    CTLFLAG_RWTUN, &sc->sc_def_mode, 0, "mode");

	/* Export current mode */
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "mode",
	    CTLFLAG_RD, &sc->sc_cur_mode, 0, "mode");

	i = sc->sc_def_mode;
	if (i > -1 && i < UDL_MAX_MODES) {
		if (udl_modes[i].chip <= sc->sc_chip) {
			device_printf(dev, "Forcing mode to %d\n", i);
			sc->sc_cur_mode = i;
		}
	}
	/* Printout current mode */
	device_printf(dev, "Mode selected %dx%d @ %dHz\n",
	    (int)udl_get_fb_width(sc),
	    (int)udl_get_fb_height(sc),
	    (int)udl_get_fb_hz(sc));

	udl_init_resolution(sc);

	/* Allocate frame buffer */
	udl_fbmem_alloc(sc);

	UDL_LOCK(sc);
	udl_callout(sc);
	UDL_UNLOCK(sc);

	sc->sc_fb_info.fb_name = device_get_nameunit(dev);
	sc->sc_fb_info.fb_size = sc->sc_fb_size;
	sc->sc_fb_info.fb_bpp = 16;
	sc->sc_fb_info.fb_depth = 16;
	sc->sc_fb_info.fb_width = udl_get_fb_width(sc);
	sc->sc_fb_info.fb_height = udl_get_fb_height(sc);
	sc->sc_fb_info.fb_stride = sc->sc_fb_info.fb_width * 2;
	sc->sc_fb_info.fb_pbase = 0;
	sc->sc_fb_info.fb_vbase = (uintptr_t)sc->sc_fb_addr;
	sc->sc_fb_info.fb_priv = sc;
	sc->sc_fb_info.setblankmode = &udl_fb_setblankmode;

	sc->sc_fbdev = device_add_child(dev, "fbd", -1);
	if (sc->sc_fbdev == NULL)
		goto detach;
	if (device_probe_and_attach(sc->sc_fbdev) != 0)
		goto detach;

	return (0);

detach:
	udl_detach(dev);

	return (ENXIO);
}