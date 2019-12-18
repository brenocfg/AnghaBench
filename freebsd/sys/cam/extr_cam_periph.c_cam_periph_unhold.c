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
struct cam_periph {int flags; } ;

/* Variables and functions */
 int CAM_PERIPH_LOCKED ; 
 int CAM_PERIPH_LOCK_WANTED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  wakeup (struct cam_periph*) ; 

void
cam_periph_unhold(struct cam_periph *periph)
{

	cam_periph_assert(periph, MA_OWNED);

	periph->flags &= ~CAM_PERIPH_LOCKED;
	if ((periph->flags & CAM_PERIPH_LOCK_WANTED) != 0) {
		periph->flags &= ~CAM_PERIPH_LOCK_WANTED;
		wakeup(periph);
	}

	cam_periph_release_locked(periph);
}