#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int (* cb ) (int /*<<< orphan*/ ,TYPE_4__,int) ;int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* on_streaming_selected ) (TYPE_3__*,int) ;} ;
struct TYPE_14__ {TYPE_12__* body; } ;
struct TYPE_16__ {TYPE_2__ write_req; TYPE_1__ _req_body; int /*<<< orphan*/  entity; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_17__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_18__ {scalar_t__ supports_request_streaming; } ;
typedef  TYPE_5__ h2o_handler_t ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 scalar_t__ h2o_buffer_append (TYPE_12__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_get_first_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int) ; 
 int stub3 (int /*<<< orphan*/ ,TYPE_4__,int) ; 

int h2o_write_req_first(void *_req, h2o_iovec_t payload, int is_end_entity)
{
    h2o_req_t *req = _req;
    h2o_handler_t *first_handler;

    /* if possible, switch to either streaming request body mode */
    if (!is_end_entity && (first_handler = h2o_get_first_handler(req)) != NULL &&
        first_handler->supports_request_streaming) {
        if (h2o_buffer_append(&req->_req_body.body, payload.base, payload.len) == 0)
            return -1;
        req->entity = h2o_iovec_init(req->_req_body.body->bytes, req->_req_body.body->size);
        req->write_req.on_streaming_selected(req, 1);
        return 0;
    }

    req->write_req.on_streaming_selected(req, 0);
    return req->write_req.cb(req->write_req.ctx, payload, is_end_entity);
}