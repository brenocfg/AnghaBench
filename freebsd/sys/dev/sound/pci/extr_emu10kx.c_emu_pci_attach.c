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
struct sndcard_func {struct emu_pcminfo* varinfo; void* func; } ;
struct emu_sc_info {int rev; int has_ac97; int has_51; int has_71; int broken_digital; int is_emu10k1; int is_emu10k2; int is_ca0102; int is_ca0108; int is_cardbus; int opcode_shift; int high_operand_shift; int input_base; int output_base; int efxc_base; int dsp_zero; int num_gprs; int code_size; int mchannel_fx; int num_fxbuses; int num_inputs; int num_outputs; int /*<<< orphan*/  lock; int /*<<< orphan*/  rw; int /*<<< orphan*/ * irq; scalar_t__ ih; int /*<<< orphan*/ * reg; int /*<<< orphan*/ * rm; scalar_t__ cdev; int /*<<< orphan*/ ** midi; int /*<<< orphan*/ ** pcm; scalar_t__ mch_rec; scalar_t__ mch_disabled; TYPE_1__* voice; scalar_t__* timer; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  address_mask; int /*<<< orphan*/  gpr_base; int /*<<< orphan*/  code_base; int /*<<< orphan*/  dev; scalar_t__ enable_ir; int /*<<< orphan*/  type; scalar_t__ dbg_level; int /*<<< orphan*/ * root; int /*<<< orphan*/ * ctx; } ;
struct emu_pcminfo {size_t route; int portnr; int /*<<< orphan*/  port; struct emu_sc_info* card; } ;
struct emu_midiinfo {size_t route; int portnr; int /*<<< orphan*/  port; struct emu_sc_info* card; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int vnum; scalar_t__ end; scalar_t__ start; scalar_t__ speed; scalar_t__ stereo; scalar_t__ b16; scalar_t__ running; scalar_t__ ismaster; scalar_t__ busy; int /*<<< orphan*/ * slave; } ;

/* Variables and functions */
 int BROKEN_DIGITAL ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  EMU_A_FXGPREGBASE ; 
 int /*<<< orphan*/  EMU_A_MICROCODEBASE ; 
 int /*<<< orphan*/  EMU_A_MUDATA1 ; 
 int /*<<< orphan*/  EMU_A_MUDATA2 ; 
 int /*<<< orphan*/  EMU_A_PTR_ADDR_MASK ; 
 int /*<<< orphan*/  EMU_FXGPREGBASE ; 
 int EMU_MAX_IRQ_CONSUMERS ; 
 int /*<<< orphan*/  EMU_MICROCODEBASE ; 
 int /*<<< orphan*/  EMU_PTR_ADDR_MASK ; 
 int ENOMEM ; 
 int ENXIO ; 
 int HAS_51 ; 
 int HAS_71 ; 
 int HAS_AC97 ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_AV ; 
 int IS_CA0102 ; 
 int IS_CA0108 ; 
 int IS_CARDBUS ; 
 int IS_EMU10K1 ; 
 int IS_EMU10K2 ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MUDATA ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int NUM_G ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RANGE (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 size_t RT_CENTER ; 
 int RT_COUNT ; 
 size_t RT_FRONT ; 
 size_t RT_MCHRECORD ; 
 size_t RT_REAR ; 
 size_t RT_SIDE ; 
 size_t RT_SUB ; 
 void* SCF_MIDI ; 
 void* SCF_PCM ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct emu_sc_info*,scalar_t__*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 void* device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct emu_sc_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct sndcard_func*) ; 
 scalar_t__ emu10kx_dev_init (struct emu_sc_info*) ; 
 int /*<<< orphan*/  emu10kx_dev_uninit (struct emu_sc_info*) ; 
 scalar_t__ emu_cardbus_init (struct emu_sc_info*) ; 
 TYPE_2__* emu_cards ; 
 size_t emu_getcard (int /*<<< orphan*/ ) ; 
 scalar_t__ emu_init (struct emu_sc_info*) ; 
 int /*<<< orphan*/  emu_intr ; 
 scalar_t__ emu_rm_init (struct emu_sc_info*) ; 
 int /*<<< orphan*/  emu_rm_uninit (struct emu_sc_info*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (char*,int,char*,scalar_t__*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_pci_attach(device_t dev)
{
	struct sndcard_func *func;
	struct emu_sc_info *sc;
	struct emu_pcminfo *pcminfo;
#if 0
	struct emu_midiinfo *midiinfo;
#endif
	int i;
	int device_flags;
	char status[255];
	int error = ENXIO;
	int unit;

	sc = device_get_softc(dev);
	unit = device_get_unit(dev);

	/* Get configuration */

	sc->ctx = device_get_sysctl_ctx(dev);
	if (sc->ctx == NULL)
		goto bad;
	sc->root = device_get_sysctl_tree(dev);
	if (sc->root == NULL)
		goto bad;

	if (resource_int_value("emu10kx", unit, "multichannel_disabled", &(sc->mch_disabled)))
		RANGE(sc->mch_disabled, 0, 1);
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "multichannel_disabled", CTLFLAG_RD, &(sc->mch_disabled), 0, "Multichannel playback setting");

	if (resource_int_value("emu10kx", unit, "multichannel_recording", &(sc->mch_rec)))
		RANGE(sc->mch_rec, 0, 1);
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "multichannel_recording", CTLFLAG_RD,  &(sc->mch_rec), 0, "Multichannel recording setting");

	if (resource_int_value("emu10kx", unit, "debug", &(sc->dbg_level)))
		RANGE(sc->mch_rec, 0, 2);
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "debug", CTLFLAG_RW, &(sc->dbg_level), 0, "Debug level");

	/* Fill in the softc. */
	mtx_init(&sc->lock, device_get_nameunit(dev), "bridge conf", MTX_DEF);
	mtx_init(&sc->rw, device_get_nameunit(dev), "exclusive io", MTX_DEF);
	sc->dev = dev;
	sc->type = pci_get_devid(dev);
	sc->rev = pci_get_revid(dev);
	sc->enable_ir = 0;
	sc->has_ac97 = 0;
	sc->has_51 = 0;
	sc->has_71 = 0;
	sc->broken_digital = 0;
	sc->is_emu10k1 = 0;
	sc->is_emu10k2 = 0;
	sc->is_ca0102 = 0;
	sc->is_ca0108 = 0;
	sc->is_cardbus = 0;

	device_flags = emu_cards[emu_getcard(dev)].flags;
	if (device_flags & HAS_51)
		sc->has_51 = 1;
	if (device_flags & HAS_71) {
		sc->has_51 = 1;
		sc->has_71 = 1;
	}
	if (device_flags & IS_EMU10K1)
		sc->is_emu10k1 = 1;
	if (device_flags & IS_EMU10K2)
		sc->is_emu10k2 = 1;
	if (device_flags & IS_CA0102)
		sc->is_ca0102 = 1;
	if (device_flags & IS_CA0108)
		sc->is_ca0108 = 1;
	if ((sc->is_emu10k2) && (sc->rev == 4)) {
		sc->is_emu10k2 = 0;
		sc->is_ca0102 = 1;	/* for unknown Audigy 2 cards */
	}
	if ((sc->is_ca0102 == 1) || (sc->is_ca0108 == 1))
		if (device_flags & IS_CARDBUS)
			sc->is_cardbus = 1;

	if ((sc->is_emu10k1 + sc->is_emu10k2 + sc->is_ca0102 + sc->is_ca0108) != 1) {
		device_printf(sc->dev, "Unable to detect HW chipset\n");
		goto bad;
	}
	if (device_flags & BROKEN_DIGITAL)
		sc->broken_digital = 1;
	if (device_flags & HAS_AC97)
		sc->has_ac97 = 1;

	sc->opcode_shift = 0;
	if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108)) {
		sc->opcode_shift = 24;
		sc->high_operand_shift = 12;

	/*	DSP map				*/
	/*	sc->fx_base = 0x0		*/
		sc->input_base = 0x40;
	/*	sc->p16vinput_base = 0x50;	*/
		sc->output_base = 0x60;
		sc->efxc_base = 0x80;
	/*	sc->output32h_base = 0xa0;	*/
	/*	sc->output32l_base = 0xb0;	*/
		sc->dsp_zero = 0xc0;
	/*	0xe0...0x100 are unknown	*/
	/*	sc->tram_base = 0x200		*/
	/*	sc->tram_addr_base = 0x300	*/
		sc->gpr_base = EMU_A_FXGPREGBASE;
		sc->num_gprs = 0x200;
		sc->code_base = EMU_A_MICROCODEBASE;
		sc->code_size = 0x800 / 2;	/* 0x600-0xdff,  2048 words,
						 * 1024 instructions */

		sc->mchannel_fx = 8;
		sc->num_fxbuses = 16;
		sc->num_inputs = 8;
		sc->num_outputs = 16;
		sc->address_mask = EMU_A_PTR_ADDR_MASK;
	}
	if (sc->is_emu10k1) {
		sc->has_51 = 0;	/* We don't support 5.1 sound on SB Live! 5.1 */
		sc->opcode_shift = 20;
		sc->high_operand_shift = 10;
		sc->code_base = EMU_MICROCODEBASE;
		sc->code_size = 0x400 / 2;	/* 0x400-0x7ff,  1024 words,
						 * 512 instructions */
		sc->gpr_base = EMU_FXGPREGBASE;
		sc->num_gprs = 0x100;
		sc->input_base = 0x10;
		sc->output_base = 0x20;
		/*
		 * XXX 5.1 Analog outputs are inside efxc address space!
		 * They use output+0x11/+0x12 (=efxc+1/+2).
		 * Don't use this efx registers for recording on SB Live! 5.1!
		 */
		sc->efxc_base = 0x30;
		sc->dsp_zero = 0x40;
		sc->mchannel_fx = 0;
		sc->num_fxbuses = 8;
		sc->num_inputs = 8;
		sc->num_outputs = 16;
		sc->address_mask = EMU_PTR_ADDR_MASK;
	}
	if (sc->opcode_shift == 0)
		goto bad;

	pci_enable_busmaster(dev);

	i = PCIR_BAR(0);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &i, RF_ACTIVE);
	if (sc->reg == NULL) {
		device_printf(dev, "unable to map register space\n");
		goto bad;
	}
	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	for (i = 0; i < EMU_MAX_IRQ_CONSUMERS; i++)
		sc->timer[i] = 0;	/* disable it */

	i = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &i, RF_ACTIVE | RF_SHAREABLE);
	if ((sc->irq == NULL) || bus_setup_intr(dev, sc->irq, INTR_MPSAFE | INTR_TYPE_AV,
	    NULL,
	    emu_intr, sc, &sc->ih)) {
		device_printf(dev, "unable to map interrupt\n");
		goto bad;
	}
	if (emu_rm_init(sc) != 0) {
		device_printf(dev, "unable to create resource manager\n");
		goto bad;
	}
	if (sc->is_cardbus)
		if (emu_cardbus_init(sc) != 0) {
			device_printf(dev, "unable to initialize CardBus interface\n");
			goto bad;
		}
	if (emu_init(sc) != 0) {
		device_printf(dev, "unable to initialize the card\n");
		goto bad;
	}
	if (emu10kx_dev_init(sc) != 0) {
		device_printf(dev, "unable to create control device\n");
		goto bad;
	}
	snprintf(status, 255, "rev %d at io 0x%jx irq %jd", sc->rev, rman_get_start(sc->reg), rman_get_start(sc->irq));

	/* Voices */
	for (i = 0; i < NUM_G; i++) {
		sc->voice[i].vnum = i;
		sc->voice[i].slave = NULL;
		sc->voice[i].busy = 0;
		sc->voice[i].ismaster = 0;
		sc->voice[i].running = 0;
		sc->voice[i].b16 = 0;
		sc->voice[i].stereo = 0;
		sc->voice[i].speed = 0;
		sc->voice[i].start = 0;
		sc->voice[i].end = 0;
	}

	/* PCM Audio */
	for (i = 0; i < RT_COUNT; i++)
		sc->pcm[i] = NULL;

	/* FRONT */
	func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (func == NULL) {
		error = ENOMEM;
		goto bad;
	}
	pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (pcminfo == NULL) {
		error = ENOMEM;
		goto bad;
	}
	pcminfo->card = sc;
	pcminfo->route = RT_FRONT;

	func->func = SCF_PCM;
	func->varinfo = pcminfo;
	sc->pcm[RT_FRONT] = device_add_child(dev, "pcm", -1);
	device_set_ivars(sc->pcm[RT_FRONT], func);

	if (!(sc->mch_disabled)) {
		/* REAR */
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL) {
			error = ENOMEM;
			goto bad;
		}
		pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (pcminfo == NULL) {
			error = ENOMEM;
			goto bad;
		}
		pcminfo->card = sc;
		pcminfo->route = RT_REAR;

		func->func = SCF_PCM;
		func->varinfo = pcminfo;
		sc->pcm[RT_REAR] = device_add_child(dev, "pcm", -1);
		device_set_ivars(sc->pcm[RT_REAR], func);
		if (sc->has_51) {
			/* CENTER */
			func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (func == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (pcminfo == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo->card = sc;
			pcminfo->route = RT_CENTER;

			func->func = SCF_PCM;
			func->varinfo = pcminfo;
			sc->pcm[RT_CENTER] = device_add_child(dev, "pcm", -1);
			device_set_ivars(sc->pcm[RT_CENTER], func);
			/* SUB */
			func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (func == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (pcminfo == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo->card = sc;
			pcminfo->route = RT_SUB;

			func->func = SCF_PCM;
			func->varinfo = pcminfo;
			sc->pcm[RT_SUB] = device_add_child(dev, "pcm", -1);
			device_set_ivars(sc->pcm[RT_SUB], func);
		}
		if (sc->has_71) {
			/* SIDE */
			func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (func == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
			if (pcminfo == NULL) {
				error = ENOMEM;
				goto bad;
			}
			pcminfo->card = sc;
			pcminfo->route = RT_SIDE;

			func->func = SCF_PCM;
			func->varinfo = pcminfo;
			sc->pcm[RT_SIDE] = device_add_child(dev, "pcm", -1);
			device_set_ivars(sc->pcm[RT_SIDE], func);
		}
	} /* mch_disabled */

	if (sc->mch_rec) {
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL) {
			error = ENOMEM;
			goto bad;
		}
		pcminfo = malloc(sizeof(struct emu_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (pcminfo == NULL) {
			error = ENOMEM;
			goto bad;
		}
		pcminfo->card = sc;
		pcminfo->route = RT_MCHRECORD;

		func->func = SCF_PCM;
		func->varinfo = pcminfo;
		sc->pcm[RT_MCHRECORD] = device_add_child(dev, "pcm", -1);
		device_set_ivars(sc->pcm[RT_MCHRECORD], func);
	} /*mch_rec */

	for (i = 0; i < 2; i++)
		sc->midi[i] = NULL;

	/* MIDI has some memory mangament and (possible) locking problems */
#if 0
	/* Midi Interface 1: Live!, Audigy, Audigy 2 */
	if ((sc->is_emu10k1) || (sc->is_emu10k2) || (sc->is_ca0102)) {
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL) {
			error = ENOMEM;
			goto bad;
		}
		midiinfo = malloc(sizeof(struct emu_midiinfo), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (midiinfo == NULL) {
			error = ENOMEM;
			goto bad;
		}
		midiinfo->card = sc;
		if (sc->is_emu10k2 || (sc->is_ca0102)) {
			midiinfo->port = EMU_A_MUDATA1;
			midiinfo->portnr = 1;
		}
		if (sc->is_emu10k1) {
			midiinfo->port = MUDATA;
			midiinfo->portnr = 1;
		}
		func->func = SCF_MIDI;
		func->varinfo = midiinfo;
		sc->midi[0] = device_add_child(dev, "midi", -1);
		device_set_ivars(sc->midi[0], func);
	}
	/* Midi Interface 2: Audigy, Audigy 2 (on AudigyDrive) */
	if (sc->is_emu10k2 || (sc->is_ca0102)) {
		func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (func == NULL) {
			error = ENOMEM;
			goto bad;
		}
		midiinfo = malloc(sizeof(struct emu_midiinfo), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (midiinfo == NULL) {
			error = ENOMEM;
			goto bad;
		}
		midiinfo->card = sc;

		midiinfo->port = EMU_A_MUDATA2;
		midiinfo->portnr = 2;

		func->func = SCF_MIDI;
		func->varinfo = midiinfo;
		sc->midi[1] = device_add_child(dev, "midi", -1);
		device_set_ivars(sc->midi[1], func);
	}
#endif
	return (bus_generic_attach(dev));

bad:
	/* XXX can we just call emu_pci_detach here? */
	if (sc->cdev)
		emu10kx_dev_uninit(sc);
	if (sc->rm != NULL)
		emu_rm_uninit(sc);
	if (sc->reg)
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(0), sc->reg);
	if (sc->ih)
		bus_teardown_intr(dev, sc->irq, sc->ih);
	if (sc->irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
	mtx_destroy(&sc->rw);
	mtx_destroy(&sc->lock);
	return (error);
}