#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  rm_descr; int /*<<< orphan*/  rm_type; int /*<<< orphan*/  rm_end; scalar_t__ rm_start; } ;
struct pcib_secbus {int sub_reg; int /*<<< orphan*/ * res; void* sub; void* sec; TYPE_1__ rman; void* dev; } ;
struct vmd_softc {void* vmd_dev; int* vmd_regs_rid; int vmd_io_rid; int vmd_msix_count; int /*<<< orphan*/ * vmd_child; TYPE_3__* vmd_irq; struct pcib_secbus vmd_bus; int /*<<< orphan*/ ** vmd_regs_resource; int /*<<< orphan*/  vmd_bhandle; int /*<<< orphan*/  vmd_btag; int /*<<< orphan*/ * vmd_io_resource; int /*<<< orphan*/  vmd_irq_lock; int /*<<< orphan*/  vmd_irq_task; int /*<<< orphan*/  vmd_irq_tq; } ;
struct vmd_irq {int dummy; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int vmd_rid; int vmd_instance; int /*<<< orphan*/ * vmd_res; int /*<<< orphan*/  vmd_handle; int /*<<< orphan*/  vmd_list; struct vmd_softc* vmd_sc; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIM_BAR_MEM_64 ; 
 int PCIM_BAR_MEM_TYPE ; 
 int PCIR_BAR (int) ; 
 int PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_PRIBUS_2 ; 
 int PCIR_SECBUS_1 ; 
 int PCIR_SUBBUS_1 ; 
 scalar_t__ PCI_BAR_MEM (int) ; 
 int /*<<< orphan*/  PCI_BUSMAX ; 
 int /*<<< orphan*/  PCI_RES_BUS ; 
 int /*<<< orphan*/  PI_DISK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmd_softc*) ; 
 int VMD_MAX_BAR ; 
 int /*<<< orphan*/  bus_adjust_resource (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,void*) ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_anywhere (void*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct vmd_softc*,int) ; 
 int /*<<< orphan*/ * device_add_child (void*,int /*<<< orphan*/ *,int) ; 
 char* device_get_nameunit (void*) ; 
 void* device_get_parent (void*) ; 
 struct vmd_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msix (void*,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (void*) ; 
 int pci_msix_count (void*) ; 
 int pci_read_config (void*,int,int) ; 
 int /*<<< orphan*/  pci_write_config (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcib_get_bus (void*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 void* rman_get_end (int /*<<< orphan*/ *) ; 
 int rman_get_size (int /*<<< orphan*/ *) ; 
 void* rman_get_start (int /*<<< orphan*/ *) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  vmd_free (struct vmd_softc*) ; 
 int /*<<< orphan*/  vmd_handle_irq ; 
 int /*<<< orphan*/  vmd_intr ; 
 void* vmd_read_config (void*,int,int,int,int,int) ; 

__attribute__((used)) static int
vmd_attach(device_t dev)
{
	struct vmd_softc *sc;
	struct pcib_secbus *bus;
	uint32_t bar;
	int i, j, error;
	int rid, sec_reg;
	static int b;
	static int s;
	static int f;
	int min_count = 1;
	char buf[64];

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->vmd_dev = dev;
	b = s = f = 0;

	pci_enable_busmaster(dev);

#ifdef TASK_QUEUE_INTR
	sc->vmd_irq_tq = taskqueue_create_fast("vmd_taskq", M_NOWAIT,
	    taskqueue_thread_enqueue, &sc->vmd_irq_tq);
	taskqueue_start_threads(&sc->vmd_irq_tq, 1, PI_DISK, "%s taskq",
            device_get_nameunit(sc->vmd_dev));
	TASK_INIT(&sc->vmd_irq_task, 0, vmd_handle_irq, sc);
#else
	mtx_init(&sc->vmd_irq_lock, "VMD IRQ lock", NULL, MTX_DEF);
#endif
	for (i = 0, j = 0; i < VMD_MAX_BAR; i++, j++ ) {
		sc->vmd_regs_rid[i] = PCIR_BAR(j);
		bar = pci_read_config(dev, PCIR_BAR(0), 4);
		if (PCI_BAR_MEM(bar) && (bar & PCIM_BAR_MEM_TYPE) ==
		    PCIM_BAR_MEM_64)
			j++;
		if ((sc->vmd_regs_resource[i] = bus_alloc_resource_any(
		    sc->vmd_dev, SYS_RES_MEMORY, &sc->vmd_regs_rid[i],
		    RF_ACTIVE)) == NULL) {
			device_printf(dev, "Cannot allocate resources\n");
			goto fail;
		}
	}

	sc->vmd_io_rid = PCIR_IOBASEL_1;
	sc->vmd_io_resource = bus_alloc_resource_any(
	    device_get_parent(sc->vmd_dev), SYS_RES_IOPORT, &sc->vmd_io_rid,
	    RF_ACTIVE);
	if (sc->vmd_io_resource == NULL) {
		device_printf(dev, "Cannot allocate IO\n");
		goto fail;
	}


	sc->vmd_btag = rman_get_bustag(sc->vmd_regs_resource[0]);
	sc->vmd_bhandle = rman_get_bushandle(sc->vmd_regs_resource[0]);

	pci_write_config(dev, PCIR_PRIBUS_2,
	    pcib_get_bus(device_get_parent(dev)), 1);

	sec_reg = PCIR_SECBUS_1;
	bus = &sc->vmd_bus;
	bus->sub_reg = PCIR_SUBBUS_1;
	bus->sec = vmd_read_config(dev, b, s, f, sec_reg, 1);
	bus->sub = vmd_read_config(dev, b, s, f, bus->sub_reg, 1);
	bus->dev = dev;
	bus->rman.rm_start = 0;
	bus->rman.rm_end = PCI_BUSMAX;
	bus->rman.rm_type = RMAN_ARRAY;
	snprintf(buf, sizeof(buf), "%s bus numbers", device_get_nameunit(dev));
	bus->rman.rm_descr = strdup(buf, M_DEVBUF);
	error = rman_init(&bus->rman);

	if (error) {
		device_printf(dev, "Failed to initialize %s bus number rman\n",
		    device_get_nameunit(dev));
		goto fail;
	}

	/*
	 * Allocate a bus range.  This will return an existing bus range
	 * if one exists, or a new bus range if one does not.
	 */
	rid = 0;
	bus->res = bus_alloc_resource_anywhere(dev, PCI_RES_BUS, &rid,
	    min_count, 0);
	if (bus->res == NULL) {
		/*
		 * Fall back to just allocating a range of a single bus
		 * number.
		 */
		bus->res = bus_alloc_resource_anywhere(dev, PCI_RES_BUS, &rid,
		    1, 0);
	} else if (rman_get_size(bus->res) < min_count) {
		/*
		 * Attempt to grow the existing range to satisfy the
		 * minimum desired count.
		 */
		(void)bus_adjust_resource(dev, PCI_RES_BUS, bus->res,
		    rman_get_start(bus->res), rman_get_start(bus->res) +
		    min_count - 1);
	}


	/*
	 * Add the initial resource to the rman.
	 */
	if (bus->res != NULL) {
		error = rman_manage_region(&bus->rman, rman_get_start(bus->res),
		    rman_get_end(bus->res));
		if (error) {
			device_printf(dev, "Failed to add resource to rman\n");
			goto fail;
		}
		bus->sec = rman_get_start(bus->res);
		bus->sub = rman_get_end(bus->res);
	}

	sc->vmd_msix_count = pci_msix_count(dev);
	if (pci_alloc_msix(dev, &sc->vmd_msix_count) == 0) {
		sc->vmd_irq = malloc(sizeof(struct vmd_irq) *
		    sc->vmd_msix_count,
		    M_DEVBUF, M_WAITOK | M_ZERO);

		for (i = 0; i < sc->vmd_msix_count; i++) {
			sc->vmd_irq[i].vmd_rid = i + 1;
			sc->vmd_irq[i].vmd_sc = sc;
			sc->vmd_irq[i].vmd_instance = i;
			sc->vmd_irq[i].vmd_res = bus_alloc_resource_any(dev,
			    SYS_RES_IRQ, &sc->vmd_irq[i].vmd_rid,
			    RF_ACTIVE);
			if (sc->vmd_irq[i].vmd_res == NULL) {
				device_printf(dev,"Failed to alloc irq\n");
				goto fail;
			}

			TAILQ_INIT(&sc->vmd_irq[i].vmd_list);
			if (bus_setup_intr(dev, sc->vmd_irq[i].vmd_res,
			    INTR_TYPE_MISC | INTR_MPSAFE, NULL, vmd_intr,
			    &sc->vmd_irq[i], &sc->vmd_irq[i].vmd_handle)) {
				device_printf(sc->vmd_dev,
				    "Cannot set up interrupt\n");
				sc->vmd_irq[i].vmd_res = NULL;
				goto fail;
			}
		}
	}

	sc->vmd_child = device_add_child(dev, NULL, -1);

	if (sc->vmd_child == NULL) {
		device_printf(dev, "Failed to attach child\n");
		goto fail;
	}

	error = device_probe_and_attach(sc->vmd_child);
	if (error) {
		device_printf(dev, "Failed to add probe child\n");
		goto fail;
	}


	return (0);

fail:
	vmd_free(sc);
	return (ENXIO);
}