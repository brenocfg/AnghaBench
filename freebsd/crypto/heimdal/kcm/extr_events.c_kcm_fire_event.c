#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_9__ {int action; scalar_t__ fire_time; int backoff_time; scalar_t__ expire_time; TYPE_5__* ccache; int /*<<< orphan*/  fire_count; } ;
typedef  TYPE_1__ kcm_event ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  client; } ;

/* Variables and functions */
#define  KCM_EVENT_ACQUIRE_CREDS 131 
#define  KCM_EVENT_DESTROY_CREDS 130 
#define  KCM_EVENT_DESTROY_EMPTY_CACHE 129 
 int KCM_EVENT_MAX_BACKOFF_TIME ; 
 int const KCM_EVENT_NONE ; 
#define  KCM_EVENT_RENEW_CREDS 128 
 scalar_t__ KRB5KRB_AP_ERR_TKT_EXPIRED ; 
 scalar_t__ KRB5_FCC_INTERNAL ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kcm_ccache_acquire (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ **) ; 
 scalar_t__ kcm_ccache_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kcm_ccache_destroy_if_empty (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ kcm_ccache_make_default_event (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kcm_ccache_refresh (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kcm_log (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kcm_remove_event_internal (int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  log_event (TYPE_1__*,char*) ; 

__attribute__((used)) static krb5_error_code
kcm_fire_event(krb5_context context,
	       kcm_event **e)
{
    kcm_event *event;
    krb5_error_code ret;
    krb5_creds *credp = NULL;
    int oneshot = 1;

    event = *e;

    switch (event->action) {
    case KCM_EVENT_ACQUIRE_CREDS:
	ret = kcm_ccache_acquire(context, event->ccache, &credp);
	oneshot = 0;
	break;
    case KCM_EVENT_RENEW_CREDS:
	ret = kcm_ccache_refresh(context, event->ccache, &credp);
	if (ret == KRB5KRB_AP_ERR_TKT_EXPIRED) {
	    ret = kcm_ccache_acquire(context, event->ccache, &credp);
	}
	oneshot = 0;
	break;
    case KCM_EVENT_DESTROY_CREDS:
	ret = kcm_ccache_destroy(context, event->ccache->name);
	break;
    case KCM_EVENT_DESTROY_EMPTY_CACHE:
	ret = kcm_ccache_destroy_if_empty(context, event->ccache);
	break;
    default:
	ret = KRB5_FCC_INTERNAL;
	break;
    }

    event->fire_count++;

    if (ret) {
	/* Reschedule failed event for another time */
	event->fire_time += event->backoff_time;
	if (event->backoff_time < KCM_EVENT_MAX_BACKOFF_TIME)
	    event->backoff_time *= 2;

	/* Remove it if it would never get executed */
	if (event->expire_time &&
	    event->fire_time > event->expire_time)
	    kcm_remove_event_internal(context, e);
    } else {
	if (!oneshot) {
	    char *cpn;

	    if (krb5_unparse_name(context, event->ccache->client,
				  &cpn))
		cpn = NULL;

	    kcm_log(0, "%s credentials in cache %s for principal %s",
		    (event->action == KCM_EVENT_ACQUIRE_CREDS) ?
			"Acquired" : "Renewed",
		    event->ccache->name,
		    (cpn != NULL) ? cpn : "<none>");

	    if (cpn != NULL)
		free(cpn);

	    /* Succeeded, but possibly replaced with another event */
	    ret = kcm_ccache_make_default_event(context, event, credp);
	    if (ret || event->action == KCM_EVENT_NONE)
		oneshot = 1;
	    else
		log_event(event, "requeuing");
	}
	if (oneshot)
	    kcm_remove_event_internal(context, e);
    }

    return ret;
}