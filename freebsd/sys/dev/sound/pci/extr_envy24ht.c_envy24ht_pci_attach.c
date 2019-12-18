#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int adcn; int dacn; scalar_t__ lock; scalar_t__ mt; int /*<<< orphan*/  mtid; scalar_t__ cs; int /*<<< orphan*/  csid; TYPE_2__* cfg; int /*<<< orphan*/ * dac; int /*<<< orphan*/ * adc; scalar_t__ dmat; scalar_t__ irq; int /*<<< orphan*/  irqid; scalar_t__ ih; scalar_t__ chnum; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_ENVY24HT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bzero (struct sc_info*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int envy24ht_alloc_resource (struct sc_info*) ; 
 int /*<<< orphan*/  envy24ht_cfgfree (TYPE_2__*) ; 
 int /*<<< orphan*/  envy24ht_dmafree (struct sc_info*) ; 
 int envy24ht_init (struct sc_info*) ; 
 int /*<<< orphan*/  envy24htchan_class ; 
 int /*<<< orphan*/  envy24htmixer_class ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rman_get_end (scalar_t__) ; 
 scalar_t__ rman_get_start (scalar_t__) ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envy24ht_pci_attach(device_t dev)
{
	struct sc_info 		*sc;
	char 			status[SND_STATUSLEN];
	int			err = 0;
	int			i;

#if(0)
	device_printf(dev, "envy24ht_pci_attach()\n");
#endif
	/* get sc_info data area */
	if ((sc = malloc(sizeof(*sc), M_ENVY24HT, M_NOWAIT)) == NULL) {
		device_printf(dev, "cannot allocate softc\n");
		return ENXIO;
	}

	bzero(sc, sizeof(*sc));
	sc->lock = snd_mtxcreate(device_get_nameunit(dev),
	    "snd_envy24ht softc");
	sc->dev = dev;

	/* initialize PCI interface */
	pci_enable_busmaster(dev);

	/* allocate resources */
	err = envy24ht_alloc_resource(sc);
	if (err) {
		device_printf(dev, "unable to allocate system resources\n");
		goto bad;
	}

	/* initialize card */
	err = envy24ht_init(sc);
	if (err) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	/* set multi track mixer */
	mixer_init(dev, &envy24htmixer_class, sc);

	/* set channel information */
	/* err = pcm_register(dev, sc, 5, 2 + sc->adcn); */
	err = pcm_register(dev, sc, 1, 2 + sc->adcn);
	if (err)
		goto bad;
	sc->chnum = 0;
	/* for (i = 0; i < 5; i++) { */
		pcm_addchan(dev, PCMDIR_PLAY, &envy24htchan_class, sc);
		sc->chnum++;
	/* } */
	for (i = 0; i < 2 + sc->adcn; i++) {
		pcm_addchan(dev, PCMDIR_REC, &envy24htchan_class, sc);
		sc->chnum++;
	}

	/* set status iformation */
	snprintf(status, SND_STATUSLEN,
	    "at io 0x%jx:%jd,0x%jx:%jd irq %jd",
	    rman_get_start(sc->cs),
	    rman_get_end(sc->cs) - rman_get_start(sc->cs) + 1,
	    rman_get_start(sc->mt),
	    rman_get_end(sc->mt) - rman_get_start(sc->mt) + 1,
	    rman_get_start(sc->irq));
	pcm_setstatus(dev, status);

	return 0;

bad:
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	envy24ht_dmafree(sc);
	if (sc->dmat)
		bus_dma_tag_destroy(sc->dmat);
        if (sc->cfg->codec->destroy != NULL) {
                for (i = 0; i < sc->adcn; i++)
                        sc->cfg->codec->destroy(sc->adc[i]);
                for (i = 0; i < sc->dacn; i++)
                        sc->cfg->codec->destroy(sc->dac[i]);
        }
	envy24ht_cfgfree(sc->cfg);
	if (sc->cs)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->csid, sc->cs);
	if (sc->mt)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->mtid, sc->mt);
	if (sc->lock)
		snd_mtxfree(sc->lock);
	free(sc, M_ENVY24HT);
	return err;
}