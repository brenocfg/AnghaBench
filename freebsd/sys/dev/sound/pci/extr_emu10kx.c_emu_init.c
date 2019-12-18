#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* ptb_pages; int ptb_pages_addr; int silent_page_addr; int /*<<< orphan*/ * silent_page; int /*<<< orphan*/  ptb_map; int /*<<< orphan*/  silent_map; int /*<<< orphan*/  blocks; struct emu_sc_info* card; int /*<<< orphan*/  dmat; } ;
struct emu_sc_info {int /*<<< orphan*/  dev; scalar_t__ is_ca0108; scalar_t__ is_ca0102; scalar_t__ is_emu10k2; scalar_t__ broken_digital; TYPE_1__ mem; scalar_t__ has_71; scalar_t__ has_51; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int EMUPAGESIZE ; 
 int /*<<< orphan*/  EMU_A2_MIXER_I2S_ENABLE ; 
 int /*<<< orphan*/  EMU_A2_MIXER_SPDIF_ENABLE ; 
 int /*<<< orphan*/  EMU_A2_SRCMULTI_ENABLE ; 
 int /*<<< orphan*/  EMU_A2_SRCSel ; 
 int EMU_AC97SLOT ; 
 int EMU_AC97SLOT_CENTER ; 
 int EMU_AC97SLOT_LFE ; 
 int EMU_AC97SLOT_REAR_LEFT ; 
 int EMU_AC97SLOT_REAR_RIGHT ; 
 int EMU_ADCBA ; 
 int EMU_ADCBS ; 
 int EMU_A_CHAN_FXRT1 ; 
 int EMU_A_CHAN_FXRT2 ; 
 int EMU_A_CHAN_SENDAMOUNTS ; 
 int EMU_A_I2S_CAPTURE_96000 ; 
 int /*<<< orphan*/  EMU_A_IOCFG ; 
 int EMU_A_SPDIF_48000 ; 
 int EMU_A_SPDIF_SAMPLERATE ; 
 int EMU_CHAN_ATKHLDM ; 
 int EMU_CHAN_ATKHLDV ; 
 int EMU_CHAN_CCCA ; 
 int EMU_CHAN_CCR ; 
 int EMU_CHAN_CPF ; 
 int EMU_CHAN_CVCF ; 
 int EMU_CHAN_DCYSUSM ; 
 int EMU_CHAN_DCYSUSV ; 
 int EMU_CHAN_DSL ; 
 int EMU_CHAN_ENVVAL ; 
 int EMU_CHAN_ENVVOL ; 
 int EMU_CHAN_FM2FRQ2 ; 
 int EMU_CHAN_FMMOD ; 
 int EMU_CHAN_FXRT ; 
 int EMU_CHAN_IFATN ; 
 int EMU_CHAN_IP ; 
 int EMU_CHAN_LFOVAL1 ; 
 int EMU_CHAN_LFOVAL2 ; 
 int EMU_CHAN_MAPA ; 
 int EMU_CHAN_MAPB ; 
 int EMU_CHAN_MAP_PTI_MASK ; 
 int EMU_CHAN_PEFE ; 
 int EMU_CHAN_PSST ; 
 int EMU_CHAN_PTRX ; 
 int EMU_CHAN_TEMPENV ; 
 int EMU_CHAN_TREMFRQ ; 
 int EMU_CHAN_VTFT ; 
 int EMU_CHAN_Z1 ; 
 int EMU_CHAN_Z2 ; 
 int EMU_CLIEH ; 
 int EMU_CLIEL ; 
 int EMU_FXBA ; 
 int EMU_FXBS ; 
 int /*<<< orphan*/  EMU_HCFG ; 
 int EMU_HCFG_LOCKSOUNDCACHE ; 
 int EMU_HCFG_LOCKTANKCACHE_MASK ; 
 int EMU_HCFG_MUTEBUTTONENABLE ; 
 int /*<<< orphan*/  EMU_INTE ; 
 int /*<<< orphan*/  EMU_INTE2 ; 
 int /*<<< orphan*/  EMU_INTE3 ; 
 int EMU_INTE_INTERTIMERENB ; 
 int EMU_INTE_PCIERRENABLE ; 
 int EMU_INTE_SAMPLERATER ; 
 int EMU_MAXPAGES ; 
 int /*<<< orphan*/  EMU_MAX_BUFSZ ; 
 int EMU_MICBA ; 
 int EMU_MICBS ; 
 int EMU_PTB ; 
 int EMU_RECBS_BUFSIZE_NONE ; 
 int EMU_SOLEH ; 
 int EMU_SOLEL ; 
 int EMU_SPBYPASS ; 
 int EMU_TCB ; 
 int EMU_TCBS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  Giant ; 
 int MODE_ANALOG ; 
 int MODE_DIGITAL ; 
 int NUM_G ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPDIF_MODE_PCM ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  emu_free (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_initefx (struct emu_sc_info*) ; 
 void* emu_malloc (TYPE_1__*,int,int*,int /*<<< orphan*/ *) ; 
 int emu_rd (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int emu_rdptr (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emu_wr_p16vptr (struct emu_sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wrptr (struct emu_sc_info*,int,int,int) ; 
 int /*<<< orphan*/  emumix_set_mode (struct emu_sc_info*,int) ; 
 int /*<<< orphan*/  emumix_set_spdif_mode (struct emu_sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int
emu_init(struct emu_sc_info *sc)
{
	uint32_t ch, tmp;
	uint32_t spdif_sr;
	uint32_t ac97slot;
	int def_mode;
	int i;

	/* disable audio and lock cache */
	emu_wr(sc, EMU_HCFG, EMU_HCFG_LOCKSOUNDCACHE | EMU_HCFG_LOCKTANKCACHE_MASK | EMU_HCFG_MUTEBUTTONENABLE, 4);

	/* reset recording buffers */
	emu_wrptr(sc, 0, EMU_MICBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_MICBA, 0);
	emu_wrptr(sc, 0, EMU_FXBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_FXBA, 0);
	emu_wrptr(sc, 0, EMU_ADCBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_ADCBA, 0);

	/* disable channel interrupt */
	emu_wr(sc, EMU_INTE, EMU_INTE_INTERTIMERENB | EMU_INTE_SAMPLERATER | EMU_INTE_PCIERRENABLE, 4);
	emu_wrptr(sc, 0, EMU_CLIEL, 0);
	emu_wrptr(sc, 0, EMU_CLIEH, 0);
	emu_wrptr(sc, 0, EMU_SOLEL, 0);
	emu_wrptr(sc, 0, EMU_SOLEH, 0);

	/* disable P16V and S/PDIF interrupts */
	if ((sc->is_ca0102) || (sc->is_ca0108))
		emu_wr(sc, EMU_INTE2, 0, 4);

	if (sc->is_ca0102)
		emu_wr(sc, EMU_INTE3, 0, 4);

	/* init phys inputs and outputs */
	ac97slot = 0;
	if (sc->has_51)
		ac97slot = EMU_AC97SLOT_CENTER | EMU_AC97SLOT_LFE;
	if (sc->has_71)
		ac97slot = EMU_AC97SLOT_CENTER | EMU_AC97SLOT_LFE | EMU_AC97SLOT_REAR_LEFT | EMU_AC97SLOT_REAR_RIGHT;
	if (sc->is_emu10k2)
		ac97slot |= 0x40;
	emu_wrptr(sc, 0, EMU_AC97SLOT, ac97slot);

	if (sc->is_emu10k2)	/* XXX for later cards? */
		emu_wrptr(sc, 0, EMU_SPBYPASS, 0xf00);	/* What will happen if
							 * we write 1 here? */

	if (bus_dma_tag_create( /* parent */ bus_get_dma_tag(sc->dev),
	     /* alignment */ 2, /* boundary */ 0,
	     /* lowaddr */ (1U << 31) - 1,	/* can only access 0-2gb */
	     /* highaddr */ BUS_SPACE_MAXADDR,
	     /* filter */ NULL, /* filterarg */ NULL,
	     /* maxsize */ EMU_MAX_BUFSZ, /* nsegments */ 1, /* maxsegz */ 0x3ffff,
	     /* flags */ 0, /* lockfunc */ busdma_lock_mutex,
	     /* lockarg */ &Giant, &(sc->mem.dmat)) != 0) {
		device_printf(sc->dev, "unable to create dma tag\n");
		bus_dma_tag_destroy(sc->mem.dmat);
		return (ENOMEM);
	}

	sc->mem.card = sc;
	SLIST_INIT(&sc->mem.blocks);
	sc->mem.ptb_pages = emu_malloc(&sc->mem, EMU_MAXPAGES * sizeof(uint32_t), &sc->mem.ptb_pages_addr, &sc->mem.ptb_map);
	if (sc->mem.ptb_pages == NULL)
		return (ENOMEM);

	sc->mem.silent_page = emu_malloc(&sc->mem, EMUPAGESIZE, &sc->mem.silent_page_addr, &sc->mem.silent_map);
	if (sc->mem.silent_page == NULL) {
		emu_free(&sc->mem, sc->mem.ptb_pages, sc->mem.ptb_map);
		return (ENOMEM);
	}
	/* Clear page with silence & setup all pointers to this page */
	bzero(sc->mem.silent_page, EMUPAGESIZE);
	tmp = (uint32_t) (sc->mem.silent_page_addr) << 1;
	for (i = 0; i < EMU_MAXPAGES; i++)
		sc->mem.ptb_pages[i] = tmp | i;

	for (ch = 0; ch < NUM_G; ch++) {
		emu_wrptr(sc, ch, EMU_CHAN_MAPA, tmp | EMU_CHAN_MAP_PTI_MASK);
		emu_wrptr(sc, ch, EMU_CHAN_MAPB, tmp | EMU_CHAN_MAP_PTI_MASK);
	}
	emu_wrptr(sc, 0, EMU_PTB, (sc->mem.ptb_pages_addr));
	emu_wrptr(sc, 0, EMU_TCB, 0);	/* taken from original driver */
	emu_wrptr(sc, 0, EMU_TCBS, 0);	/* taken from original driver */

	/* init envelope engine */
	for (ch = 0; ch < NUM_G; ch++) {
		emu_wrptr(sc, ch, EMU_CHAN_DCYSUSV, 0);
		emu_wrptr(sc, ch, EMU_CHAN_IP, 0);
		emu_wrptr(sc, ch, EMU_CHAN_VTFT, 0xffff);
		emu_wrptr(sc, ch, EMU_CHAN_CVCF, 0xffff);
		emu_wrptr(sc, ch, EMU_CHAN_PTRX, 0);
		emu_wrptr(sc, ch, EMU_CHAN_CPF, 0);
		emu_wrptr(sc, ch, EMU_CHAN_CCR, 0);

		emu_wrptr(sc, ch, EMU_CHAN_PSST, 0);
		emu_wrptr(sc, ch, EMU_CHAN_DSL, 0x10);
		emu_wrptr(sc, ch, EMU_CHAN_CCCA, 0);
		emu_wrptr(sc, ch, EMU_CHAN_Z1, 0);
		emu_wrptr(sc, ch, EMU_CHAN_Z2, 0);
		emu_wrptr(sc, ch, EMU_CHAN_FXRT, 0xd01c0000);

		emu_wrptr(sc, ch, EMU_CHAN_ATKHLDM, 0);
		emu_wrptr(sc, ch, EMU_CHAN_DCYSUSM, 0);
		emu_wrptr(sc, ch, EMU_CHAN_IFATN, 0xffff);
		emu_wrptr(sc, ch, EMU_CHAN_PEFE, 0);
		emu_wrptr(sc, ch, EMU_CHAN_FMMOD, 0);
		emu_wrptr(sc, ch, EMU_CHAN_TREMFRQ, 24);	/* 1 Hz */
		emu_wrptr(sc, ch, EMU_CHAN_FM2FRQ2, 24);	/* 1 Hz */
		emu_wrptr(sc, ch, EMU_CHAN_TEMPENV, 0);

		/*** these are last so OFF prevents writing ***/
		emu_wrptr(sc, ch, EMU_CHAN_LFOVAL2, 0);
		emu_wrptr(sc, ch, EMU_CHAN_LFOVAL1, 0);
		emu_wrptr(sc, ch, EMU_CHAN_ATKHLDV, 0);
		emu_wrptr(sc, ch, EMU_CHAN_ENVVOL, 0);
		emu_wrptr(sc, ch, EMU_CHAN_ENVVAL, 0);

		if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108)) {
			emu_wrptr(sc, ch, 0x4c, 0x0);
			emu_wrptr(sc, ch, 0x4d, 0x0);
			emu_wrptr(sc, ch, 0x4e, 0x0);
			emu_wrptr(sc, ch, 0x4f, 0x0);
			emu_wrptr(sc, ch, EMU_A_CHAN_FXRT1, 0x3f3f3f3f);
			emu_wrptr(sc, ch, EMU_A_CHAN_FXRT2, 0x3f3f3f3f);
			emu_wrptr(sc, ch, EMU_A_CHAN_SENDAMOUNTS, 0x0);
		}
	}

	emumix_set_spdif_mode(sc, SPDIF_MODE_PCM);

	if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108))
		emu_wrptr(sc, 0, EMU_A_SPDIF_SAMPLERATE, EMU_A_SPDIF_48000);

	/*
	 * CAxxxx cards needs additional setup:
	 * 1. Set I2S capture sample rate to 96000
	 * 2. Disable P16v / P17v proceesing
	 * 3. Allow EMU10K DSP inputs
	 */
	if ((sc->is_ca0102) || (sc->is_ca0108)) {

		spdif_sr = emu_rdptr(sc, 0, EMU_A_SPDIF_SAMPLERATE);
		spdif_sr &= 0xfffff1ff;
		spdif_sr |= EMU_A_I2S_CAPTURE_96000;
		emu_wrptr(sc, 0, EMU_A_SPDIF_SAMPLERATE, spdif_sr);

		/* Disable P16v processing */
		emu_wr_p16vptr(sc, 0, EMU_A2_SRCSel, 0x14);

		/* Setup P16v/P17v sound routing */
		if (sc->is_ca0102)
			emu_wr_p16vptr(sc, 0, EMU_A2_SRCMULTI_ENABLE, 0xFF00FF00);
		else {
			emu_wr_p16vptr(sc, 0, EMU_A2_MIXER_I2S_ENABLE, 0xFF000000);
			emu_wr_p16vptr(sc, 0, EMU_A2_MIXER_SPDIF_ENABLE, 0xFF000000);

			tmp = emu_rd(sc, EMU_A_IOCFG, 2);
			emu_wr(sc, EMU_A_IOCFG, tmp & ~0x8, 2);
		}
	}
	emu_initefx(sc);

	def_mode = MODE_ANALOG;
	if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108))
		def_mode = MODE_DIGITAL;
	if (((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108)) && (sc->broken_digital)) {
		device_printf(sc->dev, "Audigy card initialized in analog mode.\n");
		def_mode = MODE_ANALOG;
	}
	emumix_set_mode(sc, def_mode);

