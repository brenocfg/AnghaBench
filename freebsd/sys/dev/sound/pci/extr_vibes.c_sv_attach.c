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
typedef  int u_long ;
typedef  int u_int32_t ;
struct sc_info {int rev; int /*<<< orphan*/ * dmac_reg; void* dmac_rid; void* dmac_type; int /*<<< orphan*/ * dmaa_reg; void* dmaa_rid; void* dmaa_type; int /*<<< orphan*/ * enh_reg; void* enh_rid; void* enh_type; int /*<<< orphan*/ * irq; void* irqid; scalar_t__ ih; scalar_t__ parent_dmat; void* dmac_sh; void* dmac_st; void* dmaa_sh; void* dmaa_st; int /*<<< orphan*/  bufsz; void* enh_sh; void* enh_st; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_24BIT ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SV_DEFAULT_BUFSZ ; 
 void* SV_PCI_DMAA ; 
 int /*<<< orphan*/  SV_PCI_DMAA_SIZE ; 
 void* SV_PCI_DMAC ; 
 int /*<<< orphan*/  SV_PCI_DMAC_SIZE ; 
 int SV_PCI_DMA_ENABLE ; 
 int SV_PCI_DMA_EXTENDED ; 
 void* SV_PCI_ENHANCED ; 
 int /*<<< orphan*/  SV_PCI_GAMES ; 
 int /*<<< orphan*/  SV_PCI_MIDI ; 
 void* SYS_RES_IOPORT ; 
 void* SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,void*,void**,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_resource (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,void*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snd_vibes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_init (struct sc_info*) ; 
 int /*<<< orphan*/  sv_intr ; 
 int /*<<< orphan*/  sv_mix_mute_all (struct sc_info*) ; 
 int /*<<< orphan*/  sv_mixer_class ; 
 int /*<<< orphan*/  sv_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svpchan_class ; 
 int /*<<< orphan*/  svrchan_class ; 

__attribute__((used)) static int
sv_attach(device_t dev) {
	struct sc_info	*sc;
	rman_res_t	count, midi_start, games_start;
	u_int32_t	data;
	char		status[SND_STATUSLEN];
	u_long		sdmaa, sdmac, ml, mu;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->dev = dev;

	pci_enable_busmaster(dev);

        if (pci_get_powerstate(dev) != PCI_POWERSTATE_D0) {
                device_printf(dev, "chip is in D%d power mode "
                              "-- setting to D0\n", pci_get_powerstate(dev));
                pci_set_powerstate(dev, PCI_POWERSTATE_D0);
        }
	sc->enh_rid  = SV_PCI_ENHANCED;
	sc->enh_type = SYS_RES_IOPORT;
	sc->enh_reg  = bus_alloc_resource_any(dev, sc->enh_type,
					      &sc->enh_rid, RF_ACTIVE);
	if (sc->enh_reg == NULL) {
		device_printf(dev, "sv_attach: cannot allocate enh\n");
		return ENXIO;
	}
	sc->enh_st = rman_get_bustag(sc->enh_reg);
	sc->enh_sh = rman_get_bushandle(sc->enh_reg);

	data = pci_read_config(dev, SV_PCI_DMAA, 4);
	DEB(printf("sv_attach: initial dmaa 0x%08x\n", data));
	data = pci_read_config(dev, SV_PCI_DMAC, 4);
	DEB(printf("sv_attach: initial dmac 0x%08x\n", data));

	/* Initialize DMA_A and DMA_C */
	pci_write_config(dev, SV_PCI_DMAA, SV_PCI_DMA_EXTENDED, 4);
	pci_write_config(dev, SV_PCI_DMAC, 0, 4);

	/* Register IRQ handler */
	sc->irqid = 0;
        sc->irq   = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					   RF_ACTIVE | RF_SHAREABLE);
        if (!sc->irq ||
	    snd_setup_intr(dev, sc->irq, 0, sv_intr, sc, &sc->ih)) {
                device_printf(dev, "sv_attach: Unable to map interrupt\n");
                goto fail;
        }

	sc->bufsz = pcm_getbuffersize(dev, 4096, SV_DEFAULT_BUFSZ, 65536);
        if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
			       /*boundary*/0,
                               /*lowaddr*/BUS_SPACE_MAXADDR_24BIT,
                               /*highaddr*/BUS_SPACE_MAXADDR,
                               /*filter*/NULL, /*filterarg*/NULL,
                               /*maxsize*/sc->bufsz, /*nsegments*/1,
                               /*maxsegz*/0x3ffff, /*flags*/0,
			       /*lockfunc*/busdma_lock_mutex,
			       /*lockarg*/&Giant, &sc->parent_dmat) != 0) {
                device_printf(dev, "sv_attach: Unable to create dma tag\n");
                goto fail;
        }

	/* Power up and initialize */
	sv_mix_mute_all(sc);
	sv_power(sc, 0);
	sv_init(sc);

	if (mixer_init(dev, &sv_mixer_class, sc) != 0) {
		device_printf(dev, "sv_attach: Mixer failed to initialize\n");
		goto fail;
	}

	/* XXX This is a hack, and it's ugly.  Okay, the deal is this
	 * card has two more io regions that available for automatic
	 * configuration by the pci code.  These need to be allocated
	 * to used as control registers for the DMA engines.
	 * Unfortunately FBSD has no bus_space_foo() functions so we
	 * have to grab port space in region of existing resources.  Go
	 * for space between midi and game ports.
	 */
	bus_get_resource(dev, SYS_RES_IOPORT, SV_PCI_MIDI, &midi_start, &count);
	bus_get_resource(dev, SYS_RES_IOPORT, SV_PCI_GAMES, &games_start, &count);

	if (games_start < midi_start) {
		ml = games_start;
		mu = midi_start;
	} else {
		ml = midi_start;
		mu = games_start;
	}
	/* Check assumptions about space availability and
           alignment. How driver loaded can determine whether
           games_start > midi_start or vice versa */
	if ((mu - ml >= 0x800)  ||
	    ((mu - ml) % 0x200)) {
		device_printf(dev, "sv_attach: resource assumptions not met "
			      "(midi 0x%08lx, games 0x%08lx)\n",
			      (u_long)midi_start, (u_long)games_start);
		goto fail;
	}

	sdmaa = ml + 0x40;
	sdmac = sdmaa + 0x40;

	/* Add resources to list of pci resources for this device - from here on
	 * they look like normal pci resources. */
	bus_set_resource(dev, SYS_RES_IOPORT, SV_PCI_DMAA, sdmaa, SV_PCI_DMAA_SIZE);
	bus_set_resource(dev, SYS_RES_IOPORT, SV_PCI_DMAC, sdmac, SV_PCI_DMAC_SIZE);

	/* Cache resource short-cuts for dma_a */
	sc->dmaa_rid = SV_PCI_DMAA;
	sc->dmaa_type = SYS_RES_IOPORT;
	sc->dmaa_reg  = bus_alloc_resource_any(dev, sc->dmaa_type,
					       &sc->dmaa_rid, RF_ACTIVE);
	if (sc->dmaa_reg == NULL) {
		device_printf(dev, "sv_attach: cannot allocate dmaa\n");
		goto fail;
	}
	sc->dmaa_st = rman_get_bustag(sc->dmaa_reg);
	sc->dmaa_sh = rman_get_bushandle(sc->dmaa_reg);

	/* Poke port into dma_a configuration, nb bit flags to enable dma */
	data = pci_read_config(dev, SV_PCI_DMAA, 4) | SV_PCI_DMA_ENABLE | SV_PCI_DMA_EXTENDED;
	data = ((u_int32_t)sdmaa & 0xfffffff0) | (data & 0x0f);
	pci_write_config(dev, SV_PCI_DMAA, data, 4);
	DEB(printf("dmaa: 0x%x 0x%x\n", data, pci_read_config(dev, SV_PCI_DMAA, 4)));

	/* Cache resource short-cuts for dma_c */
	sc->dmac_rid = SV_PCI_DMAC;
	sc->dmac_type = SYS_RES_IOPORT;
	sc->dmac_reg  = bus_alloc_resource_any(dev, sc->dmac_type,
					       &sc->dmac_rid, RF_ACTIVE);
	if (sc->dmac_reg == NULL) {
		device_printf(dev, "sv_attach: cannot allocate dmac\n");
		goto fail;
	}
	sc->dmac_st = rman_get_bustag(sc->dmac_reg);
	sc->dmac_sh = rman_get_bushandle(sc->dmac_reg);

	/* Poke port into dma_c configuration, nb bit flags to enable dma */
	data = pci_read_config(dev, SV_PCI_DMAC, 4) | SV_PCI_DMA_ENABLE | SV_PCI_DMA_EXTENDED;
	data = ((u_int32_t)sdmac & 0xfffffff0) | (data & 0x0f);
	pci_write_config(dev, SV_PCI_DMAC, data, 4);
	DEB(printf("dmac: 0x%x 0x%x\n", data, pci_read_config(dev, SV_PCI_DMAC, 4)));

	if (bootverbose)
		printf("Sonicvibes: revision %d.\n", sc->rev);

        if (pcm_register(dev, sc, 1, 1)) {
		device_printf(dev, "sv_attach: pcm_register fail\n");
                goto fail;
	}

        pcm_addchan(dev, PCMDIR_PLAY, &svpchan_class, sc);
        pcm_addchan(dev, PCMDIR_REC,  &svrchan_class, sc);

        snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd %s",
                 rman_get_start(sc->enh_reg),  rman_get_start(sc->irq),PCM_KLDSTRING(snd_vibes));
        pcm_setstatus(dev, status);

        DEB(printf("sv_attach: succeeded\n"));

	return 0;

 fail:
	if (sc->parent_dmat)
		bus_dma_tag_destroy(sc->parent_dmat);
        if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
        if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if (sc->enh_reg)
		bus_release_resource(dev, sc->enh_type, sc->enh_rid, sc->enh_reg);
	if (sc->dmaa_reg)
		bus_release_resource(dev, sc->dmaa_type, sc->dmaa_rid, sc->dmaa_reg);
	if (sc->dmac_reg)
		bus_release_resource(dev, sc->dmac_type, sc->dmac_rid, sc->dmac_reg);
	return ENXIO;
}