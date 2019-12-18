#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct camq {scalar_t__ generation; } ;
struct TYPE_4__ {scalar_t__ priority; scalar_t__ index; scalar_t__ generation; } ;
typedef  TYPE_1__ cam_pinfo ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_XPT ; 
 scalar_t__ CAM_UNQUEUED_INDEX ; 
 int /*<<< orphan*/  camq_change_priority (struct camq*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  camq_insert (struct camq*,TYPE_1__*) ; 

__attribute__((used)) static int
xpt_schedule_dev(struct camq *queue, cam_pinfo *pinfo,
		 u_int32_t new_priority)
{
	int retval;
	u_int32_t old_priority;

	CAM_DEBUG_PRINT(CAM_DEBUG_XPT, ("xpt_schedule_dev\n"));


	old_priority = pinfo->priority;

	/*
	 * Are we already queued?
	 */
	if (pinfo->index != CAM_UNQUEUED_INDEX) {
		/* Simply reorder based on new priority */
		if (new_priority < old_priority) {
			camq_change_priority(queue, pinfo->index,
					     new_priority);
			CAM_DEBUG_PRINT(CAM_DEBUG_XPT,
					("changed priority to %d\n",
					 new_priority));
			retval = 1;
		} else
			retval = 0;
	} else {
		/* New entry on the queue */
		if (new_priority < old_priority)
			pinfo->priority = new_priority;

		CAM_DEBUG_PRINT(CAM_DEBUG_XPT,
				("Inserting onto queue\n"));
		pinfo->generation = ++queue->generation;
		camq_insert(queue, pinfo);
		retval = 1;
	}
	return (retval);
}