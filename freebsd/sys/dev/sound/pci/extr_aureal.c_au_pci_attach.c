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
struct resource {int dummy; } ;
struct au_info {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/ * sh; int /*<<< orphan*/ * st; int /*<<< orphan*/  unit; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int nummaps; TYPE_1__* map; } ;
struct TYPE_3__ {int ln2size; int type; int base; } ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct au_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AU_BUFFSIZE ; 
 int /*<<< orphan*/  AU_REG_IRQEN ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIR_BAR (int) ; 
 int PCI_MAPPORT ; 
 int PCI_MAXMAPS_0 ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SND_STATUSLEN ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  au_ac97 ; 
 int au_init (int /*<<< orphan*/ ,struct au_info*) ; 
 int /*<<< orphan*/  au_intr ; 
 scalar_t__ au_testirq (struct au_info*) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  auchan_class ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 TYPE_2__* config_id ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct au_info*,int /*<<< orphan*/ ) ; 
 struct au_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct au_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct au_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  snd_aureal ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct au_info*,void**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unit ; 

__attribute__((used)) static int
au_pci_attach(device_t dev)
{
	struct au_info *au;
	int		type[10];
	int		regid[10];
	struct resource *reg[10];
	int		i, j, mapped = 0;
	int		irqid;
	struct resource *irq;
	void		*ih;
	struct ac97_info *codec;
	char 		status[SND_STATUSLEN];

	au = malloc(sizeof(*au), M_DEVBUF, M_WAITOK | M_ZERO);
	au->unit = device_get_unit(dev);

	pci_enable_busmaster(dev);

	irq = NULL;
	ih = NULL;
	j=0;
	/* XXX dfr: is this strictly necessary? */
	for (i=0; i<PCI_MAXMAPS_0; i++) {
#if 0
		/* Slapped wrist: config_id and map are private structures */
		if (bootverbose) {
			printf("pcm%d: map %d - allocating ", unit, i+1);
			printf("0x%x bytes of ", 1<<config_id->map[i].ln2size);
			printf("%s space ", (config_id->map[i].type & PCI_MAPPORT)?
					    "io" : "memory");
			printf("at 0x%x...", config_id->map[i].base);
		}
#endif
		regid[j] = PCIR_BAR(i);
		type[j] = SYS_RES_MEMORY;
		reg[j] = bus_alloc_resource_any(dev, type[j], &regid[j],
						RF_ACTIVE);
		if (!reg[j]) {
			type[j] = SYS_RES_IOPORT;
			reg[j] = bus_alloc_resource_any(dev, type[j], 
							&regid[j], RF_ACTIVE);
		}
		if (reg[j]) {
			au->st[i] = rman_get_bustag(reg[j]);
			au->sh[i] = rman_get_bushandle(reg[j]);
			mapped++;
		}
#if 0
		if (bootverbose) printf("%s\n", mapped? "ok" : "failed");
#endif
		if (mapped) j++;
		if (j == 10) {
			/* XXX */
			device_printf(dev, "too many resources");
			goto bad;
		}
	}

#if 0
	if (j < config_id->nummaps) {
		printf("pcm%d: unable to map a required resource\n", unit);
		free(au, M_DEVBUF);
		return;
	}
#endif

	au_wr(au, 0, AU_REG_IRQEN, 0, 4);

	irqid = 0;
	irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &irqid,
				     RF_ACTIVE | RF_SHAREABLE);
	if (!irq || snd_setup_intr(dev, irq, 0, au_intr, au, &ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	if (au_testirq(au)) device_printf(dev, "irq test failed\n");

	if (au_init(dev, au) == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	codec = AC97_CREATE(dev, au, au_ac97);
	if (codec == NULL) goto bad;
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) goto bad;

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev), /*alignment*/2,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/AU_BUFFSIZE, /*nsegments*/1, /*maxsegz*/0x3ffff,
		/*flags*/0, /*lockfunc*/busdma_lock_mutex,
		/*lockarg*/&Giant, &au->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	snprintf(status, SND_STATUSLEN, "at %s 0x%jx irq %jd %s",
		 (type[0] == SYS_RES_IOPORT)? "io" : "memory",
		 rman_get_start(reg[0]), rman_get_start(irq),PCM_KLDSTRING(snd_aureal));

	if (pcm_register(dev, au, 1, 1)) goto bad;
	/* pcm_addchan(dev, PCMDIR_REC, &au_chantemplate, au); */
	pcm_addchan(dev, PCMDIR_PLAY, &auchan_class, au);
	pcm_setstatus(dev, status);

	return 0;

 bad:
	if (au) free(au, M_DEVBUF);
	for (i = 0; i < j; i++)
		bus_release_resource(dev, type[i], regid[i], reg[i]);
	if (ih) bus_teardown_intr(dev, irq, ih);
	if (irq) bus_release_resource(dev, SYS_RES_IRQ, irqid, irq);
	return ENXIO;
}