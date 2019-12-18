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
struct fm801_info {scalar_t__ regtype; scalar_t__ parent_dmat; void* irq; scalar_t__ irqid; scalar_t__ ih; void* reg; scalar_t__ regid; int /*<<< orphan*/  radio; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  type; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct fm801_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  FM801_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  FM801_MAXPLAYCH ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PCIR_BAR (int) ; 
 int PCI_MAXMAPS_0 ; 
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
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fm801_ac97 ; 
 int /*<<< orphan*/  fm801_init (struct fm801_info*) ; 
 int /*<<< orphan*/  fm801_intr ; 
 int /*<<< orphan*/  fm801ch_class ; 
 int /*<<< orphan*/  free (struct fm801_info*,int /*<<< orphan*/ ) ; 
 struct fm801_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fm801_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct fm801_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 int /*<<< orphan*/  snd_fm801 ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fm801_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fm801_pci_attach(device_t dev)
{
	struct ac97_info 	*codec = NULL;
	struct fm801_info 	*fm801;
	int 			i;
	int 			mapped = 0;
	char 			status[SND_STATUSLEN];

	fm801 = malloc(sizeof(*fm801), M_DEVBUF, M_WAITOK | M_ZERO);
	fm801->type = pci_get_devid(dev);

	pci_enable_busmaster(dev);

	for (i = 0; (mapped == 0) && (i < PCI_MAXMAPS_0); i++) {
		fm801->regid = PCIR_BAR(i);
		fm801->regtype = SYS_RES_MEMORY;
		fm801->reg = bus_alloc_resource_any(dev, fm801->regtype,
						    &fm801->regid, RF_ACTIVE);
		if(!fm801->reg)
		{
			fm801->regtype = SYS_RES_IOPORT;
			fm801->reg = bus_alloc_resource_any(dev, 
							    fm801->regtype,
							    &fm801->regid,
							    RF_ACTIVE);
		}

		if(fm801->reg) {
			fm801->st = rman_get_bustag(fm801->reg);
			fm801->sh = rman_get_bushandle(fm801->reg);
			mapped++;
		}
	}

	if (mapped == 0) {
		device_printf(dev, "unable to map register space\n");
		goto oops;
	}

	fm801->bufsz = pcm_getbuffersize(dev, 4096, FM801_DEFAULT_BUFSZ, 65536);

	fm801_init(fm801);

	codec = AC97_CREATE(dev, fm801, fm801_ac97);
	if (codec == NULL) goto oops;

	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) goto oops;

	fm801->irqid = 0;
	fm801->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &fm801->irqid,
					    RF_ACTIVE | RF_SHAREABLE);
	if (!fm801->irq ||
	    snd_setup_intr(dev, fm801->irq, 0, fm801_intr, fm801, &fm801->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto oops;
	}

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/fm801->bufsz, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/busdma_lock_mutex,
		/*lockarg*/&Giant, &fm801->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto oops;
	}

	snprintf(status, 64, "at %s 0x%jx irq %jd %s",
		(fm801->regtype == SYS_RES_IOPORT)? "io" : "memory",
		rman_get_start(fm801->reg), rman_get_start(fm801->irq),PCM_KLDSTRING(snd_fm801));

#define FM801_MAXPLAYCH	1
	if (pcm_register(dev, fm801, FM801_MAXPLAYCH, 1)) goto oops;
	pcm_addchan(dev, PCMDIR_PLAY, &fm801ch_class, fm801);
	pcm_addchan(dev, PCMDIR_REC, &fm801ch_class, fm801);
	pcm_setstatus(dev, status);

	fm801->radio = device_add_child(dev, "radio", -1);
	bus_generic_attach(dev);

	return 0;

oops:
	if (codec) ac97_destroy(codec);
	if (fm801->reg) bus_release_resource(dev, fm801->regtype, fm801->regid, fm801->reg);
	if (fm801->ih) bus_teardown_intr(dev, fm801->irq, fm801->ih);
	if (fm801->irq) bus_release_resource(dev, SYS_RES_IRQ, fm801->irqid, fm801->irq);
	if (fm801->parent_dmat) bus_dma_tag_destroy(fm801->parent_dmat);
	free(fm801, M_DEVBUF);
	return ENXIO;
}