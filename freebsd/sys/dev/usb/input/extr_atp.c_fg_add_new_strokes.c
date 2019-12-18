#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct atp_softc {int dummy; } ;
struct TYPE_6__ {int matched; size_t cum; } ;
typedef  TYPE_1__ fg_pspan ;
typedef  size_t atp_axis ;

/* Variables and functions */
 int FG_MAX_PSPANS_PER_AXIS ; 
 size_t X ; 
 size_t Y ; 
 size_t abs (size_t) ; 
 int /*<<< orphan*/  fg_add_stroke (struct atp_softc*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
fg_add_new_strokes(struct atp_softc *sc, fg_pspan *pspans_x,
    u_int n_xpspans, fg_pspan *pspans_y, u_int n_ypspans)
{
	fg_pspan spans[2][FG_MAX_PSPANS_PER_AXIS];
	u_int nspans[2];
	u_int i;
	u_int j;

	/* Copy unmatched pspans into the local arrays. */
	for (i = 0, nspans[X] = 0; i < n_xpspans; i++) {
		if (pspans_x[i].matched == false) {
			spans[X][nspans[X]] = pspans_x[i];
			nspans[X]++;
		}
	}
	for (j = 0, nspans[Y] = 0; j < n_ypspans; j++) {
		if (pspans_y[j].matched == false) {
			spans[Y][nspans[Y]] = pspans_y[j];
			nspans[Y]++;
		}
	}

	if (nspans[X] == nspans[Y]) {
		/* Create new strokes from pairs of unmatched pspans */
		for (i = 0, j = 0; (i < nspans[X]) && (j < nspans[Y]); i++, j++)
			fg_add_stroke(sc, &spans[X][i], &spans[Y][j]);
	} else {
		u_int    cum = 0;
		atp_axis repeat_axis;      /* axis with multi-pspans */
		u_int    repeat_count;     /* repeat count for the multi-pspan*/
		u_int    repeat_index = 0; /* index of the multi-span */

		repeat_axis  = (nspans[X] > nspans[Y]) ? Y : X;
		repeat_count = abs(nspans[X] - nspans[Y]);
		for (i = 0; i < nspans[repeat_axis]; i++) {
			if (spans[repeat_axis][i].cum > cum) {
				repeat_index = i;
				cum = spans[repeat_axis][i].cum;
			}
		}

		/* Create new strokes from pairs of unmatched pspans */
		i = 0, j = 0;
		for (; (i < nspans[X]) && (j < nspans[Y]); i++, j++) {
			fg_add_stroke(sc, &spans[X][i], &spans[Y][j]);

			/* Take care to repeat at the multi-pspan. */
			if (repeat_count > 0) {
				if ((repeat_axis == X) &&
				    (repeat_index == i)) {
					i--; /* counter loop increment */
					repeat_count--;
				} else if ((repeat_axis == Y) &&
				    (repeat_index == j)) {
					j--; /* counter loop increment */
					repeat_count--;
				}
			}
		}
	}
}