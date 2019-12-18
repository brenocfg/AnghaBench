#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * handler; TYPE_2__* pathconf; } ;
typedef  TYPE_3__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_6__ {int size; int /*<<< orphan*/ ** entries; } ;
struct TYPE_7__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  call_handlers (TYPE_3__*,int /*<<< orphan*/ **) ; 

void h2o_delegate_request(h2o_req_t *req)
{
    h2o_handler_t **handler = req->pathconf->handlers.entries, **end = handler + req->pathconf->handlers.size;
    for (;; ++handler) {
        assert(handler != end);
        if (*handler == req->handler)
            break;
    }
    ++handler;
    call_handlers(req, handler);
}