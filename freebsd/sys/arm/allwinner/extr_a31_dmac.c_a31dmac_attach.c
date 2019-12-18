#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct a31dmac_softc {int nchans; int /*<<< orphan*/ * res; int /*<<< orphan*/ * ih; TYPE_2__* chans; int /*<<< orphan*/  dmat; int /*<<< orphan*/  mtx; } ;
struct a31dmac_config {int nchans; } ;
typedef  int /*<<< orphan*/ * hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * clk_t ;
struct TYPE_6__ {size_t index; int /*<<< orphan*/  dmamap; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * callbackarg; int /*<<< orphan*/ * callback; struct a31dmac_softc* sc; } ;
struct TYPE_5__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DESC_ALIGN ; 
 int /*<<< orphan*/  DESC_SIZE ; 
 int /*<<< orphan*/  DMA_EN_REG (size_t) ; 
 int /*<<< orphan*/  DMA_IRQ_EN_REG0 ; 
 int /*<<< orphan*/  DMA_IRQ_EN_REG1 ; 
 int /*<<< orphan*/  DMA_IRQ_PEND_REG0 ; 
 int /*<<< orphan*/  DMA_IRQ_PEND_REG1 ; 
 int /*<<< orphan*/  DMA_WRITE (struct a31dmac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a31dmac_dmamap_cb ; 
 int /*<<< orphan*/  a31dmac_intr ; 
 int /*<<< orphan*/  a31dmac_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct a31dmac_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 struct a31dmac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_deassert (int /*<<< orphan*/ *) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a31dmac_attach(device_t dev)
{
	struct a31dmac_softc *sc;
	struct a31dmac_config *conf;
	u_int index;
	hwreset_t rst;
	clk_t clk;
	int error;

	sc = device_get_softc(dev);
	conf = (void *)ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	clk = NULL;
	rst = NULL;

	if (bus_alloc_resources(dev, a31dmac_spec, sc->res)) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->mtx, "a31 dmac", NULL, MTX_SPIN);

	/* Clock and reset setup */
	if (clk_get_by_ofw_index(dev, 0, 0, &clk) != 0) {
		device_printf(dev, "cannot get clock\n");
		goto fail;
	}
	if (clk_enable(clk) != 0) {
		device_printf(dev, "cannot enable clock\n");
		goto fail;
	}
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &rst) != 0) {
		device_printf(dev, "cannot get hwreset\n");
		goto fail;
	}
	if (hwreset_deassert(rst) != 0) {
		device_printf(dev, "cannot de-assert reset\n");
		goto fail;
	}

	/* Descriptor DMA */
	error = bus_dma_tag_create(
		bus_get_dma_tag(dev),		/* Parent tag */
		DESC_ALIGN, 0,			/* alignment, boundary */
		BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
		BUS_SPACE_MAXADDR,		/* highaddr */
		NULL, NULL,			/* filter, filterarg */
		DESC_SIZE, 1,			/* maxsize, nsegs */
		DESC_SIZE,			/* maxsegsize */
		0,				/* flags */
		NULL, NULL,			/* lockfunc, lockarg */
		&sc->dmat);
	if (error != 0) {
		device_printf(dev, "cannot create dma tag\n");
		goto fail;
	}

	/* Disable all interrupts and clear pending status */
	DMA_WRITE(sc, DMA_IRQ_EN_REG0, 0);
	DMA_WRITE(sc, DMA_IRQ_EN_REG1, 0);
	DMA_WRITE(sc, DMA_IRQ_PEND_REG0, ~0);
	DMA_WRITE(sc, DMA_IRQ_PEND_REG1, ~0);

	/* Initialize channels */
	sc->nchans = conf->nchans;
	sc->chans = malloc(sizeof(*sc->chans) * sc->nchans, M_DEVBUF,
	    M_WAITOK | M_ZERO);

	for (index = 0; index < sc->nchans; index++) {
		sc->chans[index].sc = sc;
		sc->chans[index].index = index;
		sc->chans[index].callback = NULL;
		sc->chans[index].callbackarg = NULL;

		error = bus_dmamem_alloc(sc->dmat,
		    (void **)&sc->chans[index].desc,
		    BUS_DMA_WAITOK | BUS_DMA_COHERENT,
		    &sc->chans[index].dmamap);
		if (error != 0) {
			device_printf(dev, "cannot allocate dma mem\n");
			goto fail;
		}
		error = bus_dmamap_load(sc->dmat, sc->chans[index].dmamap, 
		    sc->chans[index].desc, sizeof(*sc->chans[index].desc),
		    a31dmac_dmamap_cb, &sc->chans[index], BUS_DMA_WAITOK);
		if (error != 0) {
			device_printf(dev, "cannot load dma map\n");
			goto fail;
		}

		DMA_WRITE(sc, DMA_EN_REG(index), 0);
	}

	error = bus_setup_intr(dev, sc->res[1], INTR_MPSAFE | INTR_TYPE_MISC,
	    NULL, a31dmac_intr, sc, &sc->ih);
	if (error != 0) {
		device_printf(dev, "could not setup interrupt handler\n");
		bus_release_resources(dev, a31dmac_spec, sc->res);
		mtx_destroy(&sc->mtx);
		return (ENXIO);
	}

	OF_device_register_xref(OF_xref_from_node(ofw_bus_get_node(dev)), dev);
	return (0);

fail:
	for (index = 0; index < sc->nchans; index++)
		if (sc->chans[index].desc != NULL) {
			bus_dmamap_unload(sc->dmat, sc->chans[index].dmamap);
			bus_dmamem_free(sc->dmat, sc->chans[index].desc,
			    sc->chans[index].dmamap);
		}
	if (sc->chans != NULL)
		free(sc->chans, M_DEVBUF);
	if (sc->ih != NULL)
		bus_teardown_intr(dev, sc->res[1], sc->ih);
	if (rst != NULL)
		hwreset_release(rst);
	if (clk != NULL)
		clk_release(clk);
	bus_release_resources(dev, a31dmac_spec, sc->res);

	return (ENXIO);
}