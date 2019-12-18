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
typedef  int uint16_t ;
struct cyapa_softc {int cap_resy; int track_nfingers; scalar_t__ finger1_ticks; scalar_t__ poll_ticks; scalar_t__ finger2_ticks; scalar_t__ finger3_ticks; int track_x; int track_y; int track_z; int touch_x; int touch_y; int touch_z; int track_id; int track_but; scalar_t__ track_z_ticks; int delta_z; int delta_x; int delta_y; int cap_resx; int reported_but; unsigned int active_tick; scalar_t__ remote_mode; int data_signal; scalar_t__ reporting_mode; scalar_t__ fuzz_z; scalar_t__ fuzz_y; scalar_t__ fuzz_x; } ;
struct cyapa_regs {int stat; int fngr; TYPE_1__* touch; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int CYAPA_FNGR_LEFT ; 
 int CYAPA_FNGR_MIDDLE ; 
 int CYAPA_FNGR_NUMFINGERS (int) ; 
 int CYAPA_FNGR_RIGHT ; 
 int CYAPA_STAT_RUNNING ; 
 int CYAPA_TOUCH_P (struct cyapa_regs*,int) ; 
 int CYAPA_TOUCH_X (struct cyapa_regs*,int) ; 
 int CYAPA_TOUCH_Y (struct cyapa_regs*,int) ; 
 unsigned int TIME_TO_IDLE ; 
 int ZSCALE ; 
 int abs (int) ; 
 scalar_t__ cyapa_debug ; 
 int cyapa_enable_tapclick ; 
 int /*<<< orphan*/  cyapa_lock (struct cyapa_softc*) ; 
 int cyapa_minpressure ; 
 scalar_t__ cyapa_move_min_ticks ; 
 int cyapa_norm_freq ; 
 int /*<<< orphan*/  cyapa_notify (struct cyapa_softc*) ; 
 scalar_t__ cyapa_scroll_stick_ticks ; 
 scalar_t__ cyapa_scroll_wait_ticks ; 
 scalar_t__ cyapa_tapclick_max_ticks ; 
 scalar_t__ cyapa_tapclick_min_ticks ; 
 int cyapa_thumbarea_percent ; 
 int /*<<< orphan*/  cyapa_unlock (struct cyapa_softc*) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 unsigned int ticks ; 

__attribute__((used)) static int
cyapa_raw_input(struct cyapa_softc *sc, struct cyapa_regs *regs, int freq)
{
	int nfingers;
	int afingers;	/* actual fingers after culling */
	int i;
	int j;
	int k;
	int isidle;
	int thumbarea_begin;
	int seen_thumb;
	int x;
	int y;
	int z;
	int newfinger;
	int lessfingers;
	int click_x;
	int click_y;
	uint16_t but;	/* high bits used for simulated but4/but5 */

	thumbarea_begin = sc->cap_resy -
	    ((sc->cap_resy *  cyapa_thumbarea_percent) / 100);
	click_x = click_y = 0;

	/*
	 * If the device is not running the rest of the status
	 * means something else, set fingers to 0.
	 */
	if ((regs->stat & CYAPA_STAT_RUNNING) == 0) {
		regs->fngr = 0;
	}

	/* Process fingers/movement */
	nfingers = CYAPA_FNGR_NUMFINGERS(regs->fngr);
	afingers = nfingers;

	if (cyapa_debug) {
		printf("stat %02x buttons %c%c%c nfngrs=%d ",
		    regs->stat,
		    ((regs->fngr & CYAPA_FNGR_LEFT) ? 'L' : '-'),
		    ((regs->fngr & CYAPA_FNGR_MIDDLE) ? 'M' : '-'),
		    ((regs->fngr & CYAPA_FNGR_RIGHT) ? 'R' : '-'),
		    nfingers);
	}

	seen_thumb = 0;
	for (i = 0; i < afingers; ) {
		if (cyapa_debug) {
			printf(" [x=%04d y=%04d p=%d i=%d]",
			    CYAPA_TOUCH_X(regs, i),
			    CYAPA_TOUCH_Y(regs, i),
			    CYAPA_TOUCH_P(regs, i),
			    regs->touch[i].id);
		}
		if ((CYAPA_TOUCH_Y(regs, i) > thumbarea_begin && seen_thumb) ||
		     CYAPA_TOUCH_P(regs, i) < cyapa_minpressure) {
			--afingers;
			if (i < afingers) {
			    regs->touch[i] = regs->touch[i+1];
			    continue;
			}
		} else {
			if (CYAPA_TOUCH_Y(regs, i) > thumbarea_begin)
			    seen_thumb = 1;
		}
		++i;
	}
	nfingers = afingers;

	/* Tracking for local solutions */
	cyapa_lock(sc);

	/*
	 * Track timing for finger-downs.  Used to detect false-3-finger
	 * button-down.
	 */
	switch(afingers) {
	case 0:
		break;
	case 1:
		if (sc->track_nfingers == 0)
			sc->finger1_ticks = sc->poll_ticks;
		break;
	case 2:
		if (sc->track_nfingers <= 0)
			sc->finger1_ticks = sc->poll_ticks;
		if (sc->track_nfingers <= 1)
			sc->finger2_ticks = sc->poll_ticks;
		break;
	case 3:
	default:
		if (sc->track_nfingers <= 0)
			sc->finger1_ticks = sc->poll_ticks;
		if (sc->track_nfingers <= 1)
			sc->finger2_ticks = sc->poll_ticks;
		if (sc->track_nfingers <= 2)
			sc->finger3_ticks = sc->poll_ticks;
		break;
	}
	newfinger = sc->track_nfingers < afingers;
	lessfingers = sc->track_nfingers > afingers;
	sc->track_nfingers = afingers;

	/*
	 * Lookup and track finger indexes in the touch[] array.
	 */
	if (afingers == 0) {
		click_x = sc->track_x;
		click_y = sc->track_y;
		sc->track_x = -1;
		sc->track_y = -1;
		sc->track_z = -1;
		sc->fuzz_x = 0;
		sc->fuzz_y = 0;
		sc->fuzz_z = 0;
		sc->touch_x = -1;
		sc->touch_y = -1;
		sc->touch_z = -1;
		sc->track_id = -1;
		sc->track_but = 0;
		i = 0;
		j = 0;
		k = 0;
	} else {
		/*
		 * The id assigned on touch can move around in the array,
		 * find it.  If that finger is lifted up, assign some other
		 * finger for mouse tracking and reset track_x and track_y
		 * to avoid a mouse jump.
		 *
		 * If >= 2 fingers are down be sure not to assign i and
		 * j to the same index.
		 */
		for (i = 0; i < nfingers; ++i) {
			if (sc->track_id == regs->touch[i].id)
				break;
		}
		if (i == nfingers) {
			i = 0;
			sc->track_x = -1;
			sc->track_y = -1;
			sc->track_z = -1;
			while (CYAPA_TOUCH_Y(regs, i) >= thumbarea_begin &&
			    i < nfingers) ++i;
			if (i == nfingers) {
				i = 0;
			}
			sc->track_id = regs->touch[i].id;
		}
		else if ((sc->track_but ||
		     CYAPA_TOUCH_Y(regs, i) >= thumbarea_begin) &&
		    newfinger && afingers == 2) {
			j = regs->touch[0].id == sc->track_id ? 1 : 0;
			if (CYAPA_TOUCH_Y(regs, j) < thumbarea_begin) {
			    i = j;
			    sc->track_x = -1;
			    sc->track_y = -1;
			    sc->track_z = -1;
			    sc->track_id = regs->touch[i].id;
			}
		}
	}

	/* Two finger scrolling - reset after timeout */
	if (sc->track_z != -1 && afingers != 2 &&
	    (sc->poll_ticks - sc->track_z_ticks) > cyapa_scroll_stick_ticks) {
		sc->track_z = -1;
		sc->track_z_ticks = 0;
	}

	/* Initiate two finger scrolling */
	if (!(regs->fngr & CYAPA_FNGR_LEFT) &&
	    ((afingers && sc->track_z != -1) ||
	     (afingers == 2 && CYAPA_TOUCH_Y(regs, 0) < thumbarea_begin &&
	     CYAPA_TOUCH_Y(regs, 1) < thumbarea_begin))) {
		if (afingers == 2 && (sc->poll_ticks - sc->finger2_ticks)
		    > cyapa_scroll_wait_ticks) {
			z = (CYAPA_TOUCH_Y(regs, 0) +
			    CYAPA_TOUCH_Y(regs, 1)) >> 1;
			sc->delta_z += z / ZSCALE - sc->track_z;
			if (sc->track_z == -1) {
			    sc->delta_z = 0;
			}
			if (sc->touch_z == -1)
			    sc->touch_z = z;	/* not used atm */
			sc->track_z = z / ZSCALE;
			sc->track_z_ticks = sc->poll_ticks;
		}
	} else if (afingers) {
		/* Normal pad position reporting */
		x = CYAPA_TOUCH_X(regs, i);
		y = CYAPA_TOUCH_Y(regs, i);
		click_x = x;
		click_y = y;
		if (sc->track_x != -1 && sc->track_y < thumbarea_begin &&
		    (afingers > 1 || (sc->poll_ticks - sc->finger1_ticks)
		    >= cyapa_move_min_ticks || freq < cyapa_norm_freq)) {
			sc->delta_x += x - sc->track_x;
			sc->delta_y -= y - sc->track_y;
			if (sc->delta_x > sc->cap_resx)
				sc->delta_x = sc->cap_resx;
			if (sc->delta_x < -sc->cap_resx)
				sc->delta_x = -sc->cap_resx;
			if (sc->delta_y > sc->cap_resy)
				sc->delta_y = sc->cap_resy;
			if (sc->delta_y < -sc->cap_resy)
				sc->delta_y = -sc->cap_resy;

			if (abs(sc->delta_y) > sc->cap_resy / 2 ||
			    abs(sc->delta_x) > sc->cap_resx / 2) {
				if (cyapa_debug)
					printf("Detected jump by %i %i\n",
					    sc->delta_x, sc->delta_y);
			    sc->delta_x = sc->delta_y = 0;
			}
		}
		if (sc->touch_x == -1) {
			sc->touch_x = x;
			sc->touch_y = y;
		}
		sc->track_x = x;
		sc->track_y = y;
	}

	/* Select finger (L = 2/3x, M = 1/3u, R = 1/3d) */
	int is_tapclick = (cyapa_enable_tapclick && lessfingers &&
	    afingers == 0 && sc->poll_ticks - sc->finger1_ticks
	    >= cyapa_tapclick_min_ticks &&
	    sc->poll_ticks - sc->finger1_ticks < cyapa_tapclick_max_ticks);

	if (regs->fngr & CYAPA_FNGR_LEFT || is_tapclick) {
		if (sc->track_but) {
			but = sc->track_but;
		} else if (afingers == 1) {
			if (click_x < sc->cap_resx * 2 / 3)
				but = CYAPA_FNGR_LEFT;
			else if (click_y < sc->cap_resy / 2)
				but = CYAPA_FNGR_MIDDLE;
			else
				but = CYAPA_FNGR_RIGHT;
		} else if (is_tapclick) {
			if (click_x < sc->cap_resx * 2 / 3 ||
			    cyapa_enable_tapclick < 2)
				but = CYAPA_FNGR_LEFT;
			else if (click_y < sc->cap_resy / 2 &&
			    cyapa_enable_tapclick > 2)
				but = CYAPA_FNGR_MIDDLE;
			else
				but = CYAPA_FNGR_RIGHT;
		} else {
			but = CYAPA_FNGR_LEFT;
		}
	} else {
		but = 0;
	}

	/*
	 * Detect state change from last reported state and
	 * determine if we have gone idle.
	 */
	sc->track_but = but;
	if (sc->delta_x || sc->delta_y || sc->delta_z ||
	    sc->track_but != sc->reported_but) {
		sc->active_tick = ticks;
		if (sc->remote_mode == 0 && sc->reporting_mode)
			sc->data_signal = 1;
		isidle = 0;
	} else if ((unsigned)(ticks - sc->active_tick) >= TIME_TO_IDLE) {
		sc->active_tick = ticks - TIME_TO_IDLE; /* prevent overflow */
		isidle = 1;
	} else {
		isidle = 0;
	}
	cyapa_notify(sc);
	cyapa_unlock(sc);

	if (cyapa_debug)
		printf("%i >> %i << %i\n", isidle, sc->track_id, sc->delta_y);
	return (isidle);
}