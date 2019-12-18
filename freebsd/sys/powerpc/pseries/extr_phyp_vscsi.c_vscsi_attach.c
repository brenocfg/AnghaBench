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
struct vscsi_xfer {int /*<<< orphan*/  dmamap; struct vscsi_softc* sc; } ;
struct vscsi_softc {int max_transactions; int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * devq; int /*<<< orphan*/ * sim; int /*<<< orphan*/  free_xferq; int /*<<< orphan*/  data_tag; struct vscsi_xfer* xfer; int /*<<< orphan*/  crq_queue; int /*<<< orphan*/  crq_map; int /*<<< orphan*/  crq_tag; scalar_t__ n_crqs; scalar_t__ crq_phys; struct vscsi_xfer loginxp; int /*<<< orphan*/  active_xferq; int /*<<< orphan*/  irq_cookie; int /*<<< orphan*/  irq; scalar_t__ irqid; int /*<<< orphan*/  unit; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_VSCSI ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vscsi_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct vscsi_softc*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vscsi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 struct vscsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct vscsi_xfer* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue ; 
 int /*<<< orphan*/  vscsi_cam_action ; 
 int /*<<< orphan*/  vscsi_cam_poll ; 
 int /*<<< orphan*/  vscsi_crq_load_cb ; 
 int /*<<< orphan*/  vscsi_intr ; 
 int /*<<< orphan*/  vscsi_setup_bus (struct vscsi_softc*) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vscsi_attach(device_t dev)
{
	struct vscsi_softc *sc;
	struct vscsi_xfer *xp;
	int error, i;

	sc = device_get_softc(dev);
	if (sc == NULL)
		return (EINVAL);

	sc->dev = dev;
	mtx_init(&sc->io_lock, "vscsi", NULL, MTX_DEF);

	/* Get properties */
	OF_getencprop(ofw_bus_get_node(dev), "reg", &sc->unit,
	    sizeof(sc->unit));

	/* Setup interrupt */
	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
	    RF_ACTIVE);

	if (!sc->irq) {
		device_printf(dev, "Could not allocate IRQ\n");
		mtx_destroy(&sc->io_lock);
		return (ENXIO);
	}

	bus_setup_intr(dev, sc->irq, INTR_TYPE_CAM | INTR_MPSAFE |
	    INTR_ENTROPY, NULL, vscsi_intr, sc, &sc->irq_cookie);

	/* Data DMA */
	error = bus_dma_tag_create(bus_get_dma_tag(dev), 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, BUS_SPACE_MAXSIZE,
	    256, BUS_SPACE_MAXSIZE_32BIT, 0, busdma_lock_mutex, &sc->io_lock,
	    &sc->data_tag);

	TAILQ_INIT(&sc->active_xferq);
	TAILQ_INIT(&sc->free_xferq);

	/* First XFER for login data */
	sc->loginxp.sc = sc;
	bus_dmamap_create(sc->data_tag, 0, &sc->loginxp.dmamap);
	TAILQ_INSERT_TAIL(&sc->free_xferq, &sc->loginxp, queue);
	 
	/* CRQ area */
	error = bus_dma_tag_create(bus_get_dma_tag(dev), PAGE_SIZE, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, 8*PAGE_SIZE,
	    1, BUS_SPACE_MAXSIZE, 0, NULL, NULL, &sc->crq_tag);
	error = bus_dmamem_alloc(sc->crq_tag, (void **)&sc->crq_queue,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO, &sc->crq_map);
	sc->crq_phys = 0;
	sc->n_crqs = 0;
	error = bus_dmamap_load(sc->crq_tag, sc->crq_map, sc->crq_queue,
	    8*PAGE_SIZE, vscsi_crq_load_cb, sc, 0);

	mtx_lock(&sc->io_lock);
	vscsi_setup_bus(sc);
	sc->xfer = malloc(sizeof(sc->xfer[0])*sc->max_transactions, M_VSCSI,
	    M_NOWAIT);
	for (i = 0; i < sc->max_transactions; i++) {
		xp = &sc->xfer[i];
		xp->sc = sc;

		error = bus_dmamap_create(sc->data_tag, 0, &xp->dmamap);
		if (error) {
			device_printf(dev, "Could not create DMA map (%d)\n",
			    error);
			break;
		}

		TAILQ_INSERT_TAIL(&sc->free_xferq, xp, queue);
	}
	mtx_unlock(&sc->io_lock);

	/* Allocate CAM bits */
	if ((sc->devq = cam_simq_alloc(sc->max_transactions)) == NULL)
		return (ENOMEM);

	sc->sim = cam_sim_alloc(vscsi_cam_action, vscsi_cam_poll, "vscsi", sc,
				device_get_unit(dev), &sc->io_lock,
				sc->max_transactions, sc->max_transactions,
				sc->devq);
	if (sc->sim == NULL) {
		cam_simq_free(sc->devq);
		sc->devq = NULL;
		device_printf(dev, "CAM SIM attach failed\n");
		return (EINVAL);
	}


	mtx_lock(&sc->io_lock);
	if (xpt_bus_register(sc->sim, dev, 0) != 0) {
		device_printf(dev, "XPT bus registration failed\n");
		cam_sim_free(sc->sim, FALSE);
		sc->sim = NULL;
		cam_simq_free(sc->devq);
		sc->devq = NULL;
		mtx_unlock(&sc->io_lock);
		return (EINVAL);
	}
	mtx_unlock(&sc->io_lock);

	return (0);
}