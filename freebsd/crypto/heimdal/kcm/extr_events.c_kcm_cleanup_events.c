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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {scalar_t__ ccache; scalar_t__ valid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ kcm_event ;
typedef  scalar_t__ kcm_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (scalar_t__) ; 
 TYPE_1__* events_head ; 
 int /*<<< orphan*/  events_mutex ; 
 int /*<<< orphan*/  kcm_remove_event_internal (int /*<<< orphan*/ ,TYPE_1__**) ; 

krb5_error_code
kcm_cleanup_events(krb5_context context,
		   kcm_ccache ccache)
{
    kcm_event **e;

    KCM_ASSERT_VALID(ccache);

    HEIMDAL_MUTEX_lock(&events_mutex);

    for (e = &events_head; *e != NULL; e = &(*e)->next) {
	if ((*e)->valid && (*e)->ccache == ccache) {
	    kcm_remove_event_internal(context, e);
	}
	if (*e == NULL)
	    break;
    }

    HEIMDAL_MUTEX_unlock(&events_mutex);

    return 0;
}