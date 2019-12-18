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
struct videomode {int dummy; } ;
struct dwc_hdmi_softc {int /*<<< orphan*/  sc_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dwc_hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_detect_hdmi (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_set_mode (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct videomode const*,int) ; 

int
dwc_hdmi_set_videomode(device_t dev, const struct videomode *mode)
{
	struct dwc_hdmi_softc *sc;

	sc = device_get_softc(dev);
	memcpy(&sc->sc_mode, mode, sizeof(*mode));

	dwc_hdmi_detect_hdmi(sc);

	dwc_hdmi_set_mode(sc);

	return (0);
}