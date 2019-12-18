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
typedef  scalar_t__ u_int32_t ;
struct cs4231_softc {int sc_flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APC_CSR ; 
 int APC_CSR_CODEC_RESET ; 
 int APC_CSR_RESET ; 
 int APC_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APC_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AUXIO_CODEC ; 
 scalar_t__ AUXIO_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUXIO_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int AUX_INPUT_MUTE ; 
 int CODEC_COLD_RESET ; 
 int CODEC_WARM_RESET ; 
 int /*<<< orphan*/  CS4231_IADDR ; 
 int CS4231_SBUS ; 
 int /*<<< orphan*/  CS4231_STATUS ; 
 int /*<<< orphan*/  CS_ALT_FEATURE1 ; 
 int /*<<< orphan*/  CS_ALT_FEATURE2 ; 
 int CS_DAC_ZERO ; 
 int CS_HPF_ENABLE ; 
 scalar_t__ CS_IN_INIT ; 
 int /*<<< orphan*/  CS_LEFT_AUX1_CONTROL ; 
 int /*<<< orphan*/  CS_LEFT_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  CS_MISC_INFO ; 
 int CS_MODE2 ; 
 int CS_OUTPUT_LVL ; 
 int /*<<< orphan*/  CS_PIN_CONTROL ; 
 scalar_t__ CS_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_RIGHT_AUX1_CONTROL ; 
 int /*<<< orphan*/  CS_RIGHT_OUTPUT_CONTROL ; 
 int CS_TIMEOUT ; 
 int /*<<< orphan*/  CS_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int INTERRUPT_ENABLE ; 
 int OUTPUT_MUTE ; 
 int /*<<< orphan*/  cs4231_ebdma_reset (struct cs4231_softc*) ; 
 int cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_write (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cs4231_power_reset(struct cs4231_softc *sc, int how)
{
	u_int32_t v;
	int i;

	if ((sc->sc_flags & CS4231_SBUS) != 0) {
		APC_WRITE(sc, APC_CSR, APC_CSR_RESET);
		DELAY(10);
		APC_WRITE(sc, APC_CSR, 0);
		DELAY(10);
		APC_WRITE(sc,
		    APC_CSR, APC_READ(sc, APC_CSR) | APC_CSR_CODEC_RESET);
		DELAY(20);
		APC_WRITE(sc,
		    APC_CSR, APC_READ(sc, APC_CSR) & (~APC_CSR_CODEC_RESET));
	} else {
		v = AUXIO_READ(sc, AUXIO_CODEC);
		if (how == CODEC_WARM_RESET && v != 0) {
			AUXIO_WRITE(sc, AUXIO_CODEC, 0);
			DELAY(20);
		} else if (how == CODEC_COLD_RESET){
			AUXIO_WRITE(sc, AUXIO_CODEC, 1);
			DELAY(20);
			AUXIO_WRITE(sc, AUXIO_CODEC, 0);
			DELAY(20);
		}
		cs4231_ebdma_reset(sc);
	}

	for (i = CS_TIMEOUT;
	    i && CS_READ(sc, CS4231_IADDR) == CS_IN_INIT; i--)
		DELAY(10);
	if (i == 0)
		device_printf(sc->sc_dev, "timeout waiting for reset\n");

	/* turn on cs4231 mode */
	cs4231_write(sc, CS_MISC_INFO,
	    cs4231_read(sc, CS_MISC_INFO) | CS_MODE2);
	/* enable interrupts & clear CSR */
        cs4231_write(sc, CS_PIN_CONTROL,
            cs4231_read(sc, CS_PIN_CONTROL) | INTERRUPT_ENABLE);
	CS_WRITE(sc, CS4231_STATUS, 0);
	/* enable DAC output */
	cs4231_write(sc, CS_LEFT_OUTPUT_CONTROL,
	    cs4231_read(sc, CS_LEFT_OUTPUT_CONTROL) & ~OUTPUT_MUTE);
	cs4231_write(sc, CS_RIGHT_OUTPUT_CONTROL,
	    cs4231_read(sc, CS_RIGHT_OUTPUT_CONTROL) & ~OUTPUT_MUTE);
	/* mute AUX1 since it generates noises */
	cs4231_write(sc, CS_LEFT_AUX1_CONTROL,
	    cs4231_read(sc, CS_LEFT_AUX1_CONTROL) | AUX_INPUT_MUTE);
	cs4231_write(sc, CS_RIGHT_AUX1_CONTROL,
	    cs4231_read(sc, CS_RIGHT_AUX1_CONTROL) | AUX_INPUT_MUTE);
	/* protect buffer underrun and set output level to 0dB */
	cs4231_write(sc, CS_ALT_FEATURE1,
	    cs4231_read(sc, CS_ALT_FEATURE1) | CS_DAC_ZERO | CS_OUTPUT_LVL);
	/* enable high pass filter, dual xtal was disabled due to noises */
	cs4231_write(sc, CS_ALT_FEATURE2,
	    cs4231_read(sc, CS_ALT_FEATURE2) | CS_HPF_ENABLE);
}