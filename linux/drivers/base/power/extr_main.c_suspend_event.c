#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 TYPE_1__ PMSG_FREEZE ; 
 TYPE_1__ PMSG_HIBERNATE ; 
 TYPE_1__ PMSG_ON ; 
 TYPE_1__ PMSG_SUSPEND ; 
#define  PM_EVENT_RECOVER 131 
#define  PM_EVENT_RESTORE 130 
#define  PM_EVENT_RESUME 129 
#define  PM_EVENT_THAW 128 

__attribute__((used)) static pm_message_t suspend_event(pm_message_t resume_msg)
{
	switch (resume_msg.event) {
	case PM_EVENT_RESUME:
		return PMSG_SUSPEND;
	case PM_EVENT_THAW:
	case PM_EVENT_RESTORE:
		return PMSG_FREEZE;
	case PM_EVENT_RECOVER:
		return PMSG_HIBERNATE;
	}
	return PMSG_ON;
}