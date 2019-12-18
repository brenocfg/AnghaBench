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
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  respool; int /*<<< orphan*/  handler_baton; int /*<<< orphan*/  (* handler ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ serf_request_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_request (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t cancel_request(serf_request_t *request,
                                   serf_request_t **list,
                                   int notify_request)
{
    /* If we haven't run setup, then we won't have a handler to call. */
    if (request->handler && notify_request) {
        /* We actually don't care what the handler returns.
         * We have bigger matters at hand.
         */
        (*request->handler)(request, NULL, request->handler_baton,
                            request->respool);
    }

    if (*list == request) {
        *list = request->next;
    }
    else {
        serf_request_t *scan = *list;

        while (scan->next && scan->next != request)
            scan = scan->next;

        if (scan->next) {
            scan->next = scan->next->next;
        }
    }

    return destroy_request(request);
}