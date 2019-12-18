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
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  silent_map; int /*<<< orphan*/  silent_page; int /*<<< orphan*/  ptb_map; int /*<<< orphan*/  ptb_pages; int /*<<< orphan*/  blocks; } ;
struct sc_info {scalar_t__ mpu; TYPE_1__ mem; int /*<<< orphan*/  dev; scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_ADCBA ; 
 int /*<<< orphan*/  EMU_ADCBS ; 
 int /*<<< orphan*/  EMU_A_DBG ; 
 int /*<<< orphan*/  EMU_A_DBG_SINGLE_STEP ; 
 int /*<<< orphan*/  EMU_CHAN_CPF ; 
 int /*<<< orphan*/  EMU_CHAN_CVCF ; 
 int /*<<< orphan*/  EMU_CHAN_DCYSUSV ; 
 int /*<<< orphan*/  EMU_CHAN_PTRX ; 
 int /*<<< orphan*/  EMU_CHAN_VTFT ; 
 int /*<<< orphan*/  EMU_CLIEH ; 
 int /*<<< orphan*/  EMU_CLIEL ; 
 int /*<<< orphan*/  EMU_FXBA ; 
 int /*<<< orphan*/  EMU_FXBS ; 
 int /*<<< orphan*/  EMU_FXWC ; 
 int /*<<< orphan*/  EMU_HCFG ; 
 int EMU_HCFG_LOCKSOUNDCACHE ; 
 int EMU_HCFG_LOCKTANKCACHE_MASK ; 
 int EMU_HCFG_MUTEBUTTONENABLE ; 
 int /*<<< orphan*/  EMU_INTE ; 
 int /*<<< orphan*/  EMU_MICBA ; 
 int /*<<< orphan*/  EMU_MICBS ; 
 int /*<<< orphan*/  EMU_PTB ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_NONE ; 
 int /*<<< orphan*/  EMU_SOLEH ; 
 int /*<<< orphan*/  EMU_SOLEL ; 
 int /*<<< orphan*/  EMU_TCB ; 
 int /*<<< orphan*/  EMU_TCBS ; 
 int /*<<< orphan*/  ENV_OFF ; 
 scalar_t__ NUM_G ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emu_free (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpu401_uninit (scalar_t__) ; 

__attribute__((used)) static int
emu_uninit(struct sc_info *sc)
{
	u_int32_t ch;

	emu_wr(sc, EMU_INTE, 0, 4);
	for (ch = 0; ch < NUM_G; ch++)
		emu_wrptr(sc, ch, EMU_CHAN_DCYSUSV, ENV_OFF);
	for (ch = 0; ch < NUM_G; ch++) {
		emu_wrptr(sc, ch, EMU_CHAN_VTFT, 0);
		emu_wrptr(sc, ch, EMU_CHAN_CVCF, 0);
		emu_wrptr(sc, ch, EMU_CHAN_PTRX, 0);
		emu_wrptr(sc, ch, EMU_CHAN_CPF, 0);
	}

	if (sc->audigy) {	/* stop fx processor */
		emu_wrptr(sc, 0, EMU_A_DBG, EMU_A_DBG_SINGLE_STEP);
	}

	/* disable audio and lock cache */
	emu_wr(sc, EMU_HCFG,
	    EMU_HCFG_LOCKSOUNDCACHE | EMU_HCFG_LOCKTANKCACHE_MASK | EMU_HCFG_MUTEBUTTONENABLE,
	    4);

	emu_wrptr(sc, 0, EMU_PTB, 0);
	/* reset recording buffers */
	emu_wrptr(sc, 0, EMU_MICBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_MICBA, 0);
	emu_wrptr(sc, 0, EMU_FXBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_FXBA, 0);
	emu_wrptr(sc, 0, EMU_FXWC, 0);
	emu_wrptr(sc, 0, EMU_ADCBS, EMU_RECBS_BUFSIZE_NONE);
	emu_wrptr(sc, 0, EMU_ADCBA, 0);
	emu_wrptr(sc, 0, EMU_TCB, 0);
	emu_wrptr(sc, 0, EMU_TCBS, 0);

	/* disable channel interrupt */
	emu_wrptr(sc, 0, EMU_CLIEL, 0);
	emu_wrptr(sc, 0, EMU_CLIEH, 0);
	emu_wrptr(sc, 0, EMU_SOLEL, 0);
	emu_wrptr(sc, 0, EMU_SOLEH, 0);

	/* init envelope engine */
	if (!SLIST_EMPTY(&sc->mem.blocks))
		device_printf(sc->dev, "warning: memblock list not empty\n");
	emu_free(sc, sc->mem.ptb_pages, sc->mem.ptb_map);
	emu_free(sc, sc->mem.silent_page, sc->mem.silent_map);

	if(sc->mpu)
	    mpu401_uninit(sc->mpu);
	return 0;
}