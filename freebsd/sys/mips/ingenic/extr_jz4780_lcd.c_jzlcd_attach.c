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
struct lcd_frame_descriptor {int dummy; } ;
struct jzlcd_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * clk_pix; int /*<<< orphan*/  fdesc_tag; int /*<<< orphan*/  fdesc_map; int /*<<< orphan*/  fdesc; int /*<<< orphan*/  hdmi_evh; int /*<<< orphan*/  fdesc_paddr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DMA_NOCACHE ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jzlcd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct jzlcd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdmi_event ; 
 int /*<<< orphan*/  jzlcd_dmamap_cb ; 
 int /*<<< orphan*/  jzlcd_hdmi_event ; 
 int /*<<< orphan*/  jzlcd_spec ; 

__attribute__((used)) static int
jzlcd_attach(device_t dev)
{
	struct jzlcd_softc *sc;
	int error;

	sc = device_get_softc(dev);

	sc->dev = dev;

	if (bus_alloc_resources(dev, jzlcd_spec, sc->res)) {
		device_printf(dev, "cannot allocate resources for device\n");
		goto failed;
	}

	if (clk_get_by_ofw_name(dev, 0, "lcd_clk", &sc->clk) != 0 ||
	    clk_get_by_ofw_name(dev, 0, "lcd_pixclk", &sc->clk_pix) != 0) {
		device_printf(dev, "cannot get clocks\n");
		goto failed;
	}
	if (clk_enable(sc->clk) != 0 || clk_enable(sc->clk_pix) != 0) {
		device_printf(dev, "cannot enable clocks\n");
		goto failed;
	}

	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),
	    sizeof(struct lcd_frame_descriptor), 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    sizeof(struct lcd_frame_descriptor) * 2, 1,
	    sizeof(struct lcd_frame_descriptor) * 2,
	    0,
	    NULL, NULL,
	    &sc->fdesc_tag);
	if (error != 0) {
		device_printf(dev, "cannot create bus dma tag\n");
		goto failed;
	}

	error = bus_dmamem_alloc(sc->fdesc_tag, (void **)&sc->fdesc,
	    BUS_DMA_NOCACHE | BUS_DMA_WAITOK | BUS_DMA_ZERO, &sc->fdesc_map);
	if (error != 0) {
		device_printf(dev, "cannot allocate dma descriptor\n");
		goto dmaalloc_failed;
	}

	error = bus_dmamap_load(sc->fdesc_tag, sc->fdesc_map, sc->fdesc,
	    sizeof(struct lcd_frame_descriptor) * 2, jzlcd_dmamap_cb,
	    &sc->fdesc_paddr, 0);
	if (error != 0) {
		device_printf(dev, "cannot load dma map\n");
		goto dmaload_failed;
	}

	sc->hdmi_evh = EVENTHANDLER_REGISTER(hdmi_event,
	    jzlcd_hdmi_event, sc, 0);

	return (0);

dmaload_failed:
	bus_dmamem_free(sc->fdesc_tag, sc->fdesc, sc->fdesc_map);
dmaalloc_failed:
	bus_dma_tag_destroy(sc->fdesc_tag);
failed:
	if (sc->clk_pix != NULL)
		clk_release(sc->clk);
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (sc->res != NULL)
		bus_release_resources(dev, jzlcd_spec, sc->res);

	return (ENXIO);
}