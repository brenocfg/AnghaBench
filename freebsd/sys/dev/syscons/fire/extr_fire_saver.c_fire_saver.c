#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  va_line_width; int /*<<< orphan*/  va_window_size; scalar_t__ va_window; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  banksize ; 
 scalar_t__ blanked ; 
 int /*<<< orphan*/  bpsl ; 
 int /*<<< orphan*/  fire_pal ; 
 int /*<<< orphan*/  fire_update (TYPE_1__*) ; 
 int /*<<< orphan*/  scrmode ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/ * vid ; 
 int /*<<< orphan*/  vidd_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  vidd_load_palette (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidd_set_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fire_saver(video_adapter_t *adp, int blank)
{
	int pl;

	if (blank) {
		/* switch to graphics mode */
      		if (blanked <= 0) {
			pl = splhigh();
			vidd_set_mode(adp, scrmode);
			vidd_load_palette(adp, fire_pal);
			blanked++;
			vid = (u_char *)adp->va_window;
			banksize = adp->va_window_size;
			bpsl = adp->va_line_width;
			splx(pl);
			vidd_clear(adp);
		}
		fire_update(adp);
	} else {
		blanked = 0;
	}

    return 0;
}