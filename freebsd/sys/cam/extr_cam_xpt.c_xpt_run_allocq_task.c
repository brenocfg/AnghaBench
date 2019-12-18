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
struct cam_periph {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PERIPH_RUN_TASK ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_run_allocq (struct cam_periph*,int) ; 

__attribute__((used)) static void
xpt_run_allocq_task(void *context, int pending)
{
	struct cam_periph *periph = context;

	cam_periph_lock(periph);
	periph->flags &= ~CAM_PERIPH_RUN_TASK;
	xpt_run_allocq(periph, 1);
	cam_periph_unlock(periph);
	cam_periph_release(periph);
}