#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct gpiobus_pin {int dummy; } ;
struct a10codec_info {int dmasize; int /*<<< orphan*/  lock; int /*<<< orphan*/  res; TYPE_1__* cfg; int /*<<< orphan*/  dmat; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;
struct TYPE_4__ {scalar_t__ ocd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  mixer_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_DAC_DPC (struct a10codec_info*) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int /*<<< orphan*/  CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC_DPC_EN_DA ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int SD_F_MPSAFE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  a10codec_chan_class ; 
 int /*<<< orphan*/  a10codec_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_pin_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gpiobus_pin**) ; 
 int gpio_pin_set_active (struct gpiobus_pin*,int) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct a10codec_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct a10codec_info*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct a10codec_info*) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct a10codec_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
a10codec_attach(device_t dev)
{
	struct a10codec_info *sc;
	char status[SND_STATUSLEN];
	struct gpiobus_pin *pa_pin;
	phandle_t node;
	clk_t clk_bus, clk_codec;
	hwreset_t rst;
	uint32_t val;
	int error;

	node = ofw_bus_get_node(dev);

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->cfg = (void *)ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	sc->dev = dev;
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "a10codec softc");

	if (bus_alloc_resources(dev, a10codec_spec, sc->res)) {
		device_printf(dev, "cannot allocate resources for device\n");
		error = ENXIO;
		goto fail;
	}

	sc->dmasize = 131072;
	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),
	    4, sc->dmasize,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    sc->dmasize, 1,		/* maxsize, nsegs */
	    sc->dmasize, 0,		/* maxsegsize, flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->dmat);
	if (error != 0) {
		device_printf(dev, "cannot create DMA tag\n");
		goto fail;
	}

	/* Get clocks */
	if (clk_get_by_ofw_name(dev, 0, "apb", &clk_bus) != 0 &&
	    clk_get_by_ofw_name(dev, 0, "ahb", &clk_bus) != 0) {
		device_printf(dev, "cannot find bus clock\n");
		goto fail;
	}
	if (clk_get_by_ofw_name(dev, 0, "codec", &clk_codec) != 0) {
		device_printf(dev, "cannot find codec clock\n");
		goto fail;
	}

	/* Gating bus clock for codec */
	if (clk_enable(clk_bus) != 0) {
		device_printf(dev, "cannot enable bus clock\n");
		goto fail;
	}
	/* Activate audio codec clock. According to the A10 and A20 user
	 * manuals, Audio_pll can be either 24.576MHz or 22.5792MHz. Most
	 * audio sampling rates require an 24.576MHz input clock with the
	 * exception of 44.1kHz, 22.05kHz, and 11.025kHz. Unfortunately,
	 * both capture and playback use the same clock source so to
	 * safely support independent full duplex operation, we use a fixed
	 * 24.576MHz clock source and don't advertise native support for
	 * the three sampling rates that require a 22.5792MHz input.
	 */
	error = clk_set_freq(clk_codec, 24576000, CLK_SET_ROUND_DOWN);
	if (error != 0) {
		device_printf(dev, "cannot set codec clock frequency\n");
		goto fail;
	}
	/* Enable audio codec clock */
	error = clk_enable(clk_codec);
	if (error != 0) {
		device_printf(dev, "cannot enable codec clock\n");
		goto fail;
	}

	/* De-assert hwreset */
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &rst) == 0) {
		error = hwreset_deassert(rst);
		if (error != 0) {
			device_printf(dev, "cannot de-assert reset\n");
			goto fail;
		}
	}

	/* Enable DAC */
	val = CODEC_READ(sc, AC_DAC_DPC(sc));
	val |= DAC_DPC_EN_DA;
	CODEC_WRITE(sc, AC_DAC_DPC(sc), val);

	if (mixer_init(dev, sc->cfg->mixer_class, sc)) {
		device_printf(dev, "mixer_init failed\n");
		goto fail;
	}

	/* Unmute PA */
	if (gpio_pin_get_by_ofw_property(dev, node, "allwinner,pa-gpios",
	    &pa_pin) == 0) {
		error = gpio_pin_set_active(pa_pin, 1);
		if (error != 0)
			device_printf(dev, "failed to unmute PA\n");
	}

	pcm_setflags(dev, pcm_getflags(dev) | SD_F_MPSAFE);

	if (pcm_register(dev, sc, 1, 1)) {
		device_printf(dev, "pcm_register failed\n");
		goto fail;
	}

	pcm_addchan(dev, PCMDIR_PLAY, &a10codec_chan_class, sc);
	pcm_addchan(dev, PCMDIR_REC, &a10codec_chan_class, sc);

	snprintf(status, SND_STATUSLEN, "at %s", ofw_bus_get_name(dev));
	pcm_setstatus(dev, status);

	return (0);

fail:
	bus_release_resources(dev, a10codec_spec, sc->res);
	snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);

	return (ENXIO);
}