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
struct panel_info {int width; int height; int /*<<< orphan*/  backlight_pin; } ;
struct TYPE_2__ {int fb_width; int fb_height; int fb_stride; int fb_bpp; int fb_depth; int fb_size; intptr_t fb_vbase; intptr_t fb_pbase; int /*<<< orphan*/  fb_name; } ;
struct dcu_softc {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * sc_fbd; TYPE_1__ sc_info; struct panel_info* panel; int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dcu_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ contigmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcu_init (struct dcu_softc*) ; 
 int /*<<< orphan*/  dcu_intr ; 
 int /*<<< orphan*/  dcu_spec ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct dcu_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ get_panel_info (struct dcu_softc*,struct panel_info*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*,intptr_t,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcon_bypass () ; 
 scalar_t__ vtophys (intptr_t) ; 

__attribute__((used)) static int
dcu_attach(device_t dev)
{
	struct panel_info panel;
	struct dcu_softc *sc;
	device_t gpio_dev;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, dcu_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	/* Setup interrupt handler */
	err = bus_setup_intr(dev, sc->res[1], INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, dcu_intr, sc, &sc->ih);
	if (err) {
		device_printf(dev, "Unable to alloc interrupt resource.\n");
		return (ENXIO);
	}

	if (get_panel_info(sc, &panel)) {
		device_printf(dev, "Can't get panel info\n");
		return (ENXIO);
	}

	sc->panel = &panel;

	/* Bypass timing control (used for raw lcd panels) */
	tcon_bypass();

	/* Get the GPIO device, we need this to give power to USB */
	gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (gpio_dev == NULL) {
		device_printf(sc->dev, "Error: failed to get the GPIO dev\n");
		return (1);
	}

	/* Turn on backlight */
	/* TODO: Use FlexTimer/PWM */
	GPIO_PIN_SETFLAGS(gpio_dev, panel.backlight_pin, GPIO_PIN_OUTPUT);
	GPIO_PIN_SET(gpio_dev, panel.backlight_pin, GPIO_PIN_HIGH);

	sc->sc_info.fb_width = panel.width;
	sc->sc_info.fb_height = panel.height;
	sc->sc_info.fb_stride = sc->sc_info.fb_width * 3;
	sc->sc_info.fb_bpp = sc->sc_info.fb_depth = 24;
	sc->sc_info.fb_size = sc->sc_info.fb_height * sc->sc_info.fb_stride;
	sc->sc_info.fb_vbase = (intptr_t)contigmalloc(sc->sc_info.fb_size,
	    M_DEVBUF, M_ZERO, 0, ~0, PAGE_SIZE, 0);
	sc->sc_info.fb_pbase = (intptr_t)vtophys(sc->sc_info.fb_vbase);

#if 0
	printf("%dx%d [%d]\n", sc->sc_info.fb_width, sc->sc_info.fb_height,
	    sc->sc_info.fb_stride);
	printf("pbase == 0x%08x\n", sc->sc_info.fb_pbase);
#endif

	memset((int8_t *)sc->sc_info.fb_vbase, 0x0, sc->sc_info.fb_size);

	dcu_init(sc);

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