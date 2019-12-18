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
struct codec_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  clk; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AICR_DAC ; 
 int AICR_DAC_SB ; 
 int AUDIOIF_I2S ; 
 int AUDIOIF_M ; 
 int /*<<< orphan*/  CR_DAC ; 
 int /*<<< orphan*/  CR_HP ; 
 int /*<<< orphan*/  CR_VIC ; 
 int DAC_ADWL_16 ; 
 int DAC_ADWL_M ; 
 int DAC_MUTE ; 
 int DAC_SB ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  FCR_DAC ; 
 int FCR_DAC_48 ; 
 int HP_MUTE ; 
 int HP_SB ; 
 int VIC_SB ; 
 int VIC_SB_SLEEP ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci20_hp_unmute (struct codec_softc*) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int codec_read (struct codec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codec_spec ; 
 int /*<<< orphan*/  codec_write (struct codec_softc*,int /*<<< orphan*/ ,int) ; 
 struct codec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
codec_attach(device_t dev)
{
	struct codec_softc *sc;
	uint8_t reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, codec_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	if (clk_get_by_ofw_name(dev, 0, "i2s", &sc->clk) != 0) {
		device_printf(dev, "could not get i2s clock\n");
		bus_release_resources(dev, codec_spec, sc->res);
		return (ENXIO);
	}

	/* Initialize codec. */
	reg = codec_read(sc, CR_VIC);
	reg &= ~(VIC_SB_SLEEP | VIC_SB);
	codec_write(sc, CR_VIC, reg);

	DELAY(20000);

	reg = codec_read(sc, CR_DAC);
	reg &= ~(DAC_SB | DAC_MUTE);
	codec_write(sc, CR_DAC, reg);

	DELAY(10000);

	/* I2S, 16-bit, 48 kHz. */
	reg = codec_read(sc, AICR_DAC);
	reg &= ~(AICR_DAC_SB | DAC_ADWL_M);
	reg |= DAC_ADWL_16;
	reg &= ~(AUDIOIF_M);
	reg |= AUDIOIF_I2S;
	codec_write(sc, AICR_DAC, reg);

	DELAY(10000);

	reg = FCR_DAC_48;
	codec_write(sc, FCR_DAC, reg);

	DELAY(10000);

	/* Unmute headphones. */
	reg = codec_read(sc, CR_HP);
	reg &= ~(HP_SB | HP_MUTE);
	codec_write(sc, CR_HP, reg);

	ci20_hp_unmute(sc);

	return (0);
}