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
typedef  int u_int32_t ;
struct resource {int dummy; } ;
struct agg_info {int bufsz; int regid; int irqid; int /*<<< orphan*/  lock; int /*<<< orphan*/ * buf_dmat; int /*<<< orphan*/ * stat_dmat; int /*<<< orphan*/  stat_map; int /*<<< orphan*/ * stat; int /*<<< orphan*/  playchns; int /*<<< orphan*/  pch; struct ac97_info* codec; void* ih; struct resource* irq; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; struct resource* reg; int /*<<< orphan*/  curpwr; scalar_t__ phys; int /*<<< orphan*/  dev; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGG_DEFAULT_BUFSZ ; 
 int AGG_MAXPLAYCH ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  MAESTRO_MAXADDR ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  PCI_POWERSTATE_D3 ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int WAVCACHE_BASEADDR_SHIFT ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  adjust_pchbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  agg_ac97 ; 
 int /*<<< orphan*/  agg_intr ; 
 int /*<<< orphan*/  agg_lock (struct agg_info*) ; 
 int /*<<< orphan*/  agg_power (struct agg_info*,int /*<<< orphan*/ ) ; 
 int agg_rdcodec (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (struct agg_info*) ; 
 int /*<<< orphan*/  aggpch_class ; 
 int /*<<< orphan*/  aggrch_class ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_malloc (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct agg_info*,int /*<<< orphan*/ ) ; 
 struct agg_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_hwvol_init (int /*<<< orphan*/ ) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct agg_info*) ; 
 int pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int pcm_register (int /*<<< orphan*/ ,struct agg_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  powerstate_init ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_end (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct agg_info*,void**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agg_attach(device_t dev)
{
	struct agg_info	*ess = NULL;
	u_int32_t	data;
	int	regid = PCIR_BAR(0);
	struct resource	*reg = NULL;
	struct ac97_info	*codec = NULL;
	int	irqid = 0;
	struct resource	*irq = NULL;
	void	*ih = NULL;
	char	status[SND_STATUSLEN];
	int	dacn, ret = 0;

	ess = malloc(sizeof(*ess), M_DEVBUF, M_WAITOK | M_ZERO);
	ess->dev = dev;

	mtx_init(&ess->lock, device_get_desc(dev), "snd_maestro softc",
		 MTX_DEF | MTX_RECURSE);
	if (!mtx_initialized(&ess->lock)) {
		device_printf(dev, "failed to create a mutex.\n");
		ret = ENOMEM;
		goto bad;
	}

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "dac", &dacn) == 0) {
	    	if (dacn < 1)
			dacn = 1;
		else if (dacn > AGG_MAXPLAYCH)
			dacn = AGG_MAXPLAYCH;
	} else
		dacn = AGG_MAXPLAYCH;

	ess->bufsz = pcm_getbuffersize(dev, 4096, AGG_DEFAULT_BUFSZ, 65536);
	if (bus_dma_tag_create(/*parent*/ bus_get_dma_tag(dev),
			       /*align */ 4, 1 << (16+1),
			       /*limit */ MAESTRO_MAXADDR, BUS_SPACE_MAXADDR,
			       /*filter*/ NULL, NULL,
			       /*size  */ ess->bufsz, 1, 0x3ffff,
			       /*flags */ 0,
			       /*lock  */ busdma_lock_mutex, &Giant,
			       &ess->buf_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		ret = ENOMEM;
		goto bad;
	}

	if (bus_dma_tag_create(/*parent*/ bus_get_dma_tag(dev),
			       /*align */ 1 << WAVCACHE_BASEADDR_SHIFT,
			                  1 << (16+1),
			       /*limit */ MAESTRO_MAXADDR, BUS_SPACE_MAXADDR,
			       /*filter*/ NULL, NULL,
			       /*size  */ 3*ess->bufsz, 1, 0x3ffff,
			       /*flags */ 0,
			       /*lock  */ busdma_lock_mutex, &Giant,
			       &ess->stat_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		ret = ENOMEM;
		goto bad;
	}

	/* Allocate the room for brain-damaging status buffer. */
	ess->stat = dma_malloc(ess->stat_dmat, 3*ess->bufsz, &ess->phys,
	    &ess->stat_map);
	if (ess->stat == NULL) {
		device_printf(dev, "cannot allocate status buffer\n");
		ret = ENOMEM;
		goto bad;
	}
	if (bootverbose)
		device_printf(dev, "Maestro status/record buffer: %#llx\n",
		    (long long)ess->phys);

	/* State D0-uninitialized. */
	ess->curpwr = PCI_POWERSTATE_D3;
	pci_set_powerstate(dev, PCI_POWERSTATE_D0);

	pci_enable_busmaster(dev);

	/* Allocate resources. */
	reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &regid, RF_ACTIVE);
	if (reg != NULL) {
		ess->reg = reg;
		ess->regid = regid;
		ess->st = rman_get_bustag(reg);
		ess->sh = rman_get_bushandle(reg);
	} else {
		device_printf(dev, "unable to map register space\n");
		ret = ENXIO;
		goto bad;
	}
	irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &irqid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (irq != NULL) {
		ess->irq = irq;
		ess->irqid = irqid;
	} else {
		device_printf(dev, "unable to map interrupt\n");
		ret = ENXIO;
		goto bad;
	}

	/* Setup resources. */
	if (snd_setup_intr(dev, irq, INTR_MPSAFE, agg_intr, ess, &ih)) {
		device_printf(dev, "unable to setup interrupt\n");
		ret = ENXIO;
		goto bad;
	} else
		ess->ih = ih;

	/* Transition from D0-uninitialized to D0. */
	agg_lock(ess);
	agg_power(ess, PCI_POWERSTATE_D0);
	if (agg_rdcodec(ess, 0) == 0x80) {
		/* XXX - TODO: PT101 */
		agg_unlock(ess);
		device_printf(dev, "PT101 codec detected!\n");
		ret = ENXIO;
		goto bad;
	}
	agg_unlock(ess);
	codec = AC97_CREATE(dev, ess, agg_ac97);
	if (codec == NULL) {
		device_printf(dev, "failed to create AC97 codec softc!\n");
		ret = ENOMEM;
		goto bad;
	}
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) {
		device_printf(dev, "mixer initialization failed!\n");
		ret = ENXIO;
		goto bad;
	}
	ess->codec = codec;

	ret = pcm_register(dev, ess, dacn, 1);
	if (ret)
		goto bad;

	mixer_hwvol_init(dev);
	agg_lock(ess);
	agg_power(ess, powerstate_init);
	agg_unlock(ess);
	for (data = 0; data < dacn; data++)
		pcm_addchan(dev, PCMDIR_PLAY, &aggpch_class, ess);
	pcm_addchan(dev, PCMDIR_REC, &aggrch_class, ess);
	adjust_pchbase(ess->pch, ess->playchns, ess->bufsz);

	snprintf(status, SND_STATUSLEN,
	    "port 0x%jx-0x%jx irq %jd at device %d.%d on pci%d",
	    rman_get_start(reg), rman_get_end(reg), rman_get_start(irq),
	    pci_get_slot(dev), pci_get_function(dev), pci_get_bus(dev));
	pcm_setstatus(dev, status);

	return 0;

 bad:
	if (codec != NULL)
		ac97_destroy(codec);
	if (ih != NULL)
		bus_teardown_intr(dev, irq, ih);
	if (irq != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, irqid, irq);
	if (reg != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT, regid, reg);
	if (ess != NULL) {
		if (ess->stat != NULL)
			dma_free(ess->stat_dmat, ess->stat, ess->stat_map);
		if (ess->stat_dmat != NULL)
			bus_dma_tag_destroy(ess->stat_dmat);
		if (ess->buf_dmat != NULL)
			bus_dma_tag_destroy(ess->buf_dmat);
		if (mtx_initialized(&ess->lock))
			mtx_destroy(&ess->lock);
		free(ess, M_DEVBUF);
	}

	return ret;
}