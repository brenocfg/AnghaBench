#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_deferred_request_action_t {int /*<<< orphan*/  timeout; TYPE_3__* req; } ;
typedef  int /*<<< orphan*/  h2o_timer_cb ;
struct TYPE_7__ {TYPE_2__* conn; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 struct st_deferred_request_action_t* h2o_mem_alloc_shared (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_deferred_action_dispose ; 

__attribute__((used)) static struct st_deferred_request_action_t *create_deferred_action(h2o_req_t *req, size_t sz, h2o_timer_cb cb)
{
    struct st_deferred_request_action_t *action = h2o_mem_alloc_shared(&req->pool, sz, on_deferred_action_dispose);
    action->req = req;
    h2o_timer_init(&action->timeout, cb);
    h2o_timer_link(req->conn->ctx->loop, 0, &action->timeout);
    return action;
}