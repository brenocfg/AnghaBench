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
struct cam_periph {int flags; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int CAM_PERIPH_INVALID ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

int
cam_periph_acquire(struct cam_periph *periph)
{
	int status;

	if (periph == NULL)
		return (EINVAL);

	status = ENOENT;
	xpt_lock_buses();
	if ((periph->flags & CAM_PERIPH_INVALID) == 0) {
		periph->refcount++;
		status = 0;
	}
	xpt_unlock_buses();

	return (status);
}