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
typedef  scalar_t__ u_int32_t ;
struct cam_periph {scalar_t__ scheduled_priority; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_run_allocq (struct cam_periph*,int /*<<< orphan*/ ) ; 

void
xpt_schedule(struct cam_periph *periph, u_int32_t new_priority)
{

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("xpt_schedule\n"));
	cam_periph_assert(periph, MA_OWNED);
	if (new_priority < periph->scheduled_priority) {
		periph->scheduled_priority = new_priority;
		xpt_run_allocq(periph, 0);
	}
}