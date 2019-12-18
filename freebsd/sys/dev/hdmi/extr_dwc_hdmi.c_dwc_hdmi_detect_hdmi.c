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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int edid_ext_block_count; } ;
struct dwc_hdmi_softc {int sc_has_audio; int /*<<< orphan*/  sc_dev; TYPE_1__ sc_edid_info; } ;

/* Variables and functions */
 size_t CEA_DTD ; 
 int DTD_BASIC_AUDIO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dwc_hdmi_detect_hdmi_vsdb (int*) ; 
 scalar_t__ hdmi_edid_read (struct dwc_hdmi_softc*,int,int**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dwc_hdmi_detect_hdmi(struct dwc_hdmi_softc *sc)
{
	uint8_t *edid;
	uint32_t edid_len;
	int block;

	sc->sc_has_audio = 0;

	/* Scan through extension blocks, looking for a CEA-861 block */
	for (block = 1; block <= sc->sc_edid_info.edid_ext_block_count;
	    block++) {
		if (hdmi_edid_read(sc, block, &edid, &edid_len) != 0)
			return;
		if (dwc_hdmi_detect_hdmi_vsdb(edid) != 0) {
			if (bootverbose)
				device_printf(sc->sc_dev,
				    "enabling audio support\n");
			sc->sc_has_audio =
			    (edid[CEA_DTD] & DTD_BASIC_AUDIO) != 0;
			return;
		}
	}
}