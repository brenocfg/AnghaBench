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
typedef  int uint32_t ;
struct ncr53c9x_softc {int /*<<< orphan*/  sc_maxxfer; int /*<<< orphan*/  sc_lock; } ;
struct lsi64854_softc {int sc_channel; int sc_rev; int /*<<< orphan*/  sc_burst; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_buffer_dmat; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_maxdmasize; int /*<<< orphan*/  sc_parent_dmat; int /*<<< orphan*/ * setup; int /*<<< orphan*/  reset; int /*<<< orphan*/  intr; struct ncr53c9x_softc* sc_client; } ;
typedef  int /*<<< orphan*/  bus_dma_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNDARY ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
#define  DMAREV_0 135 
#define  DMAREV_1 134 
#define  DMAREV_2 133 
#define  DMAREV_ESC 132 
 int DMAREV_HME ; 
#define  DMAREV_PLUS 131 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int ENXIO ; 
#define  L64854_CHANNEL_ENET 130 
#define  L64854_CHANNEL_PP 129 
#define  L64854_CHANNEL_SCSI 128 
 int L64854_DEVID ; 
 int L64854_GCSR (struct lsi64854_softc*) ; 
 int /*<<< orphan*/  LDB_ANY ; 
 int /*<<< orphan*/  MAX_DMA_SZ ; 
 int /*<<< orphan*/  NCR_LOCK_INITIALIZED (struct ncr53c9x_softc*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsi64854_enet_intr ; 
 int /*<<< orphan*/  lsi64854_pp_intr ; 
 int /*<<< orphan*/  lsi64854_reset ; 
 int /*<<< orphan*/  lsi64854_scsi_intr ; 
 int /*<<< orphan*/ * lsi64854_setup ; 
 int /*<<< orphan*/ * lsi64854_setup_pp ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
lsi64854_attach(struct lsi64854_softc *sc)
{
	bus_dma_lock_t *lockfunc;
	struct ncr53c9x_softc *nsc;
	void *lockfuncarg;
	uint32_t csr;
	int error;

	lockfunc = NULL;
	lockfuncarg = NULL;
	sc->sc_maxdmasize = MAX_DMA_SZ;

	switch (sc->sc_channel) {
	case L64854_CHANNEL_SCSI:
		nsc = sc->sc_client;
		if (NCR_LOCK_INITIALIZED(nsc) == 0) {
			device_printf(sc->sc_dev, "mutex not initialized\n");
			return (ENXIO);
		}
		lockfunc = busdma_lock_mutex;
		lockfuncarg = &nsc->sc_lock;
		sc->sc_maxdmasize = nsc->sc_maxxfer;
		sc->intr = lsi64854_scsi_intr;
		sc->setup = lsi64854_setup;
		break;
	case L64854_CHANNEL_ENET:
		sc->intr = lsi64854_enet_intr;
		break;
	case L64854_CHANNEL_PP:
		sc->intr = lsi64854_pp_intr;
		sc->setup = lsi64854_setup_pp;
		break;
	default:
		device_printf(sc->sc_dev, "unknown channel\n");
	}
	sc->reset = lsi64854_reset;

	if (sc->setup != NULL) {
		error = bus_dma_tag_create(
		    sc->sc_parent_dmat,		/* parent */
		    1, BOUNDARY,		/* alignment, boundary */
		    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		    BUS_SPACE_MAXADDR,		/* highaddr */
		    NULL, NULL,			/* filter, filterarg */
		    sc->sc_maxdmasize,		/* maxsize */
		    1,				/* nsegments */
		    sc->sc_maxdmasize,		/* maxsegsize */
		    BUS_DMA_ALLOCNOW,		/* flags */
		    lockfunc, lockfuncarg,	/* lockfunc, lockfuncarg */
		    &sc->sc_buffer_dmat);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "cannot allocate buffer DMA tag\n");
			return (error);
		}

		error = bus_dmamap_create(sc->sc_buffer_dmat, 0,
		    &sc->sc_dmamap);
		if (error != 0) {
			device_printf(sc->sc_dev, "DMA map create failed\n");
			bus_dma_tag_destroy(sc->sc_buffer_dmat);
			return (error);
		}
	}

	csr = L64854_GCSR(sc);
	sc->sc_rev = csr & L64854_DEVID;
	if (sc->sc_rev == DMAREV_HME)
		return (0);
	device_printf(sc->sc_dev, "DMA rev. ");
	switch (sc->sc_rev) {
	case DMAREV_0:
		printf("0");
		break;
	case DMAREV_ESC:
		printf("ESC");
		break;
	case DMAREV_1:
		printf("1");
		break;
	case DMAREV_PLUS:
		printf("1+");
		break;
	case DMAREV_2:
		printf("2");
		break;
	default:
		printf("unknown (0x%x)", sc->sc_rev);
	}

	DPRINTF(LDB_ANY, (", burst 0x%x, csr 0x%x", sc->sc_burst, csr));
	printf("\n");

	return (0);
}