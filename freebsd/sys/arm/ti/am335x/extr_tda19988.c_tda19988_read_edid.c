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
struct tda19988_softc {scalar_t__ sc_version; int* sc_edid; int sc_edid_len; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_EVENT_CONNECTED ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ TDA19988 ; 
 int /*<<< orphan*/  TDA_TX4 ; 
 int /*<<< orphan*/  TX4_PD_RAM ; 
 int /*<<< orphan*/  hdmi_event ; 
 int* realloc (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tda19988_read_edid_block (struct tda19988_softc*,int*,int) ; 
 int /*<<< orphan*/  tda19988_reg_clear (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_reg_set (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tda19988_read_edid(struct tda19988_softc *sc)
{
	int err;
	int blocks, i;
	uint8_t *buf;

	err = 0;
	if (sc->sc_version == TDA19988)
		tda19988_reg_clear(sc, TDA_TX4, TX4_PD_RAM);

	err = tda19988_read_edid_block(sc, sc->sc_edid, 0);
	if (err)
		goto done;

	blocks = sc->sc_edid[0x7e];
	if (blocks > 0) {
		sc->sc_edid = realloc(sc->sc_edid, 
		    EDID_LENGTH*(blocks+1), M_DEVBUF, M_WAITOK);
		sc->sc_edid_len = EDID_LENGTH*(blocks+1);
		for (i = 0; i < blocks; i++) {
			/* TODO: check validity */
			buf = sc->sc_edid + EDID_LENGTH*(i+1);
			err = tda19988_read_edid_block(sc, buf, i);
			if (err)
				goto done;
		}
	}

	EVENTHANDLER_INVOKE(hdmi_event, sc->sc_dev, HDMI_EVENT_CONNECTED);
done:
	if (sc->sc_version == TDA19988)
		tda19988_reg_set(sc, TDA_TX4, TX4_PD_RAM);

	return (err);
}