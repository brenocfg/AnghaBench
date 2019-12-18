#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int u_int ;
struct agg_chinfo {int speed; int phys; int base; int buflen; int num; TYPE_1__* parent; scalar_t__ qs16; scalar_t__ stereo; scalar_t__ us; } ;
typedef  int bus_addr_t ;
struct TYPE_10__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_APUTYPE ; 
 int APUTYPE_16BITLINEAR ; 
 int APUTYPE_16BITSTEREO ; 
 int APUTYPE_8BITLINEAR ; 
 int APUTYPE_8BITSTEREO ; 
 int APU_APUTYPE_SHIFT ; 
 int APU_DMA_ENABLED ; 
 int PAN_FRONT ; 
 int PAN_RIGHT ; 
 int WAVCACHE_BASEADDR_SHIFT ; 
 int WAVCACHE_CHCTL_ADDRTAG_MASK ; 
 int WAVCACHE_CHCTL_STEREO ; 
 int WAVCACHE_CHCTL_U8 ; 
 scalar_t__ WAVCACHE_WTBAR ; 
 int WPWA_STEREO ; 
 int WPWA_WTBAR_SHIFT (int) ; 
 int /*<<< orphan*/  agg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  agg_power (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  apu_setparam (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  powerstate_active ; 
 int /*<<< orphan*/  set_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  wc_wrchctl (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  wc_wrreg (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  wp_starttimer (TYPE_1__*) ; 
 int /*<<< orphan*/  wp_wrapu (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aggch_start_dac(struct agg_chinfo *ch)
{
	bus_addr_t	wpwa;
	u_int32_t	speed;
	u_int16_t	size, apuch, wtbar, wcreg, aputype;
	u_int		dv;
	int		pan;

	speed = ch->speed;
	wpwa = (ch->phys - ch->base) >> 1;
	wtbar = 0xc & (wpwa >> WPWA_WTBAR_SHIFT(2));
	wcreg = (ch->phys - 16) & WAVCACHE_CHCTL_ADDRTAG_MASK;
	size  = ch->buflen;
	apuch = (ch->num << 1) | 32;
	pan = PAN_RIGHT - PAN_FRONT;

	if (ch->stereo) {
		wcreg |= WAVCACHE_CHCTL_STEREO;
		if (ch->qs16) {
			aputype = APUTYPE_16BITSTEREO;
			wpwa >>= 1;
			size >>= 1;
			pan = -pan;
		} else
			aputype = APUTYPE_8BITSTEREO;
	} else {
		pan = 0;
		if (ch->qs16)
			aputype = APUTYPE_16BITLINEAR;
		else {
			aputype = APUTYPE_8BITLINEAR;
			speed >>= 1;
		}
	}
	if (ch->us)
		wcreg |= WAVCACHE_CHCTL_U8;

	if (wtbar > 8)
		wtbar = (wtbar >> 1) + 4;

	dv = (((speed % 48000) << 16) + 24000) / 48000
	    + ((speed / 48000) << 16);

	agg_lock(ch->parent);
	agg_power(ch->parent, powerstate_active);

	wc_wrreg(ch->parent, WAVCACHE_WTBAR + wtbar,
	    ch->base >> WAVCACHE_BASEADDR_SHIFT);
	wc_wrreg(ch->parent, WAVCACHE_WTBAR + wtbar + 1,
	    ch->base >> WAVCACHE_BASEADDR_SHIFT);
	if (wtbar < 8) {
		wc_wrreg(ch->parent, WAVCACHE_WTBAR + wtbar + 2,
		    ch->base >> WAVCACHE_BASEADDR_SHIFT);
		wc_wrreg(ch->parent, WAVCACHE_WTBAR + wtbar + 3,
		    ch->base >> WAVCACHE_BASEADDR_SHIFT);
	}
	wc_wrchctl(ch->parent, apuch, wcreg);
	wc_wrchctl(ch->parent, apuch + 1, wcreg);

	apu_setparam(ch->parent, apuch, wpwa, size, pan, dv);
	if (ch->stereo) {
		if (ch->qs16)
			wpwa |= (WPWA_STEREO >> 1);
		apu_setparam(ch->parent, apuch + 1, wpwa, size, -pan, dv);

		critical_enter();
		wp_wrapu(ch->parent, apuch, APUREG_APUTYPE,
		    (aputype << APU_APUTYPE_SHIFT) | APU_DMA_ENABLED | 0xf);
		wp_wrapu(ch->parent, apuch + 1, APUREG_APUTYPE,
		    (aputype << APU_APUTYPE_SHIFT) | APU_DMA_ENABLED | 0xf);
		critical_exit();
	} else {
		wp_wrapu(ch->parent, apuch, APUREG_APUTYPE,
		    (aputype << APU_APUTYPE_SHIFT) | APU_DMA_ENABLED | 0xf);
	}

	/* to mark that this channel is ready for intr. */
	ch->parent->active |= (1 << ch->num);

	set_timer(ch->parent);
	wp_starttimer(ch->parent);
	agg_unlock(ch->parent);
}