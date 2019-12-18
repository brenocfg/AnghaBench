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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_rchinfo {int run; int /*<<< orphan*/  irqmask; int /*<<< orphan*/  setupreg; int /*<<< orphan*/  sizereg; int /*<<< orphan*/  spd; int /*<<< orphan*/  fmt; int /*<<< orphan*/  num; struct sc_info* parent; } ;
struct sc_info {int bufsz; int /*<<< orphan*/  lock; int /*<<< orphan*/  audigy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU_ADCCR_LCHANENABLE ; 
 int /*<<< orphan*/  EMU_ADCCR_RCHANENABLE ; 
 int /*<<< orphan*/  EMU_A_ADCCR_LCHANENABLE ; 
 int /*<<< orphan*/  EMU_A_ADCCR_RCHANENABLE ; 
 int /*<<< orphan*/  EMU_INTE ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_16384 ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_32768 ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_4096 ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_65536 ; 
 int /*<<< orphan*/  EMU_RECBS_BUFSIZE_8192 ; 
#define  PCMTRIG_ABORT 132 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_EMLDMARD 131 
#define  PCMTRIG_EMLDMAWR 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  audigy_recval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_recval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emurchan_trigger(kobj_t obj, void *data, int go)
{
	struct sc_rchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	u_int32_t val, sz;

	if (!PCMTRIG_COMMON(go))
		return 0;

	switch(sc->bufsz) {
	case 4096:
		sz = EMU_RECBS_BUFSIZE_4096;
		break;

	case 8192:
		sz = EMU_RECBS_BUFSIZE_8192;
		break;

	case 16384:
		sz = EMU_RECBS_BUFSIZE_16384;
		break;

	case 32768:
		sz = EMU_RECBS_BUFSIZE_32768;
		break;

	case 65536:
		sz = EMU_RECBS_BUFSIZE_65536;
		break;

	default:
		sz = EMU_RECBS_BUFSIZE_4096;
	}

	snd_mtxlock(sc->lock);
	switch(go) {
	case PCMTRIG_START:
		ch->run = 1;
		emu_wrptr(sc, 0, ch->sizereg, sz);
		if (ch->num == 0) {
			if (sc->audigy) {
				val = EMU_A_ADCCR_LCHANENABLE;
				if (AFMT_CHANNEL(ch->fmt) > 1)
					val |= EMU_A_ADCCR_RCHANENABLE;
				val |= audigy_recval(ch->spd);
			} else {
				val = EMU_ADCCR_LCHANENABLE;
				if (AFMT_CHANNEL(ch->fmt) > 1)
					val |= EMU_ADCCR_RCHANENABLE;
				val |= emu_recval(ch->spd);
			}

			emu_wrptr(sc, 0, ch->setupreg, 0);
			emu_wrptr(sc, 0, ch->setupreg, val);
		}
		val = emu_rd(sc, EMU_INTE, 4);
		val |= ch->irqmask;
		emu_wr(sc, EMU_INTE, val, 4);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		ch->run = 0;
		emu_wrptr(sc, 0, ch->sizereg, 0);
		if (ch->setupreg)
			emu_wrptr(sc, 0, ch->setupreg, 0);
		val = emu_rd(sc, EMU_INTE, 4);
		val &= ~ch->irqmask;
		emu_wr(sc, EMU_INTE, val, 4);
		break;

	case PCMTRIG_EMLDMAWR:
	case PCMTRIG_EMLDMARD:
	default:
		break;
	}
	snd_mtxunlock(sc->lock);

	return 0;
}