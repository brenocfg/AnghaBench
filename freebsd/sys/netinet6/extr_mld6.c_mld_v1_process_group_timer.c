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
struct in6_multi_head {int dummy; } ;
struct in6_multi {scalar_t__ in6m_timer; int in6m_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_MULTI_LIST_LOCK_ASSERT () ; 
#define  MLD_AWAKENING_MEMBER 137 
#define  MLD_G_QUERY_PENDING_MEMBER 136 
#define  MLD_IDLE_MEMBER 135 
#define  MLD_LAZY_MEMBER 134 
#define  MLD_LEAVING_MEMBER 133 
 int /*<<< orphan*/  MLD_LOCK_ASSERT () ; 
#define  MLD_NOT_MEMBER 132 
#define  MLD_REPORTING_MEMBER 131 
#define  MLD_SG_QUERY_PENDING_MEMBER 130 
#define  MLD_SILENT_MEMBER 129 
#define  MLD_SLEEPING_MEMBER 128 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct in6_multi_head*,struct in6_multi*,int /*<<< orphan*/ ) ; 
 int V_current_state_timers_running6 ; 
 int /*<<< orphan*/  in6m_defer ; 

__attribute__((used)) static void
mld_v1_process_group_timer(struct in6_multi_head *inmh, struct in6_multi *inm)
{
	int report_timer_expired;

	IN6_MULTI_LIST_LOCK_ASSERT();
	MLD_LOCK_ASSERT();

	if (inm->in6m_timer == 0) {
		report_timer_expired = 0;
	} else if (--inm->in6m_timer == 0) {
		report_timer_expired = 1;
	} else {
		V_current_state_timers_running6 = 1;
		return;
	}

	switch (inm->in6m_state) {
	case MLD_NOT_MEMBER:
	case MLD_SILENT_MEMBER:
	case MLD_IDLE_MEMBER:
	case MLD_LAZY_MEMBER:
	case MLD_SLEEPING_MEMBER:
	case MLD_AWAKENING_MEMBER:
		break;
	case MLD_REPORTING_MEMBER:
		if (report_timer_expired) {
			inm->in6m_state = MLD_IDLE_MEMBER;
			SLIST_INSERT_HEAD(inmh, inm, in6m_defer);
		}
		break;
	case MLD_G_QUERY_PENDING_MEMBER:
	case MLD_SG_QUERY_PENDING_MEMBER:
	case MLD_LEAVING_MEMBER:
		break;
	}
}