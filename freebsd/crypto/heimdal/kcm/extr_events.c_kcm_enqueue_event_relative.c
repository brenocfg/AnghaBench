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
struct TYPE_4__ {int /*<<< orphan*/  fire_time; int /*<<< orphan*/  backoff_time; } ;
typedef  TYPE_1__ kcm_event ;

/* Variables and functions */
 int /*<<< orphan*/  kcm_enqueue_event (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

krb5_error_code
kcm_enqueue_event_relative(krb5_context context,
			   kcm_event *event)
{
    krb5_error_code ret;
    kcm_event e;

    e = *event;
    e.backoff_time = e.fire_time;
    e.fire_time += time(NULL);

    ret = kcm_enqueue_event(context, &e);

    return ret;
}