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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct hdmi_softc {int /*<<< orphan*/  audio_src_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  audio_freq; int /*<<< orphan*/  clk_hdmi; int /*<<< orphan*/  hdmi_mode; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int ACR_ENABLE ; 
 int ACR_SUBPACK_CTS (int) ; 
 int ACR_SUBPACK_N (int) ; 
 int AUDIO_N_GENERATE_ALTERNATE ; 
 int AUDIO_N_RESETF ; 
 int AUDIO_N_VALUE (int) ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_AUDIO_N ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_CTRL ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_SPARE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_CNTRL0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_SPARE0 ; 
 int RD4 (struct hdmi_softc*,int /*<<< orphan*/ ) ; 
 int SOR_AUDIO_CNTRL0_INJECT_NULLSMPL ; 
 int SOR_AUDIO_CNTRL0_SOURCE_SELECT (int /*<<< orphan*/ ) ; 
 int SOR_AUDIO_SPARE0_HBR_ENABLE ; 
 int SPARE_CTS_RESET_VAL (int) ; 
 int SPARE_FORCE_SW_CTS ; 
 int SPARE_HW_CTS ; 
 int /*<<< orphan*/  WR4 (struct hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audio_setup_infoframe (struct hdmi_softc*) ; 
 int clk_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int get_audio_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_hda_cts_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 

__attribute__((used)) static int
audio_setup(struct hdmi_softc *sc)
{
	uint32_t val;
	uint32_t audio_n;
	uint32_t audio_cts;
	uint32_t audio_aval;
	uint64_t hdmi_freq;
	bus_size_t aval_reg;
	int rv;

	if (!sc->hdmi_mode)
		return (ENOTSUP);
	rv  = get_audio_regs(sc->audio_freq, NULL, NULL, &aval_reg);
	if (rv != 0) {
		device_printf(sc->dev, "Unsupported audio frequency.\n");
		return (rv);
	}

	rv = clk_get_freq(sc->clk_hdmi, &hdmi_freq);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get hdmi frequency: %d\n", rv);
		return (rv);
	}

	rv = get_hda_cts_n(sc->audio_freq, hdmi_freq, &audio_cts, &audio_n,
	    &audio_aval);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot compute audio coefs: %d\n", rv);
		return (rv);
	}

	/* Audio infoframe. */
	audio_setup_infoframe(sc);
	/* Setup audio source */
	WR4(sc, HDMI_NV_PDISP_SOR_AUDIO_CNTRL0,
	    SOR_AUDIO_CNTRL0_SOURCE_SELECT(sc->audio_src_type) |
	    SOR_AUDIO_CNTRL0_INJECT_NULLSMPL);

	val = RD4(sc, HDMI_NV_PDISP_SOR_AUDIO_SPARE0);
	val |= SOR_AUDIO_SPARE0_HBR_ENABLE;
	WR4(sc, HDMI_NV_PDISP_SOR_AUDIO_SPARE0, val);

	WR4(sc, HDMI_NV_PDISP_HDMI_ACR_CTRL, 0);

	WR4(sc, HDMI_NV_PDISP_AUDIO_N,
	    AUDIO_N_RESETF |
	    AUDIO_N_GENERATE_ALTERNATE |
	    AUDIO_N_VALUE(audio_n - 1));

	WR4(sc, HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH,
	    ACR_SUBPACK_N(audio_n) | ACR_ENABLE);

	WR4(sc, HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW,
	    ACR_SUBPACK_CTS(audio_cts));

	WR4(sc, HDMI_NV_PDISP_HDMI_SPARE,
	    SPARE_HW_CTS | SPARE_FORCE_SW_CTS | SPARE_CTS_RESET_VAL(1));

	val = RD4(sc, HDMI_NV_PDISP_AUDIO_N);
	val &= ~AUDIO_N_RESETF;
	WR4(sc, HDMI_NV_PDISP_AUDIO_N, val);

	WR4(sc, aval_reg, audio_aval);

	return (0);
}