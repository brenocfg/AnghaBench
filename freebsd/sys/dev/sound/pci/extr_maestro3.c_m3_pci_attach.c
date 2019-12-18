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
typedef  int /*<<< orphan*/  u_int16_t ;
struct sc_info {scalar_t__ type; scalar_t__ regtype; scalar_t__ sc_lock; scalar_t__ parent_dmat; void* reg; scalar_t__ regid; void* irq; scalar_t__ irqid; scalar_t__ ih; int /*<<< orphan*/ * savemem; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  delay2; int /*<<< orphan*/  delay1; int /*<<< orphan*/  which; int /*<<< orphan*/  dev; } ;
struct m3_card_type {scalar_t__ pci_id; int /*<<< orphan*/  delay2; int /*<<< orphan*/  delay1; int /*<<< orphan*/  which; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  CALL ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M3_BUFSIZE_DEFAULT ; 
 int /*<<< orphan*/  M3_BUFSIZE_MAX ; 
 int /*<<< orphan*/  M3_BUFSIZE_MIN ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_MAXADDR ; 
 int M3_PCHANS ; 
 int M3_RCHANS ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int REV_B_CODE_MEMORY_LENGTH ; 
 int REV_B_DATA_MEMORY_LENGTH ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 scalar_t__ SYS_RES_IOPORT ; 
 scalar_t__ SYS_RES_IRQ ; 
 scalar_t__ SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct m3_card_type* m3_card_types ; 
 int /*<<< orphan*/  m3_codec ; 
 int /*<<< orphan*/  m3_enable_ints (struct sc_info*) ; 
 int m3_init (struct sc_info*) ; 
 int /*<<< orphan*/  m3_intr ; 
 int /*<<< orphan*/  m3_pch_class ; 
 int /*<<< orphan*/  m3_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_rch_class ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_hwvol_init (int /*<<< orphan*/ ) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 scalar_t__ pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 int /*<<< orphan*/  snd_maestro3 ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_pci_attach(device_t dev)
{
	struct sc_info *sc;
	struct ac97_info *codec = NULL;
	char status[SND_STATUSLEN];
	struct m3_card_type *card;
	int i, len, dacn, adcn;

	M3_DEBUG(CALL, ("m3_pci_attach\n"));

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->dev = dev;
	sc->type = pci_get_devid(dev);
	sc->sc_lock = snd_mtxcreate(device_get_nameunit(dev),
	    "snd_maestro3 softc");
	for (card = m3_card_types ; card->pci_id ; card++) {
		if (sc->type == card->pci_id) {
			sc->which = card->which;
			sc->delay1 = card->delay1;
			sc->delay2 = card->delay2;
			break;
		}
	}

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "dac", &i) == 0) {
	    	if (i < 1)
			dacn = 1;
		else if (i > M3_PCHANS)
			dacn = M3_PCHANS;
		else
			dacn = i;
	} else
		dacn = M3_PCHANS;

	adcn = M3_RCHANS;

	pci_enable_busmaster(dev);

	sc->regid = PCIR_BAR(0);
	sc->regtype = SYS_RES_MEMORY;
	sc->reg = bus_alloc_resource_any(dev, sc->regtype, &sc->regid,
					 RF_ACTIVE);
	if (!sc->reg) {
		sc->regtype = SYS_RES_IOPORT;
		sc->reg = bus_alloc_resource_any(dev, sc->regtype, &sc->regid,
						 RF_ACTIVE);
	}
	if (!sc->reg) {
		device_printf(dev, "unable to allocate register space\n");
		goto bad;
	}
	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					 RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq) {
		device_printf(dev, "unable to allocate interrupt\n");
		goto bad;
	}

	if (snd_setup_intr(dev, sc->irq, INTR_MPSAFE, m3_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to setup interrupt\n");
		goto bad;
	}

	sc->bufsz = pcm_getbuffersize(dev, M3_BUFSIZE_MIN, M3_BUFSIZE_DEFAULT,
	    M3_BUFSIZE_MAX);

	if (bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* parent */
	    2, 0,		/* alignment, boundary */
	    M3_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,	/* highaddr */
	    NULL, NULL,		/* filtfunc, filtfuncarg */
	    sc->bufsz,		/* maxsize */
	    1,			/* nsegments */
	    0x3ffff,		/* maxsegz */
	    0,			/* flags */
	    NULL,		/* lockfunc */
	    NULL,		/* lockfuncarg */
	    &sc->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	M3_LOCK(sc);
	m3_power(sc, 0); /* power up */
	/* init chip */
	i = m3_init(sc);
	M3_UNLOCK(sc);
	if (i == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	/* create/init mixer */
	codec = AC97_CREATE(dev, sc, m3_codec);
	if (codec == NULL) {
		device_printf(dev, "ac97_create error\n");
		goto bad;
	}
	if (mixer_init(dev, ac97_getmixerclass(), codec)) {
		device_printf(dev, "mixer_init error\n");
		goto bad;
	}

	m3_enable_ints(sc);

	if (pcm_register(dev, sc, dacn, adcn)) {
		device_printf(dev, "pcm_register error\n");
		goto bad;
	}
	for (i=0 ; i<dacn ; i++) {
		if (pcm_addchan(dev, PCMDIR_PLAY, &m3_pch_class, sc)) {
			device_printf(dev, "pcm_addchan (play) error\n");
			goto bad;
		}
	}
	for (i=0 ; i<adcn ; i++) {
		if (pcm_addchan(dev, PCMDIR_REC, &m3_rch_class, sc)) {
			device_printf(dev, "pcm_addchan (rec) error\n");
			goto bad;
		}
	}
 	snprintf(status, SND_STATUSLEN, "at %s 0x%jx irq %jd %s",
	    (sc->regtype == SYS_RES_IOPORT)? "io" : "memory",
	    rman_get_start(sc->reg), rman_get_start(sc->irq),
	    PCM_KLDSTRING(snd_maestro3));
	if (pcm_setstatus(dev, status)) {
		device_printf(dev, "attach: pcm_setstatus error\n");
		goto bad;
	}

	mixer_hwvol_init(dev);

	/* Create the buffer for saving the card state during suspend */
	len = sizeof(u_int16_t) * (REV_B_CODE_MEMORY_LENGTH +
	    REV_B_DATA_MEMORY_LENGTH);
	sc->savemem = (u_int16_t*)malloc(len, M_DEVBUF, M_WAITOK | M_ZERO);

	return 0;

 bad:
	if (codec)
		ac97_destroy(codec);
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if (sc->reg)
		bus_release_resource(dev, sc->regtype, sc->regid, sc->reg);
	if (sc->parent_dmat)
		bus_dma_tag_destroy(sc->parent_dmat);
	if (sc->sc_lock)
		snd_mtxfree(sc->sc_lock);
	free(sc, M_DEVBUF);
	return ENXIO;
}