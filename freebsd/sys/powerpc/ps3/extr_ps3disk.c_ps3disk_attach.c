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
typedef  int /*<<< orphan*/  uint64_t ;
struct ps3disk_softc {int sc_blksize; int sc_nregs; int sc_running; struct ps3disk_region* sc_reg; int /*<<< orphan*/  sc_irq; scalar_t__ sc_irqid; int /*<<< orphan*/  sc_irqctx; int /*<<< orphan*/  sc_task; int /*<<< orphan*/  sc_deferredq; int /*<<< orphan*/  sc_bioq; struct disk** sc_disk; int /*<<< orphan*/  sc_dmatag; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_nblocks; int /*<<< orphan*/  sc_dev; } ;
struct ps3disk_region {int r_size; int /*<<< orphan*/  r_flags; } ;
struct disk {char* d_name; int d_sectorsize; int d_unit; int d_mediasize; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_maxsize; struct ps3disk_softc* d_drv1; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; } ;
typedef  int intmax_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DISKFLAG_CANFLUSHCACHE ; 
 int /*<<< orphan*/  DISK_VERSION ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int LV1_DENIED_BY_POLICY ; 
 int /*<<< orphan*/  M_PS3DISK ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PS3DISK_LOCK_DESTROY (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  PS3DISK_LOCK_INIT (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ps3disk_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 struct ps3disk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct disk* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (struct disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ps3disk_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ *,struct ps3disk_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int lv1_storage_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct disk** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps3bus_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3disk_close ; 
 int ps3disk_enum_regions (struct ps3disk_softc*) ; 
 int ps3disk_get_disk_geometry (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  ps3disk_intr ; 
 int /*<<< orphan*/  ps3disk_open ; 
 int /*<<< orphan*/  ps3disk_strategy ; 
 int /*<<< orphan*/  ps3disk_sysctlattach (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  ps3disk_task ; 

__attribute__((used)) static int
ps3disk_attach(device_t dev)
{
	struct ps3disk_softc *sc;
	struct disk *d;
	intmax_t mb;
	uint64_t junk;
	char unit;
	int i, err;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	PS3DISK_LOCK_INIT(sc);

	err = ps3disk_get_disk_geometry(sc);
	if (err) {
		device_printf(dev, "Could not get disk geometry\n");
		err = ENXIO;
		goto fail_destroy_lock;
	}

	device_printf(dev, "block size %lu total blocks %lu\n",
	    sc->sc_blksize, sc->sc_nblocks);

	err = ps3disk_enum_regions(sc);
	if (err) {
		device_printf(dev, "Could not enumerate disk regions\n");
		err = ENXIO;
		goto fail_destroy_lock;
	}

	device_printf(dev, "Found %lu regions\n", sc->sc_nregs);

	if (!sc->sc_nregs) {
		err = ENXIO;
		goto fail_destroy_lock;
	}

	/* Setup interrupt handler */
	sc->sc_irqid = 0;
	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irqid,
	    RF_ACTIVE);
	if (!sc->sc_irq) {
		device_printf(dev, "Could not allocate IRQ\n");
		err = ENXIO;
		goto fail_free_regions;
	}

	err = bus_setup_intr(dev, sc->sc_irq,
	    INTR_TYPE_BIO | INTR_MPSAFE | INTR_ENTROPY,
	    NULL, ps3disk_intr, sc, &sc->sc_irqctx);
	if (err) {
		device_printf(dev, "Could not setup IRQ\n");
		err = ENXIO;
		goto fail_release_intr;
	}

	/* Setup DMA */
	err = bus_dma_tag_create(bus_get_dma_tag(dev), 4096, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    BUS_SPACE_UNRESTRICTED, 1, PAGE_SIZE, 0,
	    busdma_lock_mutex, &sc->sc_mtx, &sc->sc_dmatag);
	if (err) {
		device_printf(dev, "Could not create DMA tag\n");
		err = ENXIO;
		goto fail_teardown_intr;
	}

	/* Setup disks */

	sc->sc_disk = malloc(sc->sc_nregs * sizeof(struct disk *),
	    M_PS3DISK, M_ZERO | M_WAITOK);
	if (!sc->sc_disk) {
		device_printf(dev, "Could not allocate disk(s)\n");
		err = ENOMEM;
		goto fail_teardown_intr;
	}

	for (i = 0; i < sc->sc_nregs; i++) {
		struct ps3disk_region *rp = &sc->sc_reg[i];

		d = sc->sc_disk[i] = disk_alloc();
		d->d_open = ps3disk_open;
		d->d_close = ps3disk_close;
		d->d_strategy = ps3disk_strategy;
		d->d_name = "ps3disk";
		d->d_drv1 = sc;
		d->d_maxsize = PAGE_SIZE;
		d->d_sectorsize = sc->sc_blksize;
		d->d_unit = i;
		d->d_mediasize = sc->sc_reg[i].r_size * sc->sc_blksize;
		d->d_flags |= DISKFLAG_CANFLUSHCACHE;

		mb = d->d_mediasize >> 20;
		unit = 'M';
		if (mb >= 10240) {
			unit = 'G';
			mb /= 1024;
		}

		/* Test to see if we can read this region */
		err = lv1_storage_read(ps3bus_get_device(dev), d->d_unit,
		    0, 0, rp->r_flags, 0, &junk);
		device_printf(dev, "region %d %ju%cB%s\n", i, mb, unit,
		    (err == LV1_DENIED_BY_POLICY) ?  " (hypervisor protected)"
		    : "");

		if (err != LV1_DENIED_BY_POLICY)
			disk_create(d, DISK_VERSION);
	}
	err = 0;

	bioq_init(&sc->sc_bioq);
	bioq_init(&sc->sc_deferredq);
	kproc_create(&ps3disk_task, sc, &sc->sc_task, 0, 0, "ps3disk");

	ps3disk_sysctlattach(sc);
	sc->sc_running = 1;
	return (0);

fail_teardown_intr:
	bus_teardown_intr(dev, sc->sc_irq, sc->sc_irqctx);
fail_release_intr:
	bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqid, sc->sc_irq);
fail_free_regions:
	free(sc->sc_reg, M_PS3DISK);
fail_destroy_lock:
	PS3DISK_LOCK_DESTROY(sc);
	return (err);
}