#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ kcm_event ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5_CC_NOTFOUND ; 
 TYPE_1__* events_head ; 
 int /*<<< orphan*/  events_mutex ; 
 int /*<<< orphan*/  kcm_remove_event_internal (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  log_event (TYPE_1__*,char*) ; 

krb5_error_code
kcm_remove_event(krb5_context context,
		 kcm_event *event)
{
    krb5_error_code ret;
    kcm_event **e;
    int found = 0;

    log_event(event, "removing");

    HEIMDAL_MUTEX_lock(&events_mutex);
    for (e = &events_head; *e != NULL; e = &(*e)->next) {
	if (event == *e) {
	    *e = event->next;
	    found++;
	    break;
	}
    }

    if (!found) {
	ret = KRB5_CC_NOTFOUND;
	goto out;
    }

    ret = kcm_remove_event_internal(context, &event);

out:
    HEIMDAL_MUTEX_unlock(&events_mutex);

    return ret;
}