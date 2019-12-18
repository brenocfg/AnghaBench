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
struct sc_info {scalar_t__ lock; scalar_t__ control_dmat; scalar_t__ buffer_dmat; void* irq; scalar_t__ irqid; scalar_t__ ih; void* reg; scalar_t__ regid; int /*<<< orphan*/ * regbase; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  rev; int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int AC97_F_EAPD_INV ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DS1_BUFFSIZE ; 
 int DS1_CHANS ; 
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
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int ac97_getflags (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  ac97_setflags (struct ac97_info*,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ds1pchan_class ; 
 int /*<<< orphan*/  ds1rchan_class ; 
 int /*<<< orphan*/  ds_ac97 ; 
 int /*<<< orphan*/  ds_finddev (int /*<<< orphan*/ ,int) ; 
 int ds_init (struct sc_info*) ; 
 int /*<<< orphan*/  ds_intr ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 int /*<<< orphan*/  snd_ds1 ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds_pci_attach(device_t dev)
{
	u_int32_t subdev, i;
	struct sc_info *sc;
	struct ac97_info *codec = NULL;
	char 		status[SND_STATUSLEN];

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_ds1 softc");
	sc->dev = dev;
	subdev = (pci_get_subdevice(dev) << 16) | pci_get_subvendor(dev);
	sc->type = ds_finddev(pci_get_devid(dev), subdev);
	sc->rev = pci_get_revid(dev);

	pci_enable_busmaster(dev);

	sc->regid = PCIR_BAR(0);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->regid,
					 RF_ACTIVE);
	if (!sc->reg) {
		device_printf(dev, "unable to map register space\n");
		goto bad;
	}

	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	sc->bufsz = pcm_getbuffersize(dev, 4096, DS1_BUFFSIZE, 65536);

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/sc->bufsz, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/NULL,
		/*lockarg*/NULL, &sc->buffer_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	sc->regbase = NULL;
	if (ds_init(sc) == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	codec = AC97_CREATE(dev, sc, ds_ac97);
	if (codec == NULL)
		goto bad;
	/*
	 * Turn on inverted external amplifier sense flags for few
	 * 'special' boards.
	 */
	switch (subdev) {
	case 0x81171033:	/* NEC ValueStar (VT550/0) */
		ac97_setflags(codec, ac97_getflags(codec) | AC97_F_EAPD_INV);
		break;
	default:
		break;
	}
	mixer_init(dev, ac97_getmixerclass(), codec);

	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					 RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq || snd_setup_intr(dev, sc->irq, INTR_MPSAFE, ds_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	snprintf(status, SND_STATUSLEN, "at memory 0x%jx irq %jd %s",
		 rman_get_start(sc->reg), rman_get_start(sc->irq),PCM_KLDSTRING(snd_ds1));

	if (pcm_register(dev, sc, DS1_CHANS, 2))
		goto bad;
	for (i = 0; i < DS1_CHANS; i++)
		pcm_addchan(dev, PCMDIR_PLAY, &ds1pchan_class, sc);
	for (i = 0; i < 2; i++)
		pcm_addchan(dev, PCMDIR_REC, &ds1rchan_class, sc);
	pcm_setstatus(dev, status);

	return 0;

bad:
	if (codec)
		ac97_destroy(codec);
	if (sc->reg)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->regid, sc->reg);
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if (sc->buffer_dmat)
		bus_dma_tag_destroy(sc->buffer_dmat);
	if (sc->control_dmat)
		bus_dma_tag_destroy(sc->control_dmat);
	if (sc->lock)
		snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);
	return ENXIO;
}