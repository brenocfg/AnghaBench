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
struct sc_info {scalar_t__ lock; void* reg; scalar_t__ regid; void* irq; scalar_t__ irqid; scalar_t__ ih; scalar_t__ parent_dmat; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CMI_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ cmi_init (struct sc_info*) ; 
 int /*<<< orphan*/  cmi_initsys (struct sc_info*) ; 
 int /*<<< orphan*/  cmi_intr ; 
 int /*<<< orphan*/  cmi_midiattach (struct sc_info*) ; 
 int /*<<< orphan*/  cmi_mixer_class ; 
 int /*<<< orphan*/  cmi_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmichan_class ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 int /*<<< orphan*/  snd_cmi ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmi_attach(device_t dev)
{
	struct sc_info		*sc;
	char			status[SND_STATUSLEN];

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_cmi softc");
	pci_enable_busmaster(dev);

	sc->dev = dev;
	sc->regid = PCIR_BAR(0);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->regid,
					 RF_ACTIVE);
	if (!sc->reg) {
		device_printf(dev, "cmi_attach: Cannot allocate bus resource\n");
		goto bad;
	}
	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	if (0)
		cmi_midiattach(sc);

	sc->irqid = 0;
	sc->irq   = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					   RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq ||
	    snd_setup_intr(dev, sc->irq, INTR_MPSAFE, cmi_intr, sc, &sc->ih)) {
		device_printf(dev, "cmi_attach: Unable to map interrupt\n");
		goto bad;
	}

	sc->bufsz = pcm_getbuffersize(dev, 4096, CMI_DEFAULT_BUFSZ, 65536);

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
			       /*boundary*/0,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       /*maxsize*/sc->bufsz, /*nsegments*/1,
			       /*maxsegz*/0x3ffff, /*flags*/0,
			       /*lockfunc*/NULL,
			       /*lockfunc*/NULL,
			       &sc->parent_dmat) != 0) {
		device_printf(dev, "cmi_attach: Unable to create dma tag\n");
		goto bad;
	}

	cmi_power(sc, 0);
	if (cmi_init(sc))
		goto bad;

	if (mixer_init(dev, &cmi_mixer_class, sc))
		goto bad;

	if (pcm_register(dev, sc, 1, 1))
		goto bad;

	cmi_initsys(sc);

	pcm_addchan(dev, PCMDIR_PLAY, &cmichan_class, sc);
	pcm_addchan(dev, PCMDIR_REC, &cmichan_class, sc);

	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd %s",
		 rman_get_start(sc->reg), rman_get_start(sc->irq),PCM_KLDSTRING(snd_cmi));
	pcm_setstatus(dev, status);

	DEB(printf("cmi_attach: succeeded\n"));
	return 0;

 bad:
	if (sc->parent_dmat)
		bus_dma_tag_destroy(sc->parent_dmat);
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if (sc->reg)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->regid, sc->reg);
	if (sc->lock)
		snd_mtxfree(sc->lock);
	if (sc)
		free(sc, M_DEVBUF);

	return ENXIO;
}