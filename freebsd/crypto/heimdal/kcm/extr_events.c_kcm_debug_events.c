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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ kcm_event ;

/* Variables and functions */
 TYPE_1__* events_head ; 
 int /*<<< orphan*/  log_event (TYPE_1__*,char*) ; 

krb5_error_code
kcm_debug_events(krb5_context context)
{
    kcm_event *e;

    for (e = events_head; e != NULL; e = e->next)
	log_event(e, "debug");

    return 0;
}