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
struct sc_info {scalar_t__ regtype; scalar_t__ parent_dmat; int /*<<< orphan*/ * irq; void* irqid; scalar_t__ ih; int /*<<< orphan*/ * mem; void* memid; int /*<<< orphan*/ * reg; void* regid; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CS4281_DEFAULT_BUFSZ ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* PCIR_BAR (int) ; 
 scalar_t__ PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 scalar_t__ SYS_RES_IOPORT ; 
 scalar_t__ SYS_RES_IRQ ; 
 scalar_t__ SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,scalar_t__,void**,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  cs4281_ac97 ; 
 int cs4281_init (struct sc_info*) ; 
 int /*<<< orphan*/  cs4281_intr ; 
 int /*<<< orphan*/  cs4281_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281chan_class ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cs4281 ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4281_pci_attach(device_t dev)
{
    struct sc_info *sc;
    struct ac97_info *codec = NULL;
    char status[SND_STATUSLEN];

    sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
    sc->dev = dev;
    sc->type = pci_get_devid(dev);

    pci_enable_busmaster(dev);

    if (pci_get_powerstate(dev) != PCI_POWERSTATE_D0) {
	/* Reset the power state. */
	device_printf(dev, "chip is in D%d power mode "
		      "-- setting to D0\n", pci_get_powerstate(dev));

	pci_set_powerstate(dev, PCI_POWERSTATE_D0);
    }

    sc->regid   = PCIR_BAR(0);
    sc->regtype = SYS_RES_MEMORY;
    sc->reg = bus_alloc_resource_any(dev, sc->regtype, &sc->regid, RF_ACTIVE);
    if (!sc->reg) {
	sc->regtype = SYS_RES_IOPORT;
	sc->reg = bus_alloc_resource_any(dev, sc->regtype, &sc->regid,
					 RF_ACTIVE);
	if (!sc->reg) {
	    device_printf(dev, "unable to allocate register space\n");
	    goto bad;
	}
    }
    sc->st = rman_get_bustag(sc->reg);
    sc->sh = rman_get_bushandle(sc->reg);

    sc->memid = PCIR_BAR(1);
    sc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->memid,
				     RF_ACTIVE);
    if (sc->mem == NULL) {
	device_printf(dev, "unable to allocate fifo space\n");
	goto bad;
    }

    sc->irqid = 0;
    sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
				     RF_ACTIVE | RF_SHAREABLE);
    if (!sc->irq) {
	device_printf(dev, "unable to allocate interrupt\n");
	goto bad;
    }

    if (snd_setup_intr(dev, sc->irq, 0, cs4281_intr, sc, &sc->ih)) {
	device_printf(dev, "unable to setup interrupt\n");
	goto bad;
    }

    sc->bufsz = pcm_getbuffersize(dev, 4096, CS4281_DEFAULT_BUFSZ, 65536);

    if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
			   /*boundary*/0,
			   /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			   /*highaddr*/BUS_SPACE_MAXADDR,
			   /*filter*/NULL, /*filterarg*/NULL,
			   /*maxsize*/sc->bufsz, /*nsegments*/1,
			   /*maxsegz*/0x3ffff,
			   /*flags*/0, /*lockfunc*/busdma_lock_mutex,
			   /*lockarg*/&Giant, &sc->parent_dmat) != 0) {
	device_printf(dev, "unable to create dma tag\n");
	goto bad;
    }

    /* power up */
    cs4281_power(sc, 0);

    /* init chip */
    if (cs4281_init(sc) == -1) {
	device_printf(dev, "unable to initialize the card\n");
	goto bad;
    }

    /* create/init mixer */
    codec = AC97_CREATE(dev, sc, cs4281_ac97);
    if (codec == NULL)
        goto bad;

    mixer_init(dev, ac97_getmixerclass(), codec);

    if (pcm_register(dev, sc, 1, 1))
	goto bad;

    pcm_addchan(dev, PCMDIR_PLAY, &cs4281chan_class, sc);
    pcm_addchan(dev, PCMDIR_REC, &cs4281chan_class, sc);

    snprintf(status, SND_STATUSLEN, "at %s 0x%jx irq %jd %s",
	     (sc->regtype == SYS_RES_IOPORT)? "io" : "memory",
	     rman_get_start(sc->reg), rman_get_start(sc->irq),PCM_KLDSTRING(snd_cs4281));
    pcm_setstatus(dev, status);

    return 0;

 bad:
    if (codec)
	ac97_destroy(codec);
    if (sc->reg)
	bus_release_resource(dev, sc->regtype, sc->regid, sc->reg);
    if (sc->mem)
	bus_release_resource(dev, SYS_RES_MEMORY, sc->memid, sc->mem);
    if (sc->ih)
	bus_teardown_intr(dev, sc->irq, sc->ih);
    if (sc->irq)
	bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
    if (sc->parent_dmat)
	bus_dma_tag_destroy(sc->parent_dmat);
    free(sc, M_DEVBUF);

    return ENXIO;
}