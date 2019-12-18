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
struct sc_info {void* irq; void* irqid; scalar_t__ ih; void* reg; void* regid; void* buf; void* bufid; int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  nm_ac97 ; 
 int nm_init (struct sc_info*) ; 
 int /*<<< orphan*/  nm_intr ; 
 int /*<<< orphan*/  nmchan_class ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 int /*<<< orphan*/  snd_neomagic ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nm_pci_attach(device_t dev)
{
	struct sc_info *sc;
	struct ac97_info *codec = NULL;
	char 		status[SND_STATUSLEN];

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->dev = dev;
	sc->type = pci_get_devid(dev);

	pci_enable_busmaster(dev);

	sc->bufid = PCIR_BAR(0);
	sc->buf = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->bufid,
					 RF_ACTIVE);
	sc->regid = PCIR_BAR(1);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->regid,
					 RF_ACTIVE);

	if (!sc->buf || !sc->reg) {
		device_printf(dev, "unable to map register space\n");
		goto bad;
	}

	if (nm_init(sc) == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	codec = AC97_CREATE(dev, sc, nm_ac97);
	if (codec == NULL) goto bad;
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) goto bad;

	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					 RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq || snd_setup_intr(dev, sc->irq, 0, nm_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	snprintf(status, SND_STATUSLEN, "at memory 0x%jx, 0x%jx irq %jd %s",
		 rman_get_start(sc->buf), rman_get_start(sc->reg),
		 rman_get_start(sc->irq),PCM_KLDSTRING(snd_neomagic));

	if (pcm_register(dev, sc, 1, 1)) goto bad;
	pcm_addchan(dev, PCMDIR_REC, &nmchan_class, sc);
	pcm_addchan(dev, PCMDIR_PLAY, &nmchan_class, sc);
	pcm_setstatus(dev, status);

	return 0;

bad:
	if (codec) ac97_destroy(codec);
	if (sc->buf) bus_release_resource(dev, SYS_RES_MEMORY, sc->bufid, sc->buf);
	if (sc->reg) bus_release_resource(dev, SYS_RES_MEMORY, sc->regid, sc->reg);
	if (sc->ih) bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq) bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	free(sc, M_DEVBUF);
	return ENXIO;
}