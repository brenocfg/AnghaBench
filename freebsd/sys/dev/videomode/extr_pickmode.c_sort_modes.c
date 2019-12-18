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
struct videomode {int hdisplay; int vdisplay; int dot_clock; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  htotal; } ;

/* Variables and functions */
 int DIVIDE (int,int /*<<< orphan*/ ) ; 
 int abs (int) ; 
 int /*<<< orphan*/  swap_modes (struct videomode*,struct videomode*) ; 

void
sort_modes(struct videomode *modes, struct videomode **preferred, int nmodes)
{
	int aspect, refresh, hbest, vbest, abest, atemp, rbest, rtemp;
	int i, j;
	struct videomode *mtemp = NULL;

	if (nmodes < 2)
		return;

	if (*preferred != NULL) {
		/* Put the preferred mode first in the list */
		aspect = (*preferred)->hdisplay * 100 / (*preferred)->vdisplay;
		refresh = DIVIDE(DIVIDE((*preferred)->dot_clock * 1000,
		    (*preferred)->htotal), (*preferred)->vtotal);
		if (*preferred != modes) {
			swap_modes(*preferred, modes);
			*preferred = modes;
		}
	} else {
		/*
		 * Find the largest horizontal and vertical mode and put that
		 * first in the list.  Preferred refresh rate is taken from
		 * the first mode of this size.
		 */
		hbest = 0;
		vbest = 0;
		for (i = 0; i < nmodes; i++) {
			if (modes[i].hdisplay > hbest) {
				hbest = modes[i].hdisplay;
				vbest = modes[i].vdisplay;
				mtemp = &modes[i];
			} else if (modes[i].hdisplay == hbest &&
			    modes[i].vdisplay > vbest) {
				vbest = modes[i].vdisplay;
				mtemp = &modes[i];
			}
		}
		aspect = mtemp->hdisplay * 100 / mtemp->vdisplay;
		refresh = DIVIDE(DIVIDE(mtemp->dot_clock * 1000,
		    mtemp->htotal), mtemp->vtotal);
		if (mtemp != modes)
			swap_modes(mtemp, modes);
	}

	/* Sort other modes by refresh rate, aspect ratio, then resolution */
	for (j = 1; j < nmodes - 1; j++) {
		rbest = 1000;
		abest = 1000;
		hbest = 0;
		vbest = 0;
		for (i = j; i < nmodes; i++) {
			rtemp = abs(refresh -
			    DIVIDE(DIVIDE(modes[i].dot_clock * 1000,
			    modes[i].htotal), modes[i].vtotal));
			atemp = (modes[i].hdisplay * 100 / modes[i].vdisplay);
			if (rtemp < rbest) {
				rbest = rtemp;
				mtemp = &modes[i];
			}
			if (rtemp == rbest) {
				/* Treat "close" aspect ratios as identical */
				if (abs(abest - atemp) > (abest / 8) &&
				    abs(aspect - atemp) < abs(aspect - abest)) {
					abest = atemp;
					mtemp = &modes[i];
				}
				if (atemp == abest ||
				    abs(abest - atemp) <= (abest / 8)) {
					if (modes[i].hdisplay > hbest) {
						hbest = modes[i].hdisplay;
						mtemp = &modes[i];
					}
					if (modes[i].hdisplay == hbest &&
					    modes[i].vdisplay > vbest) {
						vbest = modes[i].vdisplay;
						mtemp = &modes[i];
					}
				}
			}
		}
		if (mtemp != &modes[j])
			swap_modes(mtemp, &modes[j]);
	}
}