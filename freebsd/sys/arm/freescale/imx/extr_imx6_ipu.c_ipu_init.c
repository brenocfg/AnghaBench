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
typedef  int uint32_t ;
struct TYPE_3__ {intptr_t fb_vbase; int fb_size; int fb_bpp; int fb_depth; int fb_stride; int fb_width; int fb_height; int /*<<< orphan*/  fb_pbase; int /*<<< orphan*/  fb_name; } ;
struct ipu_softc {int sc_fb_size; int /*<<< orphan*/  sc_dev; TYPE_2__* sc_mode; TYPE_1__ sc_fb_info; int /*<<< orphan*/  sc_fb_phys; scalar_t__ sc_fb_base; int /*<<< orphan*/  sc_dma_map; int /*<<< orphan*/  sc_dma_tag; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int hdisplay; int vdisplay; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DI_PORT ; 
 int DMA_CHANNEL ; 
 int ETIMEDOUT ; 
 int IPU_CONF ; 
 int IPU_CONF_DC_EN ; 
 int IPU_CONF_DI0_EN ; 
 int IPU_CONF_DI1_EN ; 
 int IPU_CONF_DMFC_EN ; 
 int IPU_CONF_DP_EN ; 
 int IPU_IDMAC_CH_EN_1 ; 
 int IPU_IDMAC_CH_EN_2 ; 
 int IPU_MEM_RST ; 
 int IPU_MEM_RST_ALL ; 
 int IPU_MEM_RST_START ; 
 int IPU_READ4 (struct ipu_softc*,int) ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int,int) ; 
 int MODE_BPP ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_config_timing (struct ipu_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_dc_enable (struct ipu_softc*) ; 
 int /*<<< orphan*/  ipu_dc_init (struct ipu_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_dc_reset_map (struct ipu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dc_setup_map (struct ipu_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ipu_di_enable (struct ipu_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ipu_dmamap_cb ; 
 int /*<<< orphan*/  ipu_init_buffer (struct ipu_softc*) ; 
 size_t round_page (int) ; 

__attribute__((used)) static int
ipu_init(struct ipu_softc *sc)
{
	uint32_t reg, off;
	int i, err;
	size_t dma_size;

	IPU_WRITE4(sc, IPU_CONF, DI_PORT ? IPU_CONF_DI1_EN : IPU_CONF_DI0_EN);

	IPU_WRITE4(sc, IPU_MEM_RST, IPU_MEM_RST_ALL);
	i = 1000;
	while (i-- > 0) {
		if (!(IPU_READ4(sc, IPU_MEM_RST) & IPU_MEM_RST_START))
			break;
		DELAY(1);
	}

	if (i <= 0) {
		err = ETIMEDOUT;
		device_printf(sc->sc_dev, "timeout while resetting memory\n");
		goto fail;
	}

	ipu_dc_reset_map(sc, 0);
	ipu_dc_setup_map(sc, 0, 0,  7, 0xff);
	ipu_dc_setup_map(sc, 0, 1, 15, 0xff);
	ipu_dc_setup_map(sc, 0, 2, 23, 0xff);

	dma_size = round_page(sc->sc_mode->hdisplay * sc->sc_mode->vdisplay * (MODE_BPP / 8));

	/*
	 * Now allocate framebuffer memory
	 */
	err = bus_dma_tag_create(
	    bus_get_dma_tag(sc->sc_dev),
	    4, 0,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    dma_size, 1,			/* maxsize, nsegments */
	    dma_size, 0,			/* maxsegsize, flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->sc_dma_tag);
	if (err)
		goto fail;

	err = bus_dmamem_alloc(sc->sc_dma_tag, (void **)&sc->sc_fb_base,
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &sc->sc_dma_map);

	if (err) {
		device_printf(sc->sc_dev, "cannot allocate framebuffer\n");
		goto fail;
	}

	err = bus_dmamap_load(sc->sc_dma_tag, sc->sc_dma_map, sc->sc_fb_base,
	    dma_size, ipu_dmamap_cb, &sc->sc_fb_phys, BUS_DMA_NOWAIT);

	if (err) {
		device_printf(sc->sc_dev, "cannot load DMA map\n");
		goto fail;
	}

	/* Calculate actual FB Size */
	sc->sc_fb_size = sc->sc_mode->hdisplay * sc->sc_mode->vdisplay * MODE_BPP / 8;

	ipu_dc_init(sc, DI_PORT);
	reg = IPU_READ4(sc, IPU_CONF);
	reg |= IPU_CONF_DMFC_EN | IPU_CONF_DC_EN | IPU_CONF_DP_EN;
	IPU_WRITE4(sc, IPU_CONF, reg);

	ipu_config_timing(sc, DI_PORT);
	ipu_init_buffer(sc);
	ipu_di_enable(sc, DI_PORT);

	/* Enable DMA channel */
	off = (DMA_CHANNEL > 31) ? IPU_IDMAC_CH_EN_2 : IPU_IDMAC_CH_EN_1;
	reg = IPU_READ4(sc, off);
	reg |= (1 << (DMA_CHANNEL & 0x1f));
	IPU_WRITE4(sc, off, reg);

	ipu_dc_enable(sc);

	sc->sc_fb_info.fb_name = device_get_nameunit(sc->sc_dev);
	sc->sc_fb_info.fb_vbase = (intptr_t)sc->sc_fb_base;
	sc->sc_fb_info.fb_pbase = sc->sc_fb_phys;
	sc->sc_fb_info.fb_size = sc->sc_fb_size;
	sc->sc_fb_info.fb_bpp = sc->sc_fb_info.fb_depth = MODE_BPP;
	sc->sc_fb_info.fb_stride = sc->sc_mode->hdisplay * MODE_BPP / 8;
	sc->sc_fb_info.fb_width = sc->sc_mode->hdisplay;
	sc->sc_fb_info.fb_height = sc->sc_mode->vdisplay;

	device_t fbd = device_add_child(sc->sc_dev, "fbd",
	    device_get_unit(sc->sc_dev));
	if (fbd == NULL) {
		device_printf(sc->sc_dev, "Failed to add fbd child\n");
		goto fail;
	}
	if (device_probe_and_attach(fbd) != 0) {
		device_printf(sc->sc_dev, "Failed to attach fbd device\n");
		goto fail;
	}

	return (0);
fail:

	return (err);
}