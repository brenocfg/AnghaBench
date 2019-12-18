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
struct via_info {int bufsz; int codec_caps; scalar_t__ lock; scalar_t__ sgd_dmat; int /*<<< orphan*/  sgd_dmamap; scalar_t__ sgd_table; scalar_t__ sgd_addr; scalar_t__ parent_dmat; void* irq; scalar_t__ irqid; scalar_t__ ih; void* reg; scalar_t__ regid; scalar_t__ codec; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;
struct via_dma_op {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AC97_CREATE (int /*<<< orphan*/ ,struct via_info*,int /*<<< orphan*/ ) ; 
 int AC97_EXTCAP_VRA ; 
 int AC97_EXTCAP_VRM ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NSEGS ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  VIA_AC97STATUS ; 
 int VIA_AC97STATUS_RDY ; 
 int /*<<< orphan*/  VIA_ACLINKCTRL ; 
 int VIA_ACLINK_DESIRED ; 
 int VIA_ACLINK_EN ; 
 int VIA_ACLINK_NRST ; 
 int VIA_ACLINK_SYNC ; 
 int /*<<< orphan*/  VIA_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  VIA_PLAY_MODE ; 
 int /*<<< orphan*/  VIA_RECORD_MODE ; 
 int VIA_RPMODE_AUTOSTART ; 
 int VIA_RPMODE_INTR_EOL ; 
 int VIA_RPMODE_INTR_FLAG ; 
 int /*<<< orphan*/  ac97_destroy (scalar_t__) ; 
 int ac97_getextcaps (scalar_t__) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  ac97_setextmode (scalar_t__,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 scalar_t__ bus_dmamap_load (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct via_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (scalar_t__,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_cb ; 
 int /*<<< orphan*/  free (struct via_info*,int /*<<< orphan*/ ) ; 
 struct via_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct via_info*) ; 
 int pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct via_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct via_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snd_via82c686 ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_ac97 ; 
 int /*<<< orphan*/  via_intr ; 
 int /*<<< orphan*/  via_wr (struct via_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  viachan_class ; 

__attribute__((used)) static int
via_attach(device_t dev)
{
	struct via_info *via = NULL;
	char status[SND_STATUSLEN];
	u_int32_t data, cnt;

	via = malloc(sizeof(*via), M_DEVBUF, M_WAITOK | M_ZERO);
	via->lock = snd_mtxcreate(device_get_nameunit(dev),
	    "snd_via82c686 softc");

	pci_enable_busmaster(dev);

	/* Wake up and reset AC97 if necessary */
	data = pci_read_config(dev, VIA_AC97STATUS, 1);

	if ((data & VIA_AC97STATUS_RDY) == 0) {
		/* Cold reset per ac97r2.3 spec (page 95) */
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN, 1);			/* Assert low */
		DELAY(100);									/* Wait T_rst_low */
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN | VIA_ACLINK_NRST, 1);	/* Assert high */
		DELAY(5);									/* Wait T_rst2clk */
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN, 1);			/* Assert low */
	} else {
		/* Warm reset */
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN, 1);			/* Force no sync */
		DELAY(100);
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN | VIA_ACLINK_SYNC, 1);	/* Sync */
		DELAY(5);									/* Wait T_sync_high */
		pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_EN, 1);			/* Force no sync */
		DELAY(5);									/* Wait T_sync2clk */
	}

	/* Power everything up */
	pci_write_config(dev, VIA_ACLINKCTRL, VIA_ACLINK_DESIRED, 1);	

	/* Wait for codec to become ready (largest reported delay here 310ms) */
	for (cnt = 0; cnt < 2000; cnt++) {
		data = pci_read_config(dev, VIA_AC97STATUS, 1);
		if (data & VIA_AC97STATUS_RDY) 
			break;
		DELAY(5000);
	}

	via->regid = PCIR_BAR(0);
	via->reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&via->regid, RF_ACTIVE);
	if (!via->reg) {
		device_printf(dev, "cannot allocate bus resource.");
		goto bad;
	}
	via->st = rman_get_bustag(via->reg);
	via->sh = rman_get_bushandle(via->reg);

	via->bufsz = pcm_getbuffersize(dev, 4096, VIA_DEFAULT_BUFSZ, 65536);

	via->irqid = 0;
	via->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &via->irqid,
		RF_ACTIVE | RF_SHAREABLE);
	if (!via->irq || snd_setup_intr(dev, via->irq, INTR_MPSAFE, via_intr, via, &via->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	via_wr(via, VIA_PLAY_MODE, VIA_RPMODE_AUTOSTART | VIA_RPMODE_INTR_FLAG | VIA_RPMODE_INTR_EOL, 1);
	via_wr(via, VIA_RECORD_MODE, VIA_RPMODE_AUTOSTART | VIA_RPMODE_INTR_FLAG | VIA_RPMODE_INTR_EOL, 1);

	via->codec = AC97_CREATE(dev, via, via_ac97);
	if (!via->codec)
		goto bad;

	if (mixer_init(dev, ac97_getmixerclass(), via->codec))
		goto bad;

	via->codec_caps = ac97_getextcaps(via->codec);
	ac97_setextmode(via->codec, 
			via->codec_caps & (AC97_EXTCAP_VRA | AC97_EXTCAP_VRM));

	/* DMA tag for buffers */
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/via->bufsz, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/NULL,
		/*lockarg*/NULL, &via->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	/*
	 *  DMA tag for SGD table.  The 686 uses scatter/gather DMA and
	 *  requires a list in memory of work to do.  We need only 16 bytes
	 *  for this list, and it is wasteful to allocate 16K.
	 */
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/NSEGS * sizeof(struct via_dma_op),
		/*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/NULL,
		/*lockarg*/NULL, &via->sgd_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	if (bus_dmamem_alloc(via->sgd_dmat, (void **)&via->sgd_table,
	    BUS_DMA_NOWAIT, &via->sgd_dmamap) != 0)
		goto bad;
	if (bus_dmamap_load(via->sgd_dmat, via->sgd_dmamap, via->sgd_table,
	    NSEGS * sizeof(struct via_dma_op), dma_cb, via, 0) != 0)
		goto bad;

	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd %s",
		 rman_get_start(via->reg), rman_get_start(via->irq),
		 PCM_KLDSTRING(snd_via82c686));

	/* Register */
	if (pcm_register(dev, via, 1, 1)) goto bad;
	pcm_addchan(dev, PCMDIR_PLAY, &viachan_class, via);
	pcm_addchan(dev, PCMDIR_REC, &viachan_class, via);
	pcm_setstatus(dev, status);
	return 0;
bad:
	if (via->codec) ac97_destroy(via->codec);
	if (via->reg) bus_release_resource(dev, SYS_RES_IOPORT, via->regid, via->reg);
	if (via->ih) bus_teardown_intr(dev, via->irq, via->ih);
	if (via->irq) bus_release_resource(dev, SYS_RES_IRQ, via->irqid, via->irq);
	if (via->parent_dmat) bus_dma_tag_destroy(via->parent_dmat);
	if (via->sgd_addr) bus_dmamap_unload(via->sgd_dmat, via->sgd_dmamap);
	if (via->sgd_table) bus_dmamem_free(via->sgd_dmat, via->sgd_table, via->sgd_dmamap);
	if (via->sgd_dmat) bus_dma_tag_destroy(via->sgd_dmat);
	if (via->lock) snd_mtxfree(via->lock);
	if (via) free(via, M_DEVBUF);
	return ENXIO;
}