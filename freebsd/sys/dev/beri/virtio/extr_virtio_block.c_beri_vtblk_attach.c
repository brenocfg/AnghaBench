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
struct virtio_blk_config {int dummy; } ;
struct beri_vtblk_softc {TYPE_1__* cdev; int /*<<< orphan*/  pio_recv; int /*<<< orphan*/  pio_send; int /*<<< orphan*/  beri_mem_offset; int /*<<< orphan*/  vtblk_ktd; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  cfg; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct beri_vtblk_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  beri_cdevsw ; 
 int /*<<< orphan*/  beri_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct beri_vtblk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int kthread_add (int /*<<< orphan*/ ,struct beri_vtblk_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setup_pio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_thread ; 

__attribute__((used)) static int
beri_vtblk_attach(device_t dev)
{
	struct beri_vtblk_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, beri_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	sc->cfg = malloc(sizeof(struct virtio_blk_config),
		M_DEVBUF, M_NOWAIT|M_ZERO);

	sx_init(&sc->sc_mtx, device_get_nameunit(sc->dev));

	error = kthread_add(vtblk_thread, sc, NULL, &sc->vtblk_ktd,
		0, 0, "beri_virtio_block");
	if (error) {
		device_printf(dev, "cannot create kthread\n");
		return (ENXIO);
	}

	if (setup_offset(dev, &sc->beri_mem_offset) != 0)
		return (ENXIO);
	if (setup_pio(dev, "pio-send", &sc->pio_send) != 0)
		return (ENXIO);
	if (setup_pio(dev, "pio-recv", &sc->pio_recv) != 0)
		return (ENXIO);

	sc->cdev = make_dev(&beri_cdevsw, 0, UID_ROOT, GID_WHEEL,
	    S_IRWXU, "beri_vtblk");
	if (sc->cdev == NULL) {
		device_printf(dev, "Failed to create character device.\n");
		return (ENXIO);
	}

	sc->cdev->si_drv1 = sc;
	return (0);
}