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
struct cd_softc {int flags; int /*<<< orphan*/  toc; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int CD_FLAG_MEDIA_SCAN_ACT ; 
 int CD_FLAG_MEDIA_WAIT ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdmediaprobedone(struct cam_periph *periph)
{
	struct cd_softc *softc;

	softc = (struct cd_softc *)periph->softc;

	softc->flags &= ~CD_FLAG_MEDIA_SCAN_ACT;

	if ((softc->flags & CD_FLAG_MEDIA_WAIT) != 0) {
		softc->flags &= ~CD_FLAG_MEDIA_WAIT;
		wakeup(&softc->toc);
	}
}