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
struct in_multi {scalar_t__ inm_timer; int inm_state; } ;

/* Variables and functions */
#define  IGMP_AWAKENING_MEMBER 137 
#define  IGMP_G_QUERY_PENDING_MEMBER 136 
#define  IGMP_IDLE_MEMBER 135 
#define  IGMP_LAZY_MEMBER 134 
#define  IGMP_LEAVING_MEMBER 133 
 int /*<<< orphan*/  IGMP_LOCK_ASSERT () ; 
#define  IGMP_NOT_MEMBER 132 
#define  IGMP_REPORTING_MEMBER 131 
#define  IGMP_SG_QUERY_PENDING_MEMBER 130 
#define  IGMP_SILENT_MEMBER 129 
#define  IGMP_SLEEPING_MEMBER 128 
 int const IGMP_VERSION_2 ; 
 int /*<<< orphan*/  IGMP_v1_HOST_MEMBERSHIP_REPORT ; 
 int /*<<< orphan*/  IGMP_v2_HOST_MEMBERSHIP_REPORT ; 
 int /*<<< orphan*/  IN_MULTI_LIST_LOCK_ASSERT () ; 
 int V_current_state_timers_running ; 
 int /*<<< orphan*/  igmp_v1v2_queue_report (struct in_multi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
igmp_v1v2_process_group_timer(struct in_multi *inm, const int version)
{
	int report_timer_expired;

	IN_MULTI_LIST_LOCK_ASSERT();
	IGMP_LOCK_ASSERT();

	if (inm->inm_timer == 0) {
		report_timer_expired = 0;
	} else if (--inm->inm_timer == 0) {
		report_timer_expired = 1;
	} else {
		V_current_state_timers_running = 1;
		return;
	}

	switch (inm->inm_state) {
	case IGMP_NOT_MEMBER:
	case IGMP_SILENT_MEMBER:
	case IGMP_IDLE_MEMBER:
	case IGMP_LAZY_MEMBER:
	case IGMP_SLEEPING_MEMBER:
	case IGMP_AWAKENING_MEMBER:
		break;
	case IGMP_REPORTING_MEMBER:
		if (report_timer_expired) {
			inm->inm_state = IGMP_IDLE_MEMBER;
			(void)igmp_v1v2_queue_report(inm,
			    (version == IGMP_VERSION_2) ?
			     IGMP_v2_HOST_MEMBERSHIP_REPORT :
			     IGMP_v1_HOST_MEMBERSHIP_REPORT);
		}
		break;
	case IGMP_G_QUERY_PENDING_MEMBER:
	case IGMP_SG_QUERY_PENDING_MEMBER:
	case IGMP_LEAVING_MEMBER:
		break;
	}
}