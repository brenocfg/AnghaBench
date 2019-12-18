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
struct sc_info {scalar_t__ type; int rev; int audigy; int audigy2; int nchans; scalar_t__ lock; scalar_t__ parent_dmat; int /*<<< orphan*/ * irq; scalar_t__ ih; int /*<<< orphan*/ * reg; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  addrmask; int /*<<< orphan*/  dev; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AC97_CAP_MICCHANNEL ; 
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 scalar_t__ EMU10K2_PCI_ID ; 
 scalar_t__ EMU10K3_PCI_ID ; 
 int /*<<< orphan*/  EMU_A_PTR_ADDR_MASK ; 
 int /*<<< orphan*/  EMU_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  EMU_PTR_ADDR_MASK ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int ac97_getcaps (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emu_ac97 ; 
 int emu_init (struct sc_info*) ; 
 int /*<<< orphan*/  emu_intr ; 
 int /*<<< orphan*/  emu_midiattach (struct sc_info*) ; 
 int /*<<< orphan*/  emupchan_class ; 
 int /*<<< orphan*/  emurchan_class ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1 ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_pci_attach(device_t dev)
{
	struct ac97_info *codec = NULL;
	struct sc_info *sc;
	int i, gotmic;
	char status[SND_STATUSLEN];

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_emu10k1 softc");
	sc->dev = dev;
	sc->type = pci_get_devid(dev);
	sc->rev = pci_get_revid(dev);
	sc->audigy = sc->type == EMU10K2_PCI_ID || sc->type == EMU10K3_PCI_ID;
	sc->audigy2 = (sc->audigy && sc->rev == 0x04);
	sc->nchans = sc->audigy ? 8 : 4;
	sc->addrmask = sc->audigy ? EMU_A_PTR_ADDR_MASK : EMU_PTR_ADDR_MASK;

	pci_enable_busmaster(dev);

	i = PCIR_BAR(0);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &i, RF_ACTIVE);
	if (sc->reg == NULL) {
		device_printf(dev, "unable to map register space\n");
		goto bad;
	}
	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	sc->bufsz = pcm_getbuffersize(dev, 4096, EMU_DEFAULT_BUFSZ, 65536);

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/(1U << 31) - 1, /* can only access 0-2gb */
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/sc->bufsz, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/busdma_lock_mutex,
		/*lockarg*/&Giant, &sc->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	if (emu_init(sc) == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	codec = AC97_CREATE(dev, sc, emu_ac97);
	if (codec == NULL) goto bad;
	gotmic = (ac97_getcaps(codec) & AC97_CAP_MICCHANNEL) ? 1 : 0;
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) goto bad;

	emu_midiattach(sc);

	i = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &i,
	    RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq ||
	    snd_setup_intr(dev, sc->irq, INTR_MPSAFE, emu_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	snprintf(status, SND_STATUSLEN, "at io 0x%jx irq %jd %s",
	    rman_get_start(sc->reg), rman_get_start(sc->irq),
	    PCM_KLDSTRING(snd_emu10k1));

	if (pcm_register(dev, sc, sc->nchans, gotmic ? 3 : 2)) goto bad;
	for (i = 0; i < sc->nchans; i++)
		pcm_addchan(dev, PCMDIR_PLAY, &emupchan_class, sc);
	for (i = 0; i < (gotmic ? 3 : 2); i++)
		pcm_addchan(dev, PCMDIR_REC, &emurchan_class, sc);

	pcm_setstatus(dev, status);

	return 0;

bad:
	if (codec) ac97_destroy(codec);
	if (sc->reg) bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(0), sc->reg);
	if (sc->ih) bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq) bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
	if (sc->parent_dmat) bus_dma_tag_destroy(sc->parent_dmat);
	if (sc->lock) snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);
	return ENXIO;
}