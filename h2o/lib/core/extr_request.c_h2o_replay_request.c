#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* conn; int /*<<< orphan*/ * handler; TYPE_3__* pathconf; } ;
typedef  TYPE_4__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_11__ {int size; int /*<<< orphan*/ ** entries; } ;
struct TYPE_12__ {TYPE_2__ handlers; } ;
struct TYPE_10__ {int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  call_handlers (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  close_generator_and_filters (TYPE_4__*) ; 
 int /*<<< orphan*/  process_resolved_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_response (TYPE_4__*) ; 

void h2o_replay_request(h2o_req_t *req)
{
    close_generator_and_filters(req);
    reset_response(req);

    if (req->handler != NULL) {
        h2o_handler_t **handler = req->pathconf->handlers.entries, **end = handler + req->pathconf->handlers.size;
        for (;; ++handler) {
            assert(handler != end);
            if (*handler == req->handler)
                break;
        }
        call_handlers(req, handler);
    } else {
        process_resolved_request(req, req->conn->hosts);
    }
}