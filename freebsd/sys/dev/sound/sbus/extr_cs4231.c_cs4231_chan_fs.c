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
typedef  int u_int8_t ;
struct cs4231_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int AUTO_CAL_ENABLE ; 
 int AUTO_CAL_IN_PROG ; 
 int /*<<< orphan*/  CODEC_COLD_RESET ; 
 int /*<<< orphan*/  CS4231_IADDR ; 
 int /*<<< orphan*/  CS4231_IDATA ; 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_LOCK_ASSERT (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int CS_CLOCK_DATA_FORMAT ; 
 int CS_INTERFACE_CONFIG ; 
 int CS_IN_INIT ; 
 int CS_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int CS_REC_FORMAT ; 
 int CS_TEST_AND_INIT ; 
 int CS_TIMEOUT ; 
 int /*<<< orphan*/  CS_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MODE_CHANGE_ENABLE ; 
 int PCMDIR_REC ; 
 int /*<<< orphan*/  cs4231_disable (struct cs4231_softc*) ; 
 int /*<<< orphan*/  cs4231_enable (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int cs4231_read (struct cs4231_softc*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mixer_reinit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cs4231_chan_fs(struct cs4231_softc *sc, int dir, u_int8_t fs)
{
	int i, doreset;
#ifdef CS4231_AUTO_CALIBRATION
	u_int8_t v;
#endif

	CS4231_LOCK_ASSERT(sc);

	/* set autocalibration */
	doreset = 0;
#ifdef CS4231_AUTO_CALIBRATION
	v = cs4231_read(sc, CS_INTERFACE_CONFIG) | AUTO_CAL_ENABLE;
	CS_WRITE(sc, CS4231_IADDR, MODE_CHANGE_ENABLE);
	CS_WRITE(sc, CS4231_IADDR, MODE_CHANGE_ENABLE | CS_INTERFACE_CONFIG);
	CS_WRITE(sc, CS4231_IDATA, v);
#endif

	/*
	 * We always need to write CS_CLOCK_DATA_FORMAT register since
	 * the clock frequency is shared with playback/capture.
	 */
	CS_WRITE(sc, CS4231_IADDR, MODE_CHANGE_ENABLE | CS_CLOCK_DATA_FORMAT);
	CS_WRITE(sc, CS4231_IDATA, fs);
	CS_READ(sc, CS4231_IDATA);
	CS_READ(sc, CS4231_IDATA);
	for (i = CS_TIMEOUT;
	    i && CS_READ(sc, CS4231_IADDR) == CS_IN_INIT; i--)
		DELAY(10);
	if (i == 0) {
		device_printf(sc->sc_dev, "timeout setting playback speed\n");
		doreset++;
	}

	/*
	 * capture channel
	 * cs4231 doesn't allow separate fs setup for playback/capture.
	 * I believe this will break full-duplex operation.
	 */
	if (dir == PCMDIR_REC) {
		CS_WRITE(sc, CS4231_IADDR, MODE_CHANGE_ENABLE | CS_REC_FORMAT);
		CS_WRITE(sc, CS4231_IDATA, fs);
		CS_READ(sc, CS4231_IDATA);
		CS_READ(sc, CS4231_IDATA);
		for (i = CS_TIMEOUT;
		    i && CS_READ(sc, CS4231_IADDR) == CS_IN_INIT; i--)
			DELAY(10);
		if (i == 0) {
			device_printf(sc->sc_dev,
			    "timeout setting capture format\n");
			doreset++;
		}
	}

	CS_WRITE(sc, CS4231_IADDR, 0);
	for (i = CS_TIMEOUT;
	    i && CS_READ(sc, CS4231_IADDR) == CS_IN_INIT; i--)
		DELAY(10);
	if (i == 0) {
		device_printf(sc->sc_dev, "timeout waiting for !MCE\n");
		doreset++;
	}

#ifdef CS4231_AUTO_CALIBRATION
	CS_WRITE(sc, CS4231_IADDR, CS_TEST_AND_INIT);
	for (i = CS_TIMEOUT;
	    i && CS_READ(sc, CS4231_IDATA) & AUTO_CAL_IN_PROG; i--)
		DELAY(10);
	if (i == 0) {
		device_printf(sc->sc_dev,
		    "timeout waiting for autocalibration\n");
		doreset++;
	}
#endif
	if (doreset) {
		/*
		 * Maybe the last resort to avoid a dreadful message like
		 * "pcm0:play:0: play interrupt timeout, channel dead" would
		 * be hardware reset.
		 */
		device_printf(sc->sc_dev, "trying to hardware reset\n");
		cs4231_disable(sc);
		cs4231_enable(sc, CODEC_COLD_RESET);
		CS4231_UNLOCK(sc); /* XXX */
		if (mixer_reinit(sc->sc_dev) != 0) 
			device_printf(sc->sc_dev,
			    "unable to reinitialize the mixer\n");
		CS4231_LOCK(sc);
	}
}