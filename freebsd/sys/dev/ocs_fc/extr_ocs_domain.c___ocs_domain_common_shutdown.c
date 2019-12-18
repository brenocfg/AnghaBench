#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ocs_sm_event_t ;
struct TYPE_4__ {TYPE_2__* app; } ;
typedef  TYPE_1__ ocs_sm_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  ocs; int /*<<< orphan*/  domain_found_pending; int /*<<< orphan*/  pending_drec; } ;
typedef  TYPE_2__ ocs_domain_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  OCS_EVT_DOMAIN_FOUND 132 
#define  OCS_EVT_DOMAIN_LOST 131 
#define  OCS_EVT_ENTER 130 
#define  OCS_EVT_EXIT 129 
#define  OCS_EVT_REENTER 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_warn (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  ocs_sm_event_name (int) ; 

__attribute__((used)) static void *
__ocs_domain_common_shutdown(const char *funcname, ocs_sm_ctx_t *ctx, ocs_sm_event_t evt, void *arg)
{
	ocs_domain_t *domain = ctx->app;

	switch(evt) {
	case OCS_EVT_ENTER:
	case OCS_EVT_REENTER:
	case OCS_EVT_EXIT:
		break;
	case OCS_EVT_DOMAIN_FOUND:
		ocs_assert(arg, NULL);
		/* sm: / save drec, mark domain_found_pending */
		ocs_memcpy(&domain->pending_drec, arg, sizeof(domain->pending_drec));
		domain->domain_found_pending = TRUE;
		break;
	case OCS_EVT_DOMAIN_LOST: 
		/* clear drec available
		 * sm: unmark domain_found_pending */
		domain->domain_found_pending = FALSE;
		break;

	default:
		ocs_log_warn(domain->ocs, "%-20s %-20s not handled\n", funcname, ocs_sm_event_name(evt));
		break;
	}

	return NULL;
}