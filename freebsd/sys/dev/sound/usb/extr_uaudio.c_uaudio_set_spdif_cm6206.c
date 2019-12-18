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
typedef  int uint8_t ;
struct uaudio_softc {int /*<<< orphan*/  sc_mixer_iface_index; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ENXIO ; 
 int UAUDIO_SPDIF_IN_MIX ; 
 int UAUDIO_SPDIF_OUT ; 
 int UAUDIO_SPDIF_OUT_96K ; 
 int /*<<< orphan*/  UHID_OUTPUT_REPORT ; 
 scalar_t__ usbd_req_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uaudio_set_spdif_cm6206(struct uaudio_softc *sc, int flags)
{
	uint8_t cmd[2][4] = {
		{0x20, 0x20, 0x00, 0},
		{0x20, 0x30, 0x02, 1}
	};
	int i;

	if (flags & UAUDIO_SPDIF_OUT)
		cmd[1][1] = 0x00;
	else
		cmd[1][1] = 0x02;

	if (flags & UAUDIO_SPDIF_OUT_96K)
		cmd[0][1] = 0x60;	/* 96K: 3'b110 */

	if (flags & UAUDIO_SPDIF_IN_MIX)
		cmd[1][1] = 0x03;	/* SPDIFMIX */

	for (i = 0; i < 2; i++) {
		if (usbd_req_set_report(sc->sc_udev, NULL,
		    cmd[i], sizeof(cmd[0]),
		    sc->sc_mixer_iface_index, UHID_OUTPUT_REPORT, 0) != 0) {
			return (ENXIO);
		}
	}
	return (0);
}