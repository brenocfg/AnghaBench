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
struct TYPE_2__ {int /*<<< orphan*/  (* ich_func ) (struct atiixp_info*) ;struct atiixp_info* ich_arg; } ;
struct atiixp_info {int poll_ticks; int polling; int bufsz; int blkcnt; TYPE_1__ delayed_attach; int /*<<< orphan*/  sgd_table; int /*<<< orphan*/  sgd_dmamap; int /*<<< orphan*/  sgd_dmat; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  ih; void* irq; scalar_t__ irqid; void* reg; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; scalar_t__ regid; int /*<<< orphan*/  regtype; int /*<<< orphan*/  dev; int /*<<< orphan*/  poll_timer; int /*<<< orphan*/  lock; } ;
struct atiixp_dma_op {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATI_IXP_BLK_ALIGN ; 
 int ATI_IXP_BLK_MIN ; 
 int /*<<< orphan*/  ATI_IXP_BUFSZ_DEFAULT ; 
 int /*<<< orphan*/  ATI_IXP_BUFSZ_MAX ; 
 int /*<<< orphan*/  ATI_IXP_BUFSZ_MIN ; 
 int ATI_IXP_DMA_CHSEGS ; 
 int ATI_IXP_DMA_CHSEGS_MAX ; 
 int ATI_IXP_DMA_CHSEGS_MIN ; 
 int ATI_IXP_NCHANS ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  atiixp_chip_post_init (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_chip_pre_init (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_dma_cb ; 
 int /*<<< orphan*/  atiixp_intr ; 
 int /*<<< orphan*/  atiixp_release_resource (struct atiixp_info*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cold ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct atiixp_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atiixp_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
atiixp_pci_attach(device_t dev)
{
	struct atiixp_info *sc;
	int i;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_atiixp softc");
	sc->dev = dev;

	callout_init(&sc->poll_timer, 1);
	sc->poll_ticks = 1;

	if (resource_int_value(device_get_name(sc->dev),
	    device_get_unit(sc->dev), "polling", &i) == 0 && i != 0)
		sc->polling = 1;
	else
		sc->polling = 0;

	pci_enable_busmaster(dev);

	sc->regid = PCIR_BAR(0);
	sc->regtype = SYS_RES_MEMORY;
	sc->reg = bus_alloc_resource_any(dev, sc->regtype,
	    &sc->regid, RF_ACTIVE);

	if (!sc->reg) {
		device_printf(dev, "unable to allocate register space\n");
		goto bad;
	}

	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	sc->bufsz = pcm_getbuffersize(dev, ATI_IXP_BUFSZ_MIN,
	    ATI_IXP_BUFSZ_DEFAULT, ATI_IXP_BUFSZ_MAX);

	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq || snd_setup_intr(dev, sc->irq, INTR_MPSAFE,
	    atiixp_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	/*
	 * Let the user choose the best DMA segments.
	 */
	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "blocksize", &i) == 0 && i > 0) {
		i &= ATI_IXP_BLK_ALIGN;
		if (i < ATI_IXP_BLK_MIN)
			i = ATI_IXP_BLK_MIN;
		sc->blkcnt = sc->bufsz / i;
		i = 0;
		while (sc->blkcnt >> i)
			i++;
		sc->blkcnt = 1 << (i - 1);
		if (sc->blkcnt < ATI_IXP_DMA_CHSEGS_MIN)
			sc->blkcnt = ATI_IXP_DMA_CHSEGS_MIN;
		else if (sc->blkcnt > ATI_IXP_DMA_CHSEGS_MAX)
			sc->blkcnt = ATI_IXP_DMA_CHSEGS_MAX;

	} else
		sc->blkcnt = ATI_IXP_DMA_CHSEGS;

	/*
	 * DMA tag for scatter-gather buffers and link pointers
	 */
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/sc->bufsz, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/NULL,
		/*lockarg*/NULL, &sc->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/ATI_IXP_DMA_CHSEGS_MAX * ATI_IXP_NCHANS *
		sizeof(struct atiixp_dma_op),
		/*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/NULL,
		/*lockarg*/NULL, &sc->sgd_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	if (bus_dmamem_alloc(sc->sgd_dmat, (void **)&sc->sgd_table,
	    BUS_DMA_NOWAIT, &sc->sgd_dmamap) == -1)
		goto bad;

	if (bus_dmamap_load(sc->sgd_dmat, sc->sgd_dmamap, sc->sgd_table,
	    ATI_IXP_DMA_CHSEGS_MAX * ATI_IXP_NCHANS *
	    sizeof(struct atiixp_dma_op), atiixp_dma_cb, sc, 0))
		goto bad;


	atiixp_chip_pre_init(sc);

	sc->delayed_attach.ich_func = atiixp_chip_post_init;
	sc->delayed_attach.ich_arg = sc;
	if (cold == 0 ||
	    config_intrhook_establish(&sc->delayed_attach) != 0) {
		sc->delayed_attach.ich_func = NULL;
		atiixp_chip_post_init(sc);
	}

	return (0);

bad:
	atiixp_release_resource(sc);
	return (ENXIO);
}