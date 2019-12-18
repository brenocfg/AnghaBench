#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cfi_disk_softc {int /*<<< orphan*/  iotask; int /*<<< orphan*/  tq; int /*<<< orphan*/  bioq; int /*<<< orphan*/  qlock; TYPE_3__* disk; TYPE_2__* parent; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {char* d_name; struct cfi_disk_softc* d_drv1; int /*<<< orphan*/  d_mediasize; int /*<<< orphan*/  d_stripesize; int /*<<< orphan*/  d_maxsize; int /*<<< orphan*/  d_sectorsize; int /*<<< orphan*/  d_getattr; int /*<<< orphan*/ * d_dump; int /*<<< orphan*/  d_ioctl; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; int /*<<< orphan*/  d_unit; } ;
struct TYPE_6__ {int sc_width; int sc_regions; TYPE_1__* sc_region; int /*<<< orphan*/  sc_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  r_blksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_DISK_MAXIOSIZE ; 
 int /*<<< orphan*/  CFI_DISK_SECSIZE ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_DISK ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfi_disk_softc*) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfi_disk_close ; 
 int /*<<< orphan*/  cfi_disk_getattr ; 
 int /*<<< orphan*/  cfi_disk_ioctl ; 
 int /*<<< orphan*/  cfi_disk_open ; 
 int /*<<< orphan*/  cfi_disk_strategy ; 
 int /*<<< orphan*/  cfi_io_proc ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_3__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
cfi_disk_attach(device_t dev)
{
	struct cfi_disk_softc *sc = device_get_softc(dev);

	sc->parent = device_get_softc(device_get_parent(dev));
	/* validate interface width; assumed by other code */
	if (sc->parent->sc_width != 1 &&
	    sc->parent->sc_width != 2 &&
	    sc->parent->sc_width != 4)
		return EINVAL;

	sc->disk = disk_alloc();
	if (sc->disk == NULL)
		return ENOMEM;
	sc->disk->d_name = "cfid";
	sc->disk->d_unit = device_get_unit(dev);
	sc->disk->d_open = cfi_disk_open;
	sc->disk->d_close = cfi_disk_close;
	sc->disk->d_strategy = cfi_disk_strategy;
	sc->disk->d_ioctl = cfi_disk_ioctl;
	sc->disk->d_dump = NULL;		/* NB: no dumps */
	sc->disk->d_getattr = cfi_disk_getattr;
	sc->disk->d_sectorsize = CFI_DISK_SECSIZE;
	sc->disk->d_mediasize = sc->parent->sc_size;
	sc->disk->d_maxsize = CFI_DISK_MAXIOSIZE;
	/* NB: use stripesize to hold the erase/region size */
	if (sc->parent->sc_regions) {
		/*
		 * Multiple regions, use the last one.  This is a
		 * total hack as it's (presently) used only by
		 * geom_redboot to locate the FIS directory which
		 * lies at the start of the last erase region.
		 */
		sc->disk->d_stripesize =
		    sc->parent->sc_region[sc->parent->sc_regions-1].r_blksz;
	} else
		sc->disk->d_stripesize = sc->disk->d_mediasize;
	sc->disk->d_drv1 = sc;
	disk_create(sc->disk, DISK_VERSION);

	mtx_init(&sc->qlock, "CFID I/O lock", NULL, MTX_DEF);
	bioq_init(&sc->bioq);

	sc->tq = taskqueue_create("cfid_taskq", M_NOWAIT,
		taskqueue_thread_enqueue, &sc->tq);
	taskqueue_start_threads(&sc->tq, 1, PI_DISK, "cfid taskq");

	TASK_INIT(&sc->iotask, 0, cfi_io_proc, sc);

	return 0;
}