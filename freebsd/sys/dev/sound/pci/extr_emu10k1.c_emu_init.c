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
typedef  size_t u_int32_t ;
struct TYPE_4__ {size_t* ptb_pages; size_t ptb_pages_addr; size_t silent_page_addr; int /*<<< orphan*/ * silent_page; int /*<<< orphan*/  ptb_map; int /*<<< orphan*/  silent_map; int /*<<< orphan*/  blocks; } ;
struct sc_info {int rev; int tos_link; scalar_t__ audigy2; scalar_t__ audigy; TYPE_2__ mem; scalar_t__ rnum; scalar_t__ pnum; TYPE_1__* voice; } ;
struct TYPE_3__ {size_t vnum; int /*<<< orphan*/ * channel; scalar_t__ end; scalar_t__ start; scalar_t__ speed; scalar_t__ stereo; scalar_t__ b16; scalar_t__ running; scalar_t__ ismaster; scalar_t__ busy; int /*<<< orphan*/ * slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EMUMAXPAGES ; 
 int EMUPAGESIZE ; 
 int EMU_AC97SLOT ; 
 size_t EMU_AC97SLOT_CENTER ; 
 size_t EMU_AC97SLOT_LFE ; 
 int EMU_ADCBA ; 
 int EMU_ADCBS ; 
 int EMU_A_CHAN_FXRT1 ; 
 int EMU_A_CHAN_FXRT2 ; 
 int EMU_A_CHAN_SENDAMOUNTS ; 
 int EMU_A_IOCFG ; 
 size_t EMU_A_IOCFG_GPOUT_A ; 
 size_t EMU_A_IOCFG_GPOUT_AD ; 
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
 size_t EMU_CHAN_MAP_PTI_MASK ; 
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
 int EMU_HCFG ; 
 size_t EMU_HCFG_AC3ENABLE_CDSPDIF ; 
 size_t EMU_HCFG_AC3ENABLE_GPSPDIF ; 
 size_t EMU_HCFG_AUDIOENABLE ; 
 size_t EMU_HCFG_AUTOMUTE ; 
 size_t EMU_HCFG_GPINPUT0 ; 
 size_t EMU_HCFG_GPINPUT1 ; 
 size_t EMU_HCFG_GPOUT1 ; 
 size_t EMU_HCFG_JOYENABLE ; 
 size_t EMU_HCFG_LOCKSOUNDCACHE ; 
 size_t EMU_HCFG_LOCKTANKCACHE_MASK ; 
 size_t EMU_HCFG_MUTEBUTTONENABLE ; 
 int EMU_INTE ; 
 size_t EMU_INTE_INTERTIMERENB ; 
 size_t EMU_INTE_PCIERRENABLE ; 
 size_t EMU_INTE_SAMPLERATER ; 
 int EMU_MICBA ; 
 int EMU_MICBS ; 
 int EMU_PTB ; 
 size_t EMU_RECBS_BUFSIZE_NONE ; 
 int EMU_SOLEH ; 
 int EMU_SOLEL ; 
 int EMU_SPBYPASS ; 
 int EMU_SPCS0 ; 
 int EMU_SPCS1 ; 
 int EMU_SPCS2 ; 
 int EMU_SPCS_CHANNELNUM_LEFT ; 
 int EMU_SPCS_CLKACCY_1000PPM ; 
 int EMU_SPCS_COPYRIGHT ; 
 int EMU_SPCS_EMPHASIS_NONE ; 
 int EMU_SPCS_GENERATIONSTATUS ; 
 int EMU_SPCS_SAMPLERATE_48 ; 
 int EMU_SPCS_SOURCENUM_UNSPEC ; 
 int EMU_TCB ; 
 int EMU_TCBS ; 
 size_t ENV_OFF ; 
 size_t NUM_G ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audigy_initefx (struct sc_info*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emu_free (struct sc_info*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_initefx (struct sc_info*) ; 
 void* emu_malloc (struct sc_info*,int,size_t*,int /*<<< orphan*/ *) ; 
 size_t emu_rd (struct sc_info*,int,int) ; 
 int emu_rdptr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int,size_t,int) ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,size_t,int,size_t) ; 

__attribute__((used)) static int
emu_init(struct sc_info *sc)
{
	u_int32_t spcs, ch, tmp, i;

	if (sc->audigy) {
		/* enable additional AC97 slots */
		emu_wrptr(sc, 0, EMU_AC97SLOT, EMU_AC97SLOT_CENTER | EMU_AC97SLOT_LFE);
	}

	/* disable audio and lock cache */
	emu_wr(sc, EMU_HCFG,
	    EMU_HCFG_LOCKSOUNDCACHE | EMU_HCFG_LOCKTANKCACHE_MASK | EMU_HCFG_MUTEBUTTONENABLE,
	    4);

	/* reset recording buffers */
	emu_wrptr(sc, 0, EMU_MICBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_MICBA, 0);
	emu_wrptr(sc, 0, EMU_FXBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_FXBA, 0);
	emu_wrptr(sc, 0, EMU_ADCBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_ADCBA, 0);

	/* disable channel interrupt */
	emu_wr(sc, EMU_INTE,
	    EMU_INTE_INTERTIMERENB | EMU_INTE_SAMPLERATER | EMU_INTE_PCIERRENABLE,
	    4);
	emu_wrptr(sc, 0, EMU_CLIEL, 0);
	emu_wrptr(sc, 0, EMU_CLIEH, 0);
	emu_wrptr(sc, 0, EMU_SOLEL, 0);
	emu_wrptr(sc, 0, EMU_SOLEH, 0);

	/* wonder what these do... */
	if (sc->audigy) {
		emu_wrptr(sc, 0, EMU_SPBYPASS, 0xf00);
		emu_wrptr(sc, 0, EMU_AC97SLOT, 0x3);
	}

	/* init envelope engine */
	for (ch = 0; ch < NUM_G; ch++) {
		emu_wrptr(sc, ch, EMU_CHAN_DCYSUSV, ENV_OFF);
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

		if (sc->audigy) {
			/* audigy cards need this to initialize correctly */
			emu_wrptr(sc, ch, 0x4c, 0);
			emu_wrptr(sc, ch, 0x4d, 0);
			emu_wrptr(sc, ch, 0x4e, 0);
			emu_wrptr(sc, ch, 0x4f, 0);
			/* set default routing */
			emu_wrptr(sc, ch, EMU_A_CHAN_FXRT1, 0x03020100);
			emu_wrptr(sc, ch, EMU_A_CHAN_FXRT2, 0x3f3f3f3f);
			emu_wrptr(sc, ch, EMU_A_CHAN_SENDAMOUNTS, 0);
		}

		sc->voice[ch].vnum = ch;
		sc->voice[ch].slave = NULL;
		sc->voice[ch].busy = 0;
		sc->voice[ch].ismaster = 0;
		sc->voice[ch].running = 0;
		sc->voice[ch].b16 = 0;
		sc->voice[ch].stereo = 0;
		sc->voice[ch].speed = 0;
		sc->voice[ch].start = 0;
		sc->voice[ch].end = 0;
		sc->voice[ch].channel = NULL;
	}
	sc->pnum = sc->rnum = 0;

	/*
	 *  Init to 0x02109204 :
	 *  Clock accuracy    = 0     (1000ppm)
	 *  Sample Rate       = 2     (48kHz)
	 *  Audio Channel     = 1     (Left of 2)
	 *  Source Number     = 0     (Unspecified)
	 *  Generation Status = 1     (Original for Cat Code 12)
	 *  Cat Code          = 12    (Digital Signal Mixer)
	 *  Mode              = 0     (Mode 0)
	 *  Emphasis          = 0     (None)
	 *  CP                = 1     (Copyright unasserted)
	 *  AN                = 0     (Audio data)
	 *  P                 = 0     (Consumer)
	 */
	spcs = EMU_SPCS_CLKACCY_1000PPM | EMU_SPCS_SAMPLERATE_48 |
	    EMU_SPCS_CHANNELNUM_LEFT | EMU_SPCS_SOURCENUM_UNSPEC |
	    EMU_SPCS_GENERATIONSTATUS | 0x00001200 | 0x00000000 |
	    EMU_SPCS_EMPHASIS_NONE | EMU_SPCS_COPYRIGHT;
	emu_wrptr(sc, 0, EMU_SPCS0, spcs);
	emu_wrptr(sc, 0, EMU_SPCS1, spcs);
	emu_wrptr(sc, 0, EMU_SPCS2, spcs);

	if (!sc->audigy)
		emu_initefx(sc);
	else if (sc->audigy2) {	/* Audigy 2 */
		/* from ALSA initialization code: */

		/* Hack for Alice3 to work independent of haP16V driver */
		u_int32_t tmp;

		/* Setup SRCMulti_I2S SamplingRate */
		tmp = emu_rdptr(sc, 0, EMU_A_SPDIF_SAMPLERATE) & 0xfffff1ff;
		emu_wrptr(sc, 0, EMU_A_SPDIF_SAMPLERATE, tmp | 0x400);

		/* Setup SRCSel (Enable SPDIF, I2S SRCMulti) */
		emu_wr(sc, 0x20, 0x00600000, 4);
		emu_wr(sc, 0x24, 0x00000014, 4);

		/* Setup SRCMulti Input Audio Enable */
		emu_wr(sc, 0x20, 0x006e0000, 4);
		emu_wr(sc, 0x24, 0xff00ff00, 4);
	}

	SLIST_INIT(&sc->mem.blocks);
	sc->mem.ptb_pages = emu_malloc(sc, EMUMAXPAGES * sizeof(u_int32_t),
	    &sc->mem.ptb_pages_addr, &sc->mem.ptb_map);
	if (sc->mem.ptb_pages == NULL)
		return -1;

	sc->mem.silent_page = emu_malloc(sc, EMUPAGESIZE,
	    &sc->mem.silent_page_addr, &sc->mem.silent_map);
	if (sc->mem.silent_page == NULL) {
		emu_free(sc, sc->mem.ptb_pages, sc->mem.ptb_map);
		return -1;
	}
	/* Clear page with silence & setup all pointers to this page */
	bzero(sc->mem.silent_page, EMUPAGESIZE);
	tmp = (u_int32_t)(sc->mem.silent_page_addr) << 1;
	for (i = 0; i < EMUMAXPAGES; i++)
		sc->mem.ptb_pages[i] = tmp | i;

	emu_wrptr(sc, 0, EMU_PTB, (sc->mem.ptb_pages_addr));
	emu_wrptr(sc, 0, EMU_TCB, 0);	/* taken from original driver */
	emu_wrptr(sc, 0, EMU_TCBS, 0);	/* taken from original driver */

	for (ch = 0; ch < NUM_G; ch++) {
		emu_wrptr(sc, ch, EMU_CHAN_MAPA, tmp | EMU_CHAN_MAP_PTI_MASK);
		emu_wrptr(sc, ch, EMU_CHAN_MAPB, tmp | EMU_CHAN_MAP_PTI_MASK);
	}

	/* emu_memalloc(sc, EMUPAGESIZE); */
	/*
	 *  Hokay, now enable the AUD bit
	 *
	 *  Audigy
	 *   Enable Audio = 0 (enabled after fx processor initialization)
	 *   Mute Disable Audio = 0
	 *   Joystick = 1
	 *
	 *  Audigy 2
	 *   Enable Audio = 1
	 *   Mute Disable Audio = 0
	 *   Joystick = 1
	 *   GP S/PDIF AC3 Enable = 1
	 *   CD S/PDIF AC3 Enable = 1
	 *
	 *  EMU10K1
	 *   Enable Audio = 1
	 *   Mute Disable Audio = 0
	 *   Lock Tank Memory = 1
	 *   Lock Sound Memory = 0
	 *   Auto Mute = 1
	 */

	if (sc->audigy) {
		tmp = EMU_HCFG_AUTOMUTE | EMU_HCFG_JOYENABLE;
		if (sc->audigy2)	/* Audigy 2 */
			tmp = EMU_HCFG_AUDIOENABLE | EMU_HCFG_AC3ENABLE_CDSPDIF |
			    EMU_HCFG_AC3ENABLE_GPSPDIF;
		emu_wr(sc, EMU_HCFG, tmp, 4);

		audigy_initefx(sc);

		/* from ALSA initialization code: */

		/* enable audio and disable both audio/digital outputs */
		emu_wr(sc, EMU_HCFG, emu_rd(sc, EMU_HCFG, 4) | EMU_HCFG_AUDIOENABLE, 4);
		emu_wr(sc, EMU_A_IOCFG, emu_rd(sc, EMU_A_IOCFG, 4) & ~EMU_A_IOCFG_GPOUT_AD,
		    4);
		if (sc->audigy2) {	/* Audigy 2 */
			/* Unmute Analog.
			 * Set GPO6 to 1 for Apollo. This has to be done after
			 * init Alice3 I2SOut beyond 48kHz.
			 * So, sequence is important.
			 */
			emu_wr(sc, EMU_A_IOCFG,
			    emu_rd(sc, EMU_A_IOCFG, 4) | EMU_A_IOCFG_GPOUT_A, 4);
		}
	} else {
		/* EMU10K1 initialization code */
		tmp = EMU_HCFG_AUDIOENABLE | EMU_HCFG_LOCKTANKCACHE_MASK 
		    | EMU_HCFG_AUTOMUTE;
		if (sc->rev >= 6)
			tmp |= EMU_HCFG_JOYENABLE;

		emu_wr(sc, EMU_HCFG, tmp, 4);

		/* TOSLink detection */
		sc->tos_link = 0;
		tmp = emu_rd(sc, EMU_HCFG, 4);
		if (tmp & (EMU_HCFG_GPINPUT0 | EMU_HCFG_GPINPUT1)) {
			emu_wr(sc, EMU_HCFG, tmp | EMU_HCFG_GPOUT1, 4);
			DELAY(50);
			if (tmp != (emu_rd(sc, EMU_HCFG, 4) & ~EMU_HCFG_GPOUT1)) {
				sc->tos_link = 1;
				emu_wr(sc, EMU_HCFG, tmp, 4);
			}
		}
	}

	return 0;
}