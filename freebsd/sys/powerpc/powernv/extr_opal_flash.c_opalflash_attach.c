#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct opalflash_softc {int sc_erase; int /*<<< orphan*/  sc_p; int /*<<< orphan*/  sc_bio_queue; TYPE_1__* sc_disk; int /*<<< orphan*/  sc_dev; void* sc_opal_id; } ;
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  opal_id ;
typedef  int /*<<< orphan*/  flash_blocksize ;
typedef  int /*<<< orphan*/  device_t ;
typedef  void* cell_t ;
struct TYPE_3__ {char* d_name; int /*<<< orphan*/ * d_dump; void* d_stripesize; int /*<<< orphan*/  d_sectorsize; int /*<<< orphan*/  d_unit; void* d_mediasize; int /*<<< orphan*/  d_maxsize; struct opalflash_softc* d_drv1; int /*<<< orphan*/  d_getattr; int /*<<< orphan*/  d_ioctl; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLTPHYS ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int ENXIO ; 
 int /*<<< orphan*/  FLASH_BLOCKSIZE ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,void**,int) ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OPALFLASH_LOCK_INIT (struct opalflash_softc*) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 struct opalflash_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ *,struct opalflash_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opalflash_close ; 
 int /*<<< orphan*/  opalflash_getattr ; 
 int /*<<< orphan*/  opalflash_ioctl ; 
 int /*<<< orphan*/  opalflash_open ; 
 int /*<<< orphan*/  opalflash_strategy ; 
 int /*<<< orphan*/  opalflash_task ; 

__attribute__((used)) static int
opalflash_attach(device_t dev)
{
	struct opalflash_softc *sc;
	phandle_t node;
	cell_t flash_blocksize, opal_id;
	uint32_t regs[2];

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	node = ofw_bus_get_node(dev);
	OF_getencprop(node, "ibm,opal-id", &opal_id, sizeof(opal_id));
	sc->sc_opal_id = opal_id;

	if (OF_getencprop(node, "ibm,flash-block-size",
	    &flash_blocksize, sizeof(flash_blocksize)) < 0) {
		device_printf(dev, "Cannot determine flash block size.\n");
		return (ENXIO);
	}

	if (!OF_hasprop(node, "no-erase"))
		sc->sc_erase = true;

	OPALFLASH_LOCK_INIT(sc);

	if (OF_getencprop(node, "reg", regs, sizeof(regs)) < 0) {
		device_printf(dev, "Unable to get flash size.\n");
		return (ENXIO);
	}

	sc->sc_disk = disk_alloc();
	sc->sc_disk->d_name = "opalflash";
	sc->sc_disk->d_open = opalflash_open;
	sc->sc_disk->d_close = opalflash_close;
	sc->sc_disk->d_strategy = opalflash_strategy;
	sc->sc_disk->d_ioctl = opalflash_ioctl;
	sc->sc_disk->d_getattr = opalflash_getattr;
	sc->sc_disk->d_drv1 = sc;
	sc->sc_disk->d_maxsize = DFLTPHYS;
	sc->sc_disk->d_mediasize = regs[1];
	sc->sc_disk->d_unit = device_get_unit(sc->sc_dev);
	sc->sc_disk->d_sectorsize = FLASH_BLOCKSIZE;
	    sc->sc_disk->d_stripesize = flash_blocksize;
	sc->sc_disk->d_dump = NULL;

	disk_create(sc->sc_disk, DISK_VERSION);
	bioq_init(&sc->sc_bio_queue);

	kproc_create(&opalflash_task, sc, &sc->sc_p, 0, 0, "task: OPAL Flash");

	return (0);
}