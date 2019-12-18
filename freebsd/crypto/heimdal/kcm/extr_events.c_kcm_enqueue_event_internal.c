#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {scalar_t__ action; int valid; struct TYPE_5__* next; int /*<<< orphan*/  ccache; int /*<<< orphan*/  backoff_time; int /*<<< orphan*/  expire_time; scalar_t__ fire_count; int /*<<< orphan*/  fire_time; } ;
typedef  TYPE_1__ kcm_event ;

/* Variables and functions */
 scalar_t__ KCM_EVENT_NONE ; 
 int /*<<< orphan*/  KRB5_CC_NOMEM ; 
 TYPE_1__* events_head ; 
 int /*<<< orphan*/  kcm_retain_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_event (TYPE_1__*,char*) ; 
 scalar_t__ malloc (int) ; 

krb5_error_code
kcm_enqueue_event_internal(krb5_context context,
			   kcm_event *event)
{
    kcm_event **e;

    if (event->action == KCM_EVENT_NONE)
	return 0;

    for (e = &events_head; *e != NULL; e = &(*e)->next)
	;

    *e = (kcm_event *)malloc(sizeof(kcm_event));
    if (*e == NULL) {
	return KRB5_CC_NOMEM;
    }

    (*e)->valid = 1;
    (*e)->fire_time = event->fire_time;
    (*e)->fire_count = 0;
    (*e)->expire_time = event->expire_time;
    (*e)->backoff_time = event->backoff_time;

    (*e)->action = event->action;

    kcm_retain_ccache(context, event->ccache);
    (*e)->ccache = event->ccache;
    (*e)->next = NULL;

    log_event(*e, "enqueuing");

    return 0;
}