	if (bootverbose) {
		tmp = emu_rd(sc, EMU_HCFG, 4);
		device_printf(sc->dev, "Card Configuration (   0x%08x )\n", tmp);
		device_printf(sc->dev, "Card Configuration ( & 0xff000000 ) : %s%s%s%s%s%s%s%s\n",
		    (tmp & 0x80000000 ? "[Legacy MPIC] " : ""),
		    (tmp & 0x40000000 ? "[0x40] " : ""),
		    (tmp & 0x20000000 ? "[0x20] " : ""),
		    (tmp & 0x10000000 ? "[0x10] " : ""),
		    (tmp & 0x08000000 ? "[0x08] " : ""),
		    (tmp & 0x04000000 ? "[0x04] " : ""),
		    (tmp & 0x02000000 ? "[0x02] " : ""),
		    (tmp & 0x01000000 ? "[0x01]" : " "));
		device_printf(sc->dev, "Card Configuration ( & 0x00ff0000 ) : %s%s%s%s%s%s%s%s\n",
		    (tmp & 0x00800000 ? "[0x80] " : ""),
		    (tmp & 0x00400000 ? "[0x40] " : ""),
		    (tmp & 0x00200000 ? "[Legacy INT] " : ""),
		    (tmp & 0x00100000 ? "[0x10] " : ""),
		    (tmp & 0x00080000 ? "[0x08] " : ""),
		    (tmp & 0x00040000 ? "[Codec4] " : ""),
		    (tmp & 0x00020000 ? "[Codec2] " : ""),
		    (tmp & 0x00010000 ? "[I2S Codec]" : " "));
		device_printf(sc->dev, "Card Configuration ( & 0x0000ff00 ) : %s%s%s%s%s%s%s%s\n",
		    (tmp & 0x00008000 ? "[0x80] " : ""),
		    (tmp & 0x00004000 ? "[GPINPUT0] " : ""),
		    (tmp & 0x00002000 ? "[GPINPUT1] " : ""),
		    (tmp & 0x00001000 ? "[GPOUT0] " : ""),
		    (tmp & 0x00000800 ? "[GPOUT1] " : ""),
		    (tmp & 0x00000400 ? "[GPOUT2] " : ""),
		    (tmp & 0x00000200 ? "[Joystick] " : ""),
		    (tmp & 0x00000100 ? "[0x01]" : " "));
		device_printf(sc->dev, "Card Configuration ( & 0x000000ff ) : %s%s%s%s%s%s%s%s\n",
		    (tmp & 0x00000080 ? "[0x80] " : ""),
		    (tmp & 0x00000040 ? "[0x40] " : ""),
		    (tmp & 0x00000020 ? "[0x20] " : ""),
		    (tmp & 0x00000010 ? "[AUTOMUTE] " : ""),
		    (tmp & 0x00000008 ? "[LOCKSOUNDCACHE] " : ""),
		    (tmp & 0x00000004 ? "[LOCKTANKCACHE] " : ""),
		    (tmp & 0x00000002 ? "[MUTEBUTTONENABLE] " : ""),
		    (tmp & 0x00000001 ? "[AUDIOENABLE]" : " "));

		if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108)) {
			tmp = emu_rd(sc, EMU_A_IOCFG, 2);
			device_printf(sc->dev, "Audigy Card Configuration (    0x%04x )\n", tmp);
			device_printf(sc->dev, "Audigy Card Configuration (  & 0xff00 )");
			printf(" : %s%s%s%s%s%s%s%s\n",
			    (tmp & 0x8000 ? "[Rear Speakers] " : ""),
			    (tmp & 0x4000 ? "[Front Speakers] " : ""),
			    (tmp & 0x2000 ? "[0x20] " : ""),
			    (tmp & 0x1000 ? "[0x10] " : ""),
			    (tmp & 0x0800 ? "[0x08] " : ""),
			    (tmp & 0x0400 ? "[0x04] " : ""),
			    (tmp & 0x0200 ? "[0x02] " : ""),
			    (tmp & 0x0100 ? "[AudigyDrive Phones]" : " "));
			device_printf(sc->dev, "Audigy Card Configuration (  & 0x00ff )");
			printf(" : %s%s%s%s%s%s%s%s\n",
			    (tmp & 0x0080 ? "[0x80] " : ""),
			    (tmp & 0x0040 ? "[Mute AnalogOut] " : ""),
			    (tmp & 0x0020 ? "[0x20] " : ""),
			    (tmp & 0x0010 ? "[0x10] " : ""),
			    (tmp & 0x0008 ? "[0x08] " : ""),
			    (tmp & 0x0004 ? "[GPOUT0] " : ""),
			    (tmp & 0x0002 ? "[GPOUT1] " : ""),
			    (tmp & 0x0001 ? "[GPOUT2]" : " "));
		}		/* is_emu10k2 or ca* */
	}			/* bootverbose */
	return (0);
}