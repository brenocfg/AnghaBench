#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ich_func ) (struct sc_info*) ;struct sc_info* ich_arg; } ;
struct sc_info {scalar_t__ vendor; scalar_t__ devid; int swap_reg; int sample_size; int flags; int bufsz; int blkcnt; int hasmic; int hasvra; int hasvrm; int dtbl_size; scalar_t__ ich_lock; scalar_t__ dmat; scalar_t__ chan_dmat; scalar_t__ dtmap; scalar_t__ dtbl; void* nabmbar; scalar_t__ nabmbarid; int /*<<< orphan*/  regtype; void* nambar; scalar_t__ nambarid; void* irq; scalar_t__ irqid; scalar_t__ ih; int /*<<< orphan*/ * codec; TYPE_1__ intrhook; void* nabmbarh; void* nabmbart; void* nambarh; void* nambart; int /*<<< orphan*/  dev; } ;
struct ich_desc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AC97_CAP_MICCHANNEL ; 
 int /*<<< orphan*/ * AC97_CREATE (int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ AC97_EXTCAP_VRA ; 
 scalar_t__ AC97_EXTCAP_VRM ; 
 int AC97_F_EAPD_INV ; 
 int BUS_DMA_NOCACHE ; 
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int ICH_CALIBRATE_DONE ; 
 void* ICH_DEFAULT_BLKCNT ; 
 int /*<<< orphan*/  ICH_DEFAULT_BUFSZ ; 
 int ICH_DMA_NOCACHE ; 
 int ICH_DTBL_LENGTH ; 
 int ICH_FIXED_RATE ; 
 int ICH_HIGH_LATENCY ; 
 int /*<<< orphan*/  ICH_LEGACY_ENABLE ; 
 void* ICH_MAX_BLKCNT ; 
 int /*<<< orphan*/  ICH_MAX_BUFSZ ; 
 void* ICH_MIN_BLKCNT ; 
 int ICH_MIN_BLKSZ ; 
 int /*<<< orphan*/  ICH_MIN_BUFSZ ; 
 scalar_t__ INTEL_6300ESB ; 
 scalar_t__ INTEL_82440MX ; 
 scalar_t__ INTEL_82801DB ; 
 scalar_t__ INTEL_82801EB ; 
 scalar_t__ INTEL_82801FB ; 
 scalar_t__ INTEL_82801GB ; 
 scalar_t__ INTEL_VENDORID ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCIR_ICH_LEGACY ; 
 scalar_t__ PCIR_MBBAR ; 
 scalar_t__ PCIR_MMBAR ; 
 scalar_t__ PCIR_NABMBAR ; 
 scalar_t__ PCIR_NAMBAR ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ SIS_7012 ; 
 scalar_t__ SIS_VENDORID ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ac97_destroy (int /*<<< orphan*/ *) ; 
 int ac97_getcaps (int /*<<< orphan*/ *) ; 
 scalar_t__ ac97_getextcaps (int /*<<< orphan*/ *) ; 
 int ac97_getflags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  ac97_setextmode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ac97_setflags (int /*<<< orphan*/ *,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 scalar_t__ bus_dmamap_load (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,scalar_t__) ; 
 scalar_t__ bus_dmamem_alloc (scalar_t__,void**,int,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ cold ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ich_ac97 ; 
 int /*<<< orphan*/  ich_calibrate (struct sc_info*) ; 
 scalar_t__ ich_init (struct sc_info*) ; 
 int /*<<< orphan*/  ich_initsys (struct sc_info*) ; 
 int /*<<< orphan*/  ich_intr ; 
 int /*<<< orphan*/  ich_setmap ; 
 int /*<<< orphan*/  ich_setstatus (struct sc_info*) ; 
 int /*<<< orphan*/  ichchan_class ; 
 struct sc_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_info*) ; 
 int pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct sc_info*,int,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 void* rman_get_bushandle (void*) ; 
 void* rman_get_bustag (void*) ; 
 scalar_t__ snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,scalar_t__*) ; 

__attribute__((used)) static int
ich_pci_attach(device_t dev)
{
	uint32_t		subdev;
	uint16_t		extcaps;
	uint16_t		devid, vendor;
	struct sc_info 		*sc;
	int			i;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->ich_lock = snd_mtxcreate(device_get_nameunit(dev), "snd_ich softc");
	sc->dev = dev;

	vendor = sc->vendor = pci_get_vendor(dev);
	devid = sc->devid = pci_get_device(dev);
	subdev = (pci_get_subdevice(dev) << 16) | pci_get_subvendor(dev);
	/*
	 * The SiS 7012 register set isn't quite like the standard ich.
	 * There really should be a general "quirks" mechanism.
	 */
	if (vendor == SIS_VENDORID && devid == SIS_7012) {
		sc->swap_reg = 1;
		sc->sample_size = 1;
	} else {
		sc->swap_reg = 0;
		sc->sample_size = 2;
	}

	/*
	 * Intel 440MX Errata #36
	 * - AC97 Soft Audio and Soft Modem Master Abort Errata
	 *
	 * http://www.intel.com/design/chipsets/specupdt/245051.htm
	 */
	if (vendor == INTEL_VENDORID && devid == INTEL_82440MX)
		sc->flags |= ICH_DMA_NOCACHE;

	/*
	 * Enable bus master. On ich4/5 this may prevent the detection of
	 * the primary codec becoming ready in ich_init().
	 */
	pci_enable_busmaster(dev);

	/*
	 * By default, ich4 has NAMBAR and NABMBAR i/o spaces as
	 * read-only.  Need to enable "legacy support", by poking into
	 * pci config space.  The driver should use MMBAR and MBBAR,
	 * but doing so will mess things up here.  ich4 has enough new
	 * features it warrants it's own driver. 
	 */
	if (vendor == INTEL_VENDORID && (devid == INTEL_82801DB ||
	    devid == INTEL_82801EB || devid == INTEL_6300ESB ||
	    devid == INTEL_82801FB || devid == INTEL_82801GB)) {
		sc->nambarid = PCIR_MMBAR;
		sc->nabmbarid = PCIR_MBBAR;
		sc->regtype = SYS_RES_MEMORY;
		pci_write_config(dev, PCIR_ICH_LEGACY, ICH_LEGACY_ENABLE, 1);
	} else {
		sc->nambarid = PCIR_NAMBAR;
		sc->nabmbarid = PCIR_NABMBAR;
		sc->regtype = SYS_RES_IOPORT;
	}

	sc->nambar = bus_alloc_resource_any(dev, sc->regtype, 
		&sc->nambarid, RF_ACTIVE);
	sc->nabmbar = bus_alloc_resource_any(dev, sc->regtype, 
		&sc->nabmbarid, RF_ACTIVE);

	if (!sc->nambar || !sc->nabmbar) {
		device_printf(dev, "unable to map IO port space\n");
		goto bad;
	}

	sc->nambart = rman_get_bustag(sc->nambar);
	sc->nambarh = rman_get_bushandle(sc->nambar);
	sc->nabmbart = rman_get_bustag(sc->nabmbar);
	sc->nabmbarh = rman_get_bushandle(sc->nabmbar);

	sc->bufsz = pcm_getbuffersize(dev,
	    ICH_MIN_BUFSZ, ICH_DEFAULT_BUFSZ, ICH_MAX_BUFSZ);

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "blocksize", &i) == 0 && i > 0) {
		sc->blkcnt = sc->bufsz / i;
		i = 0;
		while (sc->blkcnt >> i)
			i++;
		sc->blkcnt = 1 << (i - 1);
		if (sc->blkcnt < ICH_MIN_BLKCNT)
			sc->blkcnt = ICH_MIN_BLKCNT;
		else if (sc->blkcnt > ICH_MAX_BLKCNT)
			sc->blkcnt = ICH_MAX_BLKCNT;
	} else
		sc->blkcnt = ICH_DEFAULT_BLKCNT;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "highlatency", &i) == 0 && i != 0) {
		sc->flags |= ICH_HIGH_LATENCY;
		sc->blkcnt = ICH_MIN_BLKCNT;
	}

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "fixedrate", &i) == 0 && i != 0)
		sc->flags |= ICH_FIXED_RATE;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "micchannel_enabled", &i) == 0 && i != 0)
		sc->hasmic = 1;

	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (!sc->irq || snd_setup_intr(dev, sc->irq, INTR_MPSAFE, ich_intr,
	    sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}

	if (ich_init(sc)) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}

	sc->codec = AC97_CREATE(dev, sc, ich_ac97);
	if (sc->codec == NULL)
		goto bad;

	/*
	 * Turn on inverted external amplifier sense flags for few
	 * 'special' boards.
	 */
	switch (subdev) {
	case 0x202f161f:	/* Gateway 7326GZ */
	case 0x203a161f:	/* Gateway 4028GZ */
	case 0x203e161f:	/* Gateway 3520GZ/M210 */
	case 0x204c161f:	/* Kvazar-Micro Senator 3592XT */
	case 0x8144104d:	/* Sony VAIO PCG-TR* */
	case 0x8197104d:	/* Sony S1XP */
	case 0x81c0104d:	/* Sony VAIO type T */
	case 0x81c5104d:	/* Sony VAIO VGN B1VP/B1XP */
	case 0x3089103c:	/* Compaq Presario B3800 */
	case 0x309a103c:	/* HP Compaq nx4300 */
	case 0x82131033:	/* NEC VersaPro VJ10F/BH */
	case 0x82be1033:	/* NEC VersaPro VJ12F/CH */
		ac97_setflags(sc->codec, ac97_getflags(sc->codec) | AC97_F_EAPD_INV);
		break;
	default:
		break;
	}

	mixer_init(dev, ac97_getmixerclass(), sc->codec);

	/* check and set VRA function */
	extcaps = ac97_getextcaps(sc->codec);
	sc->hasvra = extcaps & AC97_EXTCAP_VRA;
	sc->hasvrm = extcaps & AC97_EXTCAP_VRM;
	sc->hasmic = (sc->hasmic != 0 &&
	    (ac97_getcaps(sc->codec) & AC97_CAP_MICCHANNEL)) ? 1 : 0;
	ac97_setextmode(sc->codec, sc->hasvra | sc->hasvrm);

	sc->dtbl_size = sizeof(struct ich_desc) * ICH_DTBL_LENGTH *
	    ((sc->hasmic) ? 3 : 2);

	/* BDL tag */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 8, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    sc->dtbl_size, 1, 0x3ffff, 0, NULL, NULL, &sc->dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	/* PCM channel tag */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), ICH_MIN_BLKSZ, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    sc->bufsz, 1, 0x3ffff, 0, NULL, NULL, &sc->chan_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}

	if (bus_dmamem_alloc(sc->dmat, (void **)&sc->dtbl, BUS_DMA_NOWAIT |
	    ((sc->flags & ICH_DMA_NOCACHE) ? BUS_DMA_NOCACHE : 0),
	    &sc->dtmap))
		goto bad;

	if (bus_dmamap_load(sc->dmat, sc->dtmap, sc->dtbl, sc->dtbl_size,
	    ich_setmap, sc, 0))
		goto bad;

	if (pcm_register(dev, sc, 1, (sc->hasmic) ? 2 : 1))
		goto bad;

	pcm_addchan(dev, PCMDIR_PLAY, &ichchan_class, sc);		/* play */
	pcm_addchan(dev, PCMDIR_REC, &ichchan_class, sc);		/* record */
	if (sc->hasmic)
		pcm_addchan(dev, PCMDIR_REC, &ichchan_class, sc);	/* record mic */

	if (sc->flags & ICH_FIXED_RATE) {
		sc->flags |= ICH_CALIBRATE_DONE;
		ich_setstatus(sc);
	} else {
		ich_initsys(sc);

		sc->intrhook.ich_func = ich_calibrate;
		sc->intrhook.ich_arg = sc;
		if (cold == 0 ||
		    config_intrhook_establish(&sc->intrhook) != 0) {
			sc->intrhook.ich_func = NULL;
			ich_calibrate(sc);
		}
	}

	return (0);

bad:
	if (sc->codec)
		ac97_destroy(sc->codec);
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if (sc->nambar)
		bus_release_resource(dev, sc->regtype,
		    sc->nambarid, sc->nambar);
	if (sc->nabmbar)
		bus_release_resource(dev, sc->regtype,
		    sc->nabmbarid, sc->nabmbar);
	if (sc->dtmap)
		bus_dmamap_unload(sc->dmat, sc->dtmap);
	if (sc->dtbl)
		bus_dmamem_free(sc->dmat, sc->dtbl, sc->dtmap);
	if (sc->chan_dmat)
		bus_dma_tag_destroy(sc->chan_dmat);
	if (sc->dmat)
		bus_dma_tag_destroy(sc->dmat);
	if (sc->ich_lock)
		snd_mtxfree(sc->ich_lock);
	free(sc, M_DEVBUF);
	return (ENXIO);
}