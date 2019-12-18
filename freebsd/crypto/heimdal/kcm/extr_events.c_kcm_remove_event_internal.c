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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  ccache; scalar_t__ backoff_time; scalar_t__ expire_time; scalar_t__ fire_count; scalar_t__ fire_time; scalar_t__ valid; } ;
typedef  TYPE_1__ kcm_event ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
kcm_remove_event_internal(krb5_context context,
			  kcm_event **e)
{
    kcm_event *next;

    next = (*e)->next;

    (*e)->valid = 0;
    (*e)->fire_time = 0;
    (*e)->fire_count = 0;
    (*e)->expire_time = 0;
    (*e)->backoff_time = 0;
    kcm_release_ccache(context, (*e)->ccache);
    (*e)->next = NULL;
    free(*e);

    *e = next;

    return 0;
}