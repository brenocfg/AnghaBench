#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ min_pressure; int max_width; int max_pressure; int margin_top; int margin_right; int margin_bottom; int margin_left; int na_top; int na_right; int na_bottom; int na_left; int window_min; int window_max; int multiplicator; int weight_current; int weight_previous; int weight_len_squared; int div_min; int div_max; int div_len; int vscroll_hor_area; int vscroll_ver_area; int two_finger_scroll; int max_x; int max_y; int natural_scroll; int vscroll_div_min; int vscroll_div_max; int weight_previous_na; int div_max_na; } ;
struct TYPE_13__ {scalar_t__ window_min; int in_vscroll; } ;
struct psm_softc {TYPE_2__ syninfo; TYPE_5__ gesture; TYPE_3__* smoother; } ;
struct TYPE_11__ {int active; int start_x; int start_y; int queue_cursor; scalar_t__ queue_len; int avg_dx; int avg_dy; int squelch_x; int squelch_y; int is_fuzzy; TYPE_1__* queue; } ;
typedef  TYPE_3__ smoother_t ;
struct TYPE_12__ {int /*<<< orphan*/  button; } ;
typedef  TYPE_4__ mousestatus_t ;
typedef  TYPE_5__ gesture_t ;
struct TYPE_14__ {scalar_t__ p; int flags; int x; int y; int /*<<< orphan*/  w; } ;
typedef  TYPE_6__ finger_t ;
struct TYPE_9__ {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  MOUSE_BUTTON4DOWN ; 
 int /*<<< orphan*/  MOUSE_BUTTON5DOWN ; 
 int /*<<< orphan*/  MOUSE_BUTTON6DOWN ; 
 int /*<<< orphan*/  MOUSE_BUTTON7DOWN ; 
 int PSM_FINGER_FUZZY ; 
 scalar_t__ SYNAPTICS_PACKETQUEUE ; 
 int SYNAPTICS_QUEUE_CURSOR (int) ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int abs (int) ; 
 int imax (int,int) ; 
 int imin (int,int) ; 

__attribute__((used)) static void
psmsmoother(struct psm_softc *sc, finger_t *f, int smoother_id,
    mousestatus_t *ms, int *x, int *y)
{
	smoother_t *smoother = &sc->smoother[smoother_id];
	gesture_t *gest = &(sc->gesture);

	/*
	 * Check pressure to detect a real wanted action on the
	 * touchpad.
	 */
	if (f->p >= sc->syninfo.min_pressure) {
		int x0, y0;
		int cursor, peer, window;
		int dx, dy, dxp, dyp;
		int max_width, max_pressure;
		int margin_top, margin_right, margin_bottom, margin_left;
		int na_top, na_right, na_bottom, na_left;
		int window_min, window_max;
		int multiplicator;
		int weight_current, weight_previous, weight_len_squared;
		int div_min, div_max, div_len;
		int vscroll_hor_area, vscroll_ver_area;
		int two_finger_scroll;
		int max_x, max_y;
		int len, weight_prev_x, weight_prev_y;
		int div_max_x, div_max_y, div_x, div_y;
		int is_fuzzy;
		int natural_scroll;

		/* Read sysctl. */
		/* XXX Verify values? */
		max_width = sc->syninfo.max_width;
		max_pressure = sc->syninfo.max_pressure;
		margin_top = sc->syninfo.margin_top;
		margin_right = sc->syninfo.margin_right;
		margin_bottom = sc->syninfo.margin_bottom;
		margin_left = sc->syninfo.margin_left;
		na_top = sc->syninfo.na_top;
		na_right = sc->syninfo.na_right;
		na_bottom = sc->syninfo.na_bottom;
		na_left = sc->syninfo.na_left;
		window_min = sc->syninfo.window_min;
		window_max = sc->syninfo.window_max;
		multiplicator = sc->syninfo.multiplicator;
		weight_current = sc->syninfo.weight_current;
		weight_previous = sc->syninfo.weight_previous;
		weight_len_squared = sc->syninfo.weight_len_squared;
		div_min = sc->syninfo.div_min;
		div_max = sc->syninfo.div_max;
		div_len = sc->syninfo.div_len;
		vscroll_hor_area = sc->syninfo.vscroll_hor_area;
		vscroll_ver_area = sc->syninfo.vscroll_ver_area;
		two_finger_scroll = sc->syninfo.two_finger_scroll;
		max_x = sc->syninfo.max_x;
		max_y = sc->syninfo.max_y;
		natural_scroll = sc->syninfo.natural_scroll;

		is_fuzzy = (f->flags & PSM_FINGER_FUZZY) != 0;

		/* Read current absolute position. */
		x0 = f->x;
		y0 = f->y;

		/*
		 * Limit the coordinates to the specified margins because
		 * this area isn't very reliable.
		 */
		if (x0 <= margin_left)
			x0 = margin_left;
		else if (x0 >= max_x - margin_right)
			x0 = max_x - margin_right;
		if (y0 <= margin_bottom)
			y0 = margin_bottom;
		else if (y0 >= max_y - margin_top)
			y0 = max_y - margin_top;

		/* If the action is just beginning, init the structure. */
		if (smoother->active == 0) {
			VLOG(3, (LOG_DEBUG, "smoother%d: ---\n", smoother_id));

			/* Store the first point of this action. */
			smoother->start_x = x0;
			smoother->start_y = y0;
			dx = dy = 0;

			/* Initialize queue. */
			smoother->queue_cursor = SYNAPTICS_PACKETQUEUE;
			smoother->queue_len = 0;

			/* Reset average. */
			smoother->avg_dx = 0;
			smoother->avg_dy = 0;

			/* Reset squelch. */
			smoother->squelch_x = 0;
			smoother->squelch_y = 0;

			/* Activate queue */
			smoother->active = 1;
		} else {
			/* Calculate the current delta. */
			cursor = smoother->queue_cursor;
			dx = x0 - smoother->queue[cursor].x;
			dy = y0 - smoother->queue[cursor].y;
		}

		VLOG(3, (LOG_DEBUG, "smoother%d: ipacket: [%d, %d], %d, %d\n",
		    smoother_id, x0, y0, f->p, f->w));

		/* Queue this new packet. */
		cursor = SYNAPTICS_QUEUE_CURSOR(smoother->queue_cursor - 1);
		smoother->queue[cursor].x = x0;
		smoother->queue[cursor].y = y0;
		smoother->queue_cursor = cursor;
		if (smoother->queue_len < SYNAPTICS_PACKETQUEUE)
			smoother->queue_len++;
		VLOG(5, (LOG_DEBUG,
		    "smoother%d: cursor[%d]: x=%d, y=%d, dx=%d, dy=%d\n",
		    smoother_id, cursor, x0, y0, dx, dy));

		/* Do we have enough packets to consider this a movement? */
		if (smoother->queue_len < gest->window_min)
			return;

		weight_prev_x = weight_prev_y = weight_previous;
		div_max_x = div_max_y = div_max;

		if (gest->in_vscroll) {
			/* Dividers are different with virtual scrolling. */
			div_min = sc->syninfo.vscroll_div_min;
			div_max_x = div_max_y = sc->syninfo.vscroll_div_max;
		} else {
			/*
			 * There's a lot of noise in coordinates when
			 * the finger is on the touchpad's borders. When
			 * using this area, we apply a special weight and
			 * div.
			 */
			if (x0 <= na_left || x0 >= max_x - na_right) {
				weight_prev_x = sc->syninfo.weight_previous_na;
				div_max_x = sc->syninfo.div_max_na;
			}

			if (y0 <= na_bottom || y0 >= max_y - na_top) {
				weight_prev_y = sc->syninfo.weight_previous_na;
				div_max_y = sc->syninfo.div_max_na;
			}
		}

		/*
		 * Calculate weights for the average operands and
		 * the divisor. Both depend on the distance between
		 * the current packet and a previous one (based on the
		 * window width).
		 */
		window = imin(smoother->queue_len, window_max);
		peer = SYNAPTICS_QUEUE_CURSOR(cursor + window - 1);
		dxp = abs(x0 - smoother->queue[peer].x) + 1;
		dyp = abs(y0 - smoother->queue[peer].y) + 1;
		len = (dxp * dxp) + (dyp * dyp);
		weight_prev_x = imin(weight_prev_x,
		    weight_len_squared * weight_prev_x / len);
		weight_prev_y = imin(weight_prev_y,
		    weight_len_squared * weight_prev_y / len);

		len = (dxp + dyp) / 2;
		div_x = div_len * div_max_x / len;
		div_x = imin(div_max_x, div_x);
		div_x = imax(div_min, div_x);
		div_y = div_len * div_max_y / len;
		div_y = imin(div_max_y, div_y);
		div_y = imax(div_min, div_y);

		VLOG(3, (LOG_DEBUG,
		    "smoother%d: peer=%d, len=%d, weight=%d/%d, div=%d/%d\n",
		    smoother_id, peer, len, weight_prev_x, weight_prev_y,
		    div_x, div_y));

		/* Compute averages. */
		smoother->avg_dx =
		    (weight_current * dx * multiplicator +
		     weight_prev_x * smoother->avg_dx) /
		    (weight_current + weight_prev_x);

		smoother->avg_dy =
		    (weight_current * dy * multiplicator +
		     weight_prev_y * smoother->avg_dy) /
		    (weight_current + weight_prev_y);

		VLOG(5, (LOG_DEBUG,
		    "smoother%d: avg_dx~=%d, avg_dy~=%d\n", smoother_id,
		    smoother->avg_dx / multiplicator,
		    smoother->avg_dy / multiplicator));

		/* Use these averages to calculate x & y. */
		smoother->squelch_x += smoother->avg_dx;
		dxp = smoother->squelch_x / (div_x * multiplicator);
		smoother->squelch_x = smoother->squelch_x %
		    (div_x * multiplicator);

		smoother->squelch_y += smoother->avg_dy;
		dyp = smoother->squelch_y / (div_y * multiplicator);
		smoother->squelch_y = smoother->squelch_y %
		    (div_y * multiplicator);

		switch(gest->in_vscroll) {
		case 0: /* Pointer movement. */
			/* On real<->fuzzy finger switch the x/y pos jumps */
			if (is_fuzzy == smoother->is_fuzzy) {
				*x += dxp;
				*y += dyp;
			}

			VLOG(3, (LOG_DEBUG, "smoother%d: [%d, %d] -> [%d, %d]\n",
			    smoother_id, dx, dy, dxp, dyp));
			break;
		case 1: /* Vertical scrolling. */
			if (dyp != 0) {
				if (two_finger_scroll && natural_scroll)
					ms->button |= (dyp > 0) ?
					    MOUSE_BUTTON5DOWN : MOUSE_BUTTON4DOWN;
				else
					ms->button |= (dyp > 0) ?
					    MOUSE_BUTTON4DOWN : MOUSE_BUTTON5DOWN;
			}
			break;
		case 2: /* Horizontal scrolling. */
			if (dxp != 0) {
				if (two_finger_scroll && natural_scroll)
					ms->button |= (dxp > 0) ?
					    MOUSE_BUTTON6DOWN : MOUSE_BUTTON7DOWN;
				else
					ms->button |= (dxp > 0) ?
					    MOUSE_BUTTON7DOWN : MOUSE_BUTTON6DOWN;
			}
			break;
		}

		smoother->is_fuzzy = is_fuzzy;

	} else {
		/*
		 * Deactivate queue. Note: We can not just reset queue here
		 * as these values are still used by gesture processor.
		 * So postpone reset till next touch.
		 */
		smoother->active = 0;
	}
}