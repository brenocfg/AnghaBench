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
 TYPE_1__ PMSG_ON ; 
 TYPE_1__ PMSG_RECOVER ; 
 TYPE_1__ PMSG_RESTORE ; 
 TYPE_1__ PMSG_RESUME ; 
#define  PM_EVENT_FREEZE 131 
#define  PM_EVENT_HIBERNATE 130 
#define  PM_EVENT_QUIESCE 129 
#define  PM_EVENT_SUSPEND 128 

__attribute__((used)) static pm_message_t resume_event(pm_message_t sleep_state)
{
	switch (sleep_state.event) {
	case PM_EVENT_SUSPEND:
		return PMSG_RESUME;
	case PM_EVENT_FREEZE:
	case PM_EVENT_QUIESCE:
		return PMSG_RECOVER;
	case PM_EVENT_HIBERNATE:
		return PMSG_RESTORE;
	}
	return PMSG_ON;
}