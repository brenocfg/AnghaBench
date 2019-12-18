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
struct n25q_softc {int sc_sectorsize; int sc_flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_taskstate; int /*<<< orphan*/  sc_p; int /*<<< orphan*/  sc_bio_queue; TYPE_1__* sc_disk; } ;
struct n25q_flash_ident {int sectorsize; int sectorcount; int flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {char* d_name; int d_mediasize; int d_stripesize; int /*<<< orphan*/ * d_dump; int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_sectorsize; int /*<<< orphan*/  d_maxsize; struct n25q_softc* d_drv1; int /*<<< orphan*/  d_ioctl; int /*<<< orphan*/  d_getattr; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ENTER_4B_MODE ; 
 int /*<<< orphan*/  CMD_EXIT_4B_MODE ; 
 int /*<<< orphan*/  DFLTPHYS ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int ENXIO ; 
 int /*<<< orphan*/  FLASH_SECTORSIZE ; 
 int FL_DISABLE_4B_ADDR ; 
 int FL_ENABLE_4B_ADDR ; 
 int /*<<< orphan*/  N25Q_LOCK_INIT (struct n25q_softc*) ; 
 int /*<<< orphan*/  TSTATE_RUNNING ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 struct n25q_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ *,struct n25q_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  n25q_close ; 
 struct n25q_flash_ident* n25q_get_device_ident (struct n25q_softc*) ; 
 int /*<<< orphan*/  n25q_getattr ; 
 int /*<<< orphan*/  n25q_ioctl ; 
 int /*<<< orphan*/  n25q_open ; 
 int /*<<< orphan*/  n25q_set_4b_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n25q_strategy ; 
 int /*<<< orphan*/  n25q_task ; 
 int /*<<< orphan*/  n25q_wait_for_device_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
n25q_attach(device_t dev)
{
	struct n25q_flash_ident *ident;
	struct n25q_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	N25Q_LOCK_INIT(sc);

	ident = n25q_get_device_ident(sc);
	if (ident == NULL) {
		return (ENXIO);
	}

	n25q_wait_for_device_ready(sc->dev);

	sc->sc_disk = disk_alloc();
	sc->sc_disk->d_open = n25q_open;
	sc->sc_disk->d_close = n25q_close;
	sc->sc_disk->d_strategy = n25q_strategy;
	sc->sc_disk->d_getattr = n25q_getattr;
	sc->sc_disk->d_ioctl = n25q_ioctl;
	sc->sc_disk->d_name = "flash/qspi";
	sc->sc_disk->d_drv1 = sc;
	sc->sc_disk->d_maxsize = DFLTPHYS;
	sc->sc_disk->d_sectorsize = FLASH_SECTORSIZE;
	sc->sc_disk->d_mediasize = (ident->sectorsize * ident->sectorcount);
	sc->sc_disk->d_unit = device_get_unit(sc->dev);
	sc->sc_disk->d_dump = NULL;
	/* Sectorsize for erase operations */
	sc->sc_sectorsize =  ident->sectorsize;
	sc->sc_flags = ident->flags;

	if (sc->sc_flags & FL_ENABLE_4B_ADDR)
		n25q_set_4b_mode(dev, CMD_ENTER_4B_MODE);

	if (sc->sc_flags & FL_DISABLE_4B_ADDR)
		n25q_set_4b_mode(dev, CMD_EXIT_4B_MODE);

        /* NB: use stripesize to hold the erase/region size for RedBoot */
	sc->sc_disk->d_stripesize = ident->sectorsize;

	disk_create(sc->sc_disk, DISK_VERSION);
	bioq_init(&sc->sc_bio_queue);

	kproc_create(&n25q_task, sc, &sc->sc_p, 0, 0, "task: n25q flash");
	sc->sc_taskstate = TSTATE_RUNNING;

	device_printf(sc->dev, "%s, sector %d bytes, %d sectors\n", 
	    ident->name, ident->sectorsize, ident->sectorcount);

	return (0);
}