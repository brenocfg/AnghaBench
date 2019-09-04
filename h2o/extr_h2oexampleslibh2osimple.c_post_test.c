#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int status; char* reason; int /*<<< orphan*/  headers; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_13__ {int /*<<< orphan*/  entity; TYPE_3__ res; int /*<<< orphan*/  pool; TYPE_2__ path_normalized; TYPE_1__ method; } ;
typedef  TYPE_4__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_14__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_5__ h2o_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_TYPE ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send (TYPE_4__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  h2o_start_response (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static int post_test(h2o_handler_t *self, h2o_req_t *req)
{
    if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("POST")) &&
        h2o_memis(req->path_normalized.base, req->path_normalized.len, H2O_STRLIT("/post-test/"))) {
        static h2o_generator_t generator = {NULL, NULL};
        req->res.status = 200;
        req->res.reason = "OK";
        h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL, H2O_STRLIT("text/plain; charset=utf-8"));
        h2o_start_response(req, &generator);
        h2o_send(req, &req->entity, 1, 1);
        return 0;
    }

    return -1;
}