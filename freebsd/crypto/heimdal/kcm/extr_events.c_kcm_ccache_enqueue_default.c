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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  ccache; } ;
typedef  TYPE_1__ kcm_event ;
typedef  int /*<<< orphan*/  kcm_ccache ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 scalar_t__ kcm_ccache_make_default_event (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kcm_enqueue_event_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

krb5_error_code
kcm_ccache_enqueue_default(krb5_context context,
			   kcm_ccache ccache,
			   krb5_creds *newcred)
{
    kcm_event event;
    krb5_error_code ret;

    memset(&event, 0, sizeof(event));
    event.ccache = ccache;

    ret = kcm_ccache_make_default_event(context, &event, newcred);
    if (ret)
	return ret;

    ret = kcm_enqueue_event_internal(context, &event);
    if (ret)
	return ret;

    return 0;
}