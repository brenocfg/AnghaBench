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
struct wi_softc {int sc_reset; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct wi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  WI_CMD_INI ; 
 int WI_DELAY ; 
 int /*<<< orphan*/  WI_EVENT_ACK ; 
 int WI_INIT_TRIES ; 
 int /*<<< orphan*/  WI_INT_EN ; 
 int /*<<< orphan*/  WI_RID_TICK_TIME ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int wi_cmd (struct wi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_write_val (struct wi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wi_reset(struct wi_softc *sc)
{
#define WI_INIT_TRIES 3
	int i, error = 0;

	for (i = 0; i < WI_INIT_TRIES; i++) {
		error = wi_cmd(sc, WI_CMD_INI, 0, 0, 0);
		if (error == 0)
			break;
		DELAY(WI_DELAY * 1000);
	}
	sc->sc_reset = 1;
	if (i == WI_INIT_TRIES) {
		device_printf(sc->sc_dev, "reset failed\n");
		return error;
	}

	CSR_WRITE_2(sc, WI_INT_EN, 0);
	CSR_WRITE_2(sc, WI_EVENT_ACK, 0xFFFF);

	/* Calibrate timer. */
	wi_write_val(sc, WI_RID_TICK_TIME, 8);

	return 0;
#undef WI_INIT_TRIES
}