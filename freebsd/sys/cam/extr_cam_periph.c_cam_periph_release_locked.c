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
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_periph_release_locked_buses (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

void
cam_periph_release_locked(struct cam_periph *periph)
{

	if (periph == NULL)
		return;

	xpt_lock_buses();
	cam_periph_release_locked_buses(periph);
	xpt_unlock_buses();
}