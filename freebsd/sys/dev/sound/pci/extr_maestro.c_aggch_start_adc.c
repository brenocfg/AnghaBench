#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
typedef  int u_int ;
struct agg_rchinfo {int speed; int stereo; int srcphys; int base; int phys; int buflen; TYPE_1__* parent; scalar_t__ hwptr; } ;
typedef  int bus_addr_t ;
struct TYPE_9__ {int bufsz; int active; int playchns; } ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_AMPLITUDE ; 
 int /*<<< orphan*/  APUREG_APUTYPE ; 
 int /*<<< orphan*/  APUREG_EFFECT_GAIN ; 
 int /*<<< orphan*/  APUREG_ROUTING ; 
 int APUTYPE_INPUTMIXER ; 
 int APUTYPE_RATECONV ; 
 int APU_APUTYPE_SHIFT ; 
 int APU_DATASRC_A_SHIFT ; 
 int APU_DMA_ENABLED ; 
 int PAN_FRONT ; 
 int PAN_LEFT ; 
 int WAVCACHE_CHCTL_ADDRTAG_MASK ; 
 int WAVCACHE_CHCTL_STEREO ; 
 int WPWA_USE_SYSMEM ; 
 int /*<<< orphan*/  agg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  agg_power (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  apu_setparam (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  powerstate_active ; 
 int /*<<< orphan*/  set_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  wc_wrchctl (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  wp_starttimer (TYPE_1__*) ; 
 int /*<<< orphan*/  wp_wrapu (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aggch_start_adc(struct agg_rchinfo *ch)
{
	bus_addr_t	wpwa, wpwa2;
	u_int16_t	wcreg, wcreg2;
	u_int	dv;
	int	pan;

	/* speed > 48000 not cared */
	dv = ((ch->speed << 16) + 24000) / 48000;

	/* RATECONV doesn't seem to like dv == 0x10000. */
	if (dv == 0x10000)
		dv--;

	if (ch->stereo) {
		wpwa = (ch->srcphys - ch->base) >> 1;
		wpwa2 = (ch->srcphys + ch->parent->bufsz/2 - ch->base) >> 1;
		wcreg = (ch->srcphys - 16) & WAVCACHE_CHCTL_ADDRTAG_MASK;
		wcreg2 = (ch->base - 16) & WAVCACHE_CHCTL_ADDRTAG_MASK;
		pan = PAN_LEFT - PAN_FRONT;
	} else {
		wpwa = (ch->phys - ch->base) >> 1;
		wpwa2 = (ch->srcphys - ch->base) >> 1;
		wcreg = (ch->phys - 16) & WAVCACHE_CHCTL_ADDRTAG_MASK;
		wcreg2 = (ch->base - 16) & WAVCACHE_CHCTL_ADDRTAG_MASK;
		pan = 0;
	}

	agg_lock(ch->parent);

	ch->hwptr = 0;
	agg_power(ch->parent, powerstate_active);

	/* Invalidate WaveCache. */
	wc_wrchctl(ch->parent, 0, wcreg | WAVCACHE_CHCTL_STEREO);
	wc_wrchctl(ch->parent, 1, wcreg | WAVCACHE_CHCTL_STEREO);
	wc_wrchctl(ch->parent, 2, wcreg2 | WAVCACHE_CHCTL_STEREO);
	wc_wrchctl(ch->parent, 3, wcreg2 | WAVCACHE_CHCTL_STEREO);

	/* Load APU registers. */
	/* APU #0 : Sample rate converter for left/center. */
	apu_setparam(ch->parent, 0, WPWA_USE_SYSMEM | wpwa,
		     ch->buflen >> ch->stereo, 0, dv);
	wp_wrapu(ch->parent, 0, APUREG_AMPLITUDE, 0);
	wp_wrapu(ch->parent, 0, APUREG_ROUTING, 2 << APU_DATASRC_A_SHIFT);

	/* APU #1 : Sample rate converter for right. */
	apu_setparam(ch->parent, 1, WPWA_USE_SYSMEM | wpwa2,
		     ch->buflen >> ch->stereo, 0, dv);
	wp_wrapu(ch->parent, 1, APUREG_AMPLITUDE, 0);
	wp_wrapu(ch->parent, 1, APUREG_ROUTING, 3 << APU_DATASRC_A_SHIFT);

	/* APU #2 : Input mixer for left. */
	apu_setparam(ch->parent, 2, WPWA_USE_SYSMEM | 0,
		     ch->parent->bufsz >> 2, pan, 0x10000);
	wp_wrapu(ch->parent, 2, APUREG_AMPLITUDE, 0);
	wp_wrapu(ch->parent, 2, APUREG_EFFECT_GAIN, 0xf0);
	wp_wrapu(ch->parent, 2, APUREG_ROUTING, 0x15 << APU_DATASRC_A_SHIFT);

	/* APU #3 : Input mixer for right. */
	apu_setparam(ch->parent, 3, WPWA_USE_SYSMEM | (ch->parent->bufsz >> 2),
		     ch->parent->bufsz >> 2, -pan, 0x10000);
	wp_wrapu(ch->parent, 3, APUREG_AMPLITUDE, 0);
	wp_wrapu(ch->parent, 3, APUREG_EFFECT_GAIN, 0xf0);
	wp_wrapu(ch->parent, 3, APUREG_ROUTING, 0x14 << APU_DATASRC_A_SHIFT);

	/* to mark this channel ready for intr. */
	ch->parent->active |= (1 << ch->parent->playchns);

	/* start adc */
	critical_enter();
	wp_wrapu(ch->parent, 0, APUREG_APUTYPE,
	    (APUTYPE_RATECONV << APU_APUTYPE_SHIFT) | APU_DMA_ENABLED | 0xf);
	wp_wrapu(ch->parent, 1, APUREG_APUTYPE,
	    (APUTYPE_RATECONV << APU_APUTYPE_SHIFT) | APU_DMA_ENABLED | 0xf);
	wp_wrapu(ch->parent, 2, APUREG_APUTYPE,
	    (APUTYPE_INPUTMIXER << APU_APUTYPE_SHIFT) | 0xf);
	wp_wrapu(ch->parent, 3, APUREG_APUTYPE,
	    (APUTYPE_INPUTMIXER << APU_APUTYPE_SHIFT) | 0xf);
	critical_exit();

	set_timer(ch->parent);
	wp_starttimer(ch->parent);
	agg_unlock(ch->parent);
}