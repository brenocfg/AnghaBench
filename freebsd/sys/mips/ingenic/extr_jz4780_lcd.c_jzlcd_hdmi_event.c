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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct videomode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct jzlcd_softc {int /*<<< orphan*/  dev; } ;
struct edid_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FB_DEFAULT_H ; 
 int /*<<< orphan*/  FB_DEFAULT_REF ; 
 int /*<<< orphan*/  FB_DEFAULT_W ; 
 int HDMI_GET_EDID (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  HDMI_SET_VIDEOMODE (int /*<<< orphan*/ ,struct videomode*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int edid_parse (int /*<<< orphan*/ *,struct edid_info*) ; 
 int /*<<< orphan*/  edid_print (struct edid_info*) ; 
 int jzlcd_configure (struct jzlcd_softc*,struct videomode const*) ; 
 struct videomode* jzlcd_find_mode (struct edid_info*) ; 
 int /*<<< orphan*/  jzlcd_start (struct jzlcd_softc*) ; 
 int /*<<< orphan*/  jzlcd_stop (struct jzlcd_softc*) ; 
 struct videomode* pick_mode_by_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jzlcd_hdmi_event(void *arg, device_t hdmi_dev)
{
	const struct videomode *mode;
	struct videomode hdmi_mode;
	struct jzlcd_softc *sc;
	struct edid_info ei;
	uint8_t *edid;
	uint32_t edid_len;
	int error;

	sc = arg;
	edid = NULL;
	edid_len = 0;
	mode = NULL;

	error = HDMI_GET_EDID(hdmi_dev, &edid, &edid_len);
	if (error != 0) {
		device_printf(sc->dev, "failed to get EDID: %d\n", error);
	} else {
		error = edid_parse(edid, &ei);
		if (error != 0) {
			device_printf(sc->dev, "failed to parse EDID: %d\n",
			    error);
		} else {
			if (bootverbose)
				edid_print(&ei);

			mode = jzlcd_find_mode(&ei);
		}
	}

	/* If a suitable mode could not be found, try the default */
	if (mode == NULL)
		mode = pick_mode_by_ref(FB_DEFAULT_W, FB_DEFAULT_H,
		    FB_DEFAULT_REF);

	if (mode == NULL) {
		device_printf(sc->dev, "failed to find usable video mode\n");
		return;
	}

	if (bootverbose)
		device_printf(sc->dev, "using %dx%d\n",
		    mode->hdisplay, mode->vdisplay);

	/* Stop the controller */
	jzlcd_stop(sc);

	/* Configure LCD controller */
	error = jzlcd_configure(sc, mode);
	if (error != 0) {
		device_printf(sc->dev, "failed to configure FB: %d\n", error);
		return;
	}

	/* Enable HDMI TX */
	hdmi_mode = *mode;
	HDMI_SET_VIDEOMODE(hdmi_dev, &hdmi_mode);

	/* Start the controller! */
	jzlcd_start(sc);
}