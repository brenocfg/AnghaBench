#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct panel_info {int clkval_f; int width; int height; scalar_t__ ivclk; scalar_t__ fixvclk; } ;
struct TYPE_2__ {int fb_width; int fb_height; int fb_stride; int fb_bpp; int fb_depth; int fb_size; intptr_t fb_vbase; intptr_t fb_pbase; int /*<<< orphan*/  fb_name; } ;
struct fimd_softc {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * sc_fbd; TYPE_1__ sc_info; void* bsh_sysreg; void* bst_sysreg; struct panel_info* panel; int /*<<< orphan*/ * res; void* bsh_disp; void* bst_disp; void* bsh; void* bst; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int FIMDBYPASS_DISP1 ; 
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (void*,void*,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (void*,void*,int,int) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct fimd_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimd_init (struct fimd_softc*) ; 
 int /*<<< orphan*/  fimd_spec ; 
 scalar_t__ get_panel_info (struct fimd_softc*,struct panel_info*) ; 
 scalar_t__ kmem_alloc_contig (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*,intptr_t,...) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 void* rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ vtophys (intptr_t) ; 

__attribute__((used)) static int
fimd_attach(device_t dev)
{
	struct panel_info panel;
	struct fimd_softc *sc;
	device_t gpio_dev;
	int reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, fimd_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);
	sc->bst_disp = rman_get_bustag(sc->res[1]);
	sc->bsh_disp = rman_get_bushandle(sc->res[1]);
	sc->bst_sysreg = rman_get_bustag(sc->res[2]);
	sc->bsh_sysreg = rman_get_bushandle(sc->res[2]);

	if (get_panel_info(sc, &panel)) {
		device_printf(dev, "Can't get panel info\n");
		return (ENXIO);
	}

	panel.fixvclk = 0;
	panel.ivclk = 0;
	panel.clkval_f = 2;

	sc->panel = &panel;

	/* Get the GPIO device, we need this to give power to USB */
	gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (gpio_dev == NULL) {
		/* TODO */
	}

	reg = bus_space_read_4(sc->bst_sysreg, sc->bsh_sysreg, 0x214);
	reg |= FIMDBYPASS_DISP1;
	bus_space_write_4(sc->bst_sysreg, sc->bsh_sysreg, 0x214, reg);

	sc->sc_info.fb_width = panel.width;
	sc->sc_info.fb_height = panel.height;
	sc->sc_info.fb_stride = sc->sc_info.fb_width * 2;
	sc->sc_info.fb_bpp = sc->sc_info.fb_depth = 16;
	sc->sc_info.fb_size = sc->sc_info.fb_height * sc->sc_info.fb_stride;
	sc->sc_info.fb_vbase = (intptr_t)kmem_alloc_contig(sc->sc_info.fb_size,
	    M_ZERO, 0, ~0, PAGE_SIZE, 0, VM_MEMATTR_UNCACHEABLE);
	sc->sc_info.fb_pbase = (intptr_t)vtophys(sc->sc_info.fb_vbase);

#if 0
	printf("%dx%d [%d]\n", sc->sc_info.fb_width, sc->sc_info.fb_height,
	    sc->sc_info.fb_stride);
	printf("pbase == 0x%08x\n", sc->sc_info.fb_pbase);
#endif

	memset((int8_t *)sc->sc_info.fb_vbase, 0x0, sc->sc_info.fb_size);

	fimd_init(sc);

	sc->sc_info.fb_name = device_get_nameunit(dev);

	/* Ask newbus to attach framebuffer device to me. */
	sc->sc_fbd = device_add_child(dev, "fbd", device_get_unit(dev));
	if (sc->sc_fbd == NULL)
		device_printf(dev, "Can't attach fbd device\n");

	if (device_probe_and_attach(sc->sc_fbd) != 0) {
		device_printf(sc->dev, "Failed to attach fbd device\n");
	}

	return (0);
}