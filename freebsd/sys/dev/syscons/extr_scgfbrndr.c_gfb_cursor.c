#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_6__ {scalar_t__ height; } ;
struct TYPE_7__ {int status; int xsize; TYPE_2__ curs_attr; TYPE_1__* sc; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_5__ {int /*<<< orphan*/ * adp; } ;

/* Variables and functions */
 int VR_CURSOR_BLINK ; 
 int VR_CURSOR_ON ; 
 int pxlblinkrate ; 
 int /*<<< orphan*/  vidd_set_hw_cursor (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void 
gfb_cursor(scr_stat *scp, int at, int blink, int on, int flip)
{
	video_adapter_t *adp;

	adp = scp->sc->adp;
	if (scp->curs_attr.height <= 0) 
		/* the text cursor is disabled */
		return;

	if (on) {
		if (!blink) {
			scp->status |= VR_CURSOR_ON;
			vidd_set_hw_cursor(adp, at%scp->xsize, at/scp->xsize);
		} else if (++pxlblinkrate & 4) {
			pxlblinkrate = 0;
			scp->status ^= VR_CURSOR_ON;
			if(scp->status & VR_CURSOR_ON)
				vidd_set_hw_cursor(adp, at%scp->xsize,
				    at/scp->xsize);
			else
				vidd_set_hw_cursor(adp, -1, -1);
		}
	} else {
		if (scp->status & VR_CURSOR_ON)
			vidd_set_hw_cursor(adp, at%scp->xsize, at/scp->xsize);
		scp->status &= ~VR_CURSOR_ON;
	}
	if (blink)
		scp->status |= VR_CURSOR_BLINK;
	else
		scp->status &= ~VR_CURSOR_BLINK;
}