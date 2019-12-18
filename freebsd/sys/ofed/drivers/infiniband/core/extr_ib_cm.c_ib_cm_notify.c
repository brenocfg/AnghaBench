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
struct ib_cm_id {int dummy; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_EVENT_COMM_EST 129 
#define  IB_EVENT_PATH_MIG 128 
 int cm_establish (struct ib_cm_id*) ; 
 int cm_migrate (struct ib_cm_id*) ; 

int ib_cm_notify(struct ib_cm_id *cm_id, enum ib_event_type event)
{
	int ret;

	switch (event) {
	case IB_EVENT_COMM_EST:
		ret = cm_establish(cm_id);
		break;
	case IB_EVENT_PATH_MIG:
		ret = cm_migrate(cm_id);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}