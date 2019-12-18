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
struct tr_info {int type; scalar_t__ lock; scalar_t__ parent_dmat; void* irq; scalar_t__ irqid; scalar_t__ ih; void* reg; scalar_t__ regid; int /*<<< orphan*/  regtype; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  hwchns; scalar_t__ playchns; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  rev; } ;
struct ac97_info {int dummy; } ;
typedef  struct tr_info device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (struct tr_info,struct tr_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_BUFSZ ; 
 int /*<<< orphan*/  ALI_MAXADDR ; 
 int /*<<< orphan*/  ALI_MAXHWCH ; 
 int ALI_MAXPLAYCH ; 
#define  ALI_PCI_ID 128 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
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
 int /*<<< orphan*/  TR_BUFALGN ; 
 int /*<<< orphan*/  TR_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  TR_MAXADDR ; 
 int /*<<< orphan*/  TR_MAXHWCH ; 
 int TR_MAXPLAYCH ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (struct tr_info,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (struct tr_info) ; 
 int /*<<< orphan*/  bus_release_resource (struct tr_info,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (struct tr_info,void*,scalar_t__) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,struct tr_info**,int*) ; 
 int /*<<< orphan*/  device_get_name (struct tr_info) ; 
 int /*<<< orphan*/  device_get_nameunit (struct tr_info) ; 
 int /*<<< orphan*/  device_get_parent (struct tr_info) ; 
 int /*<<< orphan*/  device_get_unit (struct tr_info) ; 
 int /*<<< orphan*/  device_printf (struct tr_info,char*,...) ; 
 int /*<<< orphan*/  free (struct tr_info*,int /*<<< orphan*/ ) ; 
 struct tr_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (struct tr_info,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (struct tr_info) ; 
 int pci_get_devid (struct tr_info) ; 
 int /*<<< orphan*/  pci_get_revid (struct tr_info) ; 
 int pci_read_config (struct tr_info,int,int) ; 
 int /*<<< orphan*/  pci_write_config (struct tr_info,int,int,int) ; 
 int /*<<< orphan*/  pcm_addchan (struct tr_info,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tr_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (struct tr_info,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcm_register (struct tr_info,struct tr_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (struct tr_info,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (struct tr_info,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tr_info*,scalar_t__*) ; 
 int /*<<< orphan*/  snd_t4dwave ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_ac97 ; 
 int tr_init (struct tr_info*) ; 
 int /*<<< orphan*/  tr_intr ; 
 int /*<<< orphan*/  trpchan_class ; 
 int /*<<< orphan*/  trrchan_class ; 

__attribute__((used)) static int
tr_pci_attach(device_t dev)
{
	struct tr_info *tr;
	struct ac97_info *codec = NULL;
	bus_addr_t	lowaddr;
	int		i, dacn;
	char 		status[SND_STATUSLEN];
#ifdef __sparc64__
	device_t	*children;
	int		nchildren;
	u_int32_t	data;
#endif

	tr = malloc(sizeof(*tr), M_DEVBUF, M_WAITOK | M_ZERO);
	tr->type = pci_get_devid(dev);
	tr->rev = pci_get_revid(dev);
	tr->lock = snd_mtxcreate(device_get_nameunit(dev), "snd_t4dwave softc");

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "dac", &i) == 0) {
	    	if (i < 1)
			dacn = 1;
		else if (i > TR_MAXPLAYCH)
			dacn = TR_MAXPLAYCH;
		else
			dacn = i;
	} else {
		switch (tr->type) {
		case ALI_PCI_ID:
			dacn = ALI_MAXPLAYCH;
			break;
		default:
			dacn = TR_MAXPLAYCH;
			break;
		}
	}

	pci_enable_busmaster(dev);

	tr->regid = PCIR_BAR(0);
	tr->regtype = SYS_RES_IOPORT;
	tr->reg = bus_alloc_resource_any(dev, tr->regtype, &tr->regid,
		RF_ACTIVE);
	if (tr->reg) {
		tr->st = rman_get_bustag(tr->reg);
		tr->sh = rman_get_bushandle(tr->reg);
	} else {
		device_printf(dev, "unable to map register space\n");
		goto bad;
	}

	if (tr_init(tr) == -1) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}
	tr->playchns = 0;

	codec = AC97_CREATE(dev, tr, tr_ac97);
	if (codec == NULL) goto bad;
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) goto bad;

	tr->irqid = 0;
	tr->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &tr->irqid,
				 RF_ACTIVE | RF_SHAREABLE);
	if (!tr->irq || snd_setup_intr(dev, tr->irq, 0, tr_intr, tr, &tr->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	if (tr->type == ALI_PCI_ID) {
		/*
		 * The M5451 generates 31 bit of DMA and in order to do
		 * 32-bit DMA, the 31st bit can be set via its accompanying
		 * ISA bridge.  Note that we can't predict whether bus_dma(9)
		 * will actually supply us with a 32-bit buffer and even when
		 * using a low address of BUS_SPACE_MAXADDR_32BIT for both
		 * we might end up with the play buffer being in the 32-bit
		 * range while the record buffer isn't or vice versa. So we
		 * limit enabling the 31st bit to sparc64, where the IOMMU
		 * guarantees that we're using a 32-bit address (and in turn
		 * requires it).
		 */
		lowaddr = ALI_MAXADDR;
#ifdef __sparc64__
		if (device_get_children(device_get_parent(dev), &children,
		    &nchildren) == 0) {
			for (i = 0; i < nchildren; i++) {
				if (pci_get_devid(children[i]) == 0x153310b9) {
					lowaddr = BUS_SPACE_MAXADDR_32BIT;
					data = pci_read_config(children[i],
					    0x7e, 1);
					if (bootverbose)
						device_printf(dev,
						    "M1533 0x7e: 0x%x -> ",
						    data);
					data |= 0x1;
					if (bootverbose)
						printf("0x%x\n", data);
					pci_write_config(children[i], 0x7e,
					    data, 1);
					break;
				}
			}
		}
		free(children, M_TEMP);
#endif
		tr->hwchns = ALI_MAXHWCH;
		tr->bufsz = ALI_BUFSZ;
	} else {
		lowaddr = TR_MAXADDR;
		tr->hwchns = TR_MAXHWCH;
		tr->bufsz = pcm_getbuffersize(dev, 4096, TR_DEFAULT_BUFSZ,
		    65536);
	}

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev),
		/*alignment*/TR_BUFALGN,
		/*boundary*/0,
		/*lowaddr*/lowaddr,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL, /*filterarg*/NULL,
		/*maxsize*/tr->bufsz, /*nsegments*/1, /*maxsegz*/tr->bufsz,
		/*flags*/0, /*lockfunc*/busdma_lock_mutex,
		/*lockarg*/&Giant, &tr->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	snprintf(status, 64, "at io 0x%jx irq %jd %s",
		 rman_get_start(tr->reg), rman_get_start(tr->irq),PCM_KLDSTRING(snd_t4dwave));

	if (pcm_register(dev, tr, dacn, 1))
		goto bad;
	pcm_addchan(dev, PCMDIR_REC, &trrchan_class, tr);
	for (i = 0; i < dacn; i++)
		pcm_addchan(dev, PCMDIR_PLAY, &trpchan_class, tr);
	pcm_setstatus(dev, status);

	return 0;

bad:
	if (codec) ac97_destroy(codec);
	if (tr->reg) bus_release_resource(dev, tr->regtype, tr->regid, tr->reg);
	if (tr->ih) bus_teardown_intr(dev, tr->irq, tr->ih);
	if (tr->irq) bus_release_resource(dev, SYS_RES_IRQ, tr->irqid, tr->irq);
	if (tr->parent_dmat) bus_dma_tag_destroy(tr->parent_dmat);
	if (tr->lock) snd_mtxfree(tr->lock);
	free(tr, M_DEVBUF);
	return ENXIO;
}