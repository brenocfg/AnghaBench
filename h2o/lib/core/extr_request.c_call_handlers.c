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
struct TYPE_12__ {TYPE_4__* handler; TYPE_2__* pathconf; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_13__ {scalar_t__ (* on_req ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_4__ h2o_handler_t ;
struct TYPE_10__ {int size; TYPE_4__** entries; } ;
struct TYPE_11__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_send_error_404 (TYPE_3__*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void call_handlers(h2o_req_t *req, h2o_handler_t **handler)
{
    h2o_handler_t **end = req->pathconf->handlers.entries + req->pathconf->handlers.size;

    for (; handler != end; ++handler) {
        req->handler = *handler;
        if ((*handler)->on_req(*handler, req) == 0)
            return;
    }

    h2o_send_error_404(req, "File Not Found", "not found", 0);
}