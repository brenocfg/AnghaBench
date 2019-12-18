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
typedef  int /*<<< orphan*/  uint32_t ;
struct dwc_hdmi_softc {int /*<<< orphan*/  sc_edid_info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dwc_hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edid_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hdmi_edid_read (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
dwc_hdmi_get_edid(device_t dev, uint8_t **edid, uint32_t *edid_len)
{
	struct dwc_hdmi_softc *sc;
	int error;

	sc = device_get_softc(dev);

	memset(&sc->sc_edid_info, 0, sizeof(sc->sc_edid_info));

	error = hdmi_edid_read(sc, 0, edid, edid_len);
	if (error != 0)
		return (error);

	edid_parse(*edid, &sc->sc_edid_info);

	return (0);
}