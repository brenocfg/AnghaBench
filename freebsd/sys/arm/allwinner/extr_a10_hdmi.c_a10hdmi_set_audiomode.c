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
typedef  int uint32_t ;
struct videomode {int /*<<< orphan*/  dot_clock; } ;
struct a10hdmi_softc {int /*<<< orphan*/  has_audio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AUD_CTRL_EN ; 
 int AUD_CTRL_RST ; 
 int AUD_FMT_CH (int /*<<< orphan*/ ) ; 
 int CH_STATUS0_FS_FREQ_48 ; 
 int CH_STATUS1_WORD_LEN_16 ; 
 int /*<<< orphan*/  HDMI_ADMA_CTRL ; 
 int HDMI_ADMA_MODE_DDMA ; 
 int HDMI_AUDIO_CHANNELMAP ; 
 int /*<<< orphan*/  HDMI_AUDIO_CHANNELS ; 
 int HDMI_AUDIO_CTS (int /*<<< orphan*/ ,int) ; 
 int HDMI_AUDIO_N ; 
 int HDMI_AUDIO_RESET_RETRY ; 
 int /*<<< orphan*/  HDMI_AUD_CH_STATUS0 ; 
 int /*<<< orphan*/  HDMI_AUD_CH_STATUS1 ; 
 int /*<<< orphan*/  HDMI_AUD_CTRL ; 
 int /*<<< orphan*/  HDMI_AUD_CTS ; 
 int /*<<< orphan*/  HDMI_AUD_FMT ; 
 int /*<<< orphan*/  HDMI_AUD_N ; 
 int /*<<< orphan*/  HDMI_PCM_CTRL ; 
 int HDMI_READ (struct a10hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (struct a10hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 struct a10hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
a10hdmi_set_audiomode(device_t dev, const struct videomode *mode)
{
	struct a10hdmi_softc *sc;
	uint32_t val;
	int retry;

	sc = device_get_softc(dev);

	/* Disable and reset audio module and wait for reset bit to clear */
	HDMI_WRITE(sc, HDMI_AUD_CTRL, AUD_CTRL_RST);
	for (retry = HDMI_AUDIO_RESET_RETRY; retry > 0; retry--) {
		val = HDMI_READ(sc, HDMI_AUD_CTRL);
		if ((val & AUD_CTRL_RST) == 0)
			break;
	}
	if (retry == 0) {
		device_printf(dev, "timeout waiting for audio module\n");
		return;
	}

	if (!sc->has_audio)
		return;

	/* DMA and FIFO control */
	HDMI_WRITE(sc, HDMI_ADMA_CTRL, HDMI_ADMA_MODE_DDMA);

	/* Audio format control (LPCM, S16LE, stereo) */
	HDMI_WRITE(sc, HDMI_AUD_FMT, AUD_FMT_CH(HDMI_AUDIO_CHANNELS));

	/* Channel mappings */
	HDMI_WRITE(sc, HDMI_PCM_CTRL, HDMI_AUDIO_CHANNELMAP);

	/* Clocks */
	HDMI_WRITE(sc, HDMI_AUD_CTS,
	    HDMI_AUDIO_CTS(mode->dot_clock, HDMI_AUDIO_N));
	HDMI_WRITE(sc, HDMI_AUD_N, HDMI_AUDIO_N);

	/* Set sampling frequency to 48 kHz, word length to 16-bit */
	HDMI_WRITE(sc, HDMI_AUD_CH_STATUS0, CH_STATUS0_FS_FREQ_48);
	HDMI_WRITE(sc, HDMI_AUD_CH_STATUS1, CH_STATUS1_WORD_LEN_16);

	/* Enable */
	HDMI_WRITE(sc, HDMI_AUD_CTRL, AUD_CTRL_EN);
}