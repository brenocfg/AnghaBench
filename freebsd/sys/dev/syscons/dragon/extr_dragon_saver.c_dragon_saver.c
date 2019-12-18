#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ va_window; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ CURVE ; 
 int /*<<< orphan*/  VIDEO_MODE ; 
 scalar_t__ blanked ; 
 scalar_t__ curve ; 
 int /*<<< orphan*/  dragon_update (TYPE_1__*) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/ * vid ; 
 int /*<<< orphan*/  vidd_set_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dragon_saver(video_adapter_t *adp, int blank)
{
	int pl;

	if (blank) {
		/* switch to graphics mode */
		if (blanked <= 0) {
			pl = splhigh();
			vidd_set_mode(adp, VIDEO_MODE);
			vid = (u_char *)adp->va_window;
			curve = CURVE + 1;
			++blanked;
			splx(pl);
		}

		/* update display */
		dragon_update(adp);
	}
	else {
		blanked = 0;
	}
	return 0;
}