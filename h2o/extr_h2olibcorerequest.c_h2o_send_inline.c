#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {TYPE_2__ method; } ;
struct TYPE_11__ {TYPE_1__ input; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_12__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ h2o_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_start_response (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,char const*,size_t) ; 

void h2o_send_inline(h2o_req_t *req, const char *body, size_t len)
{
    static h2o_generator_t generator = {NULL, NULL};

    h2o_iovec_t buf = h2o_strdup(&req->pool, body, len);
    /* the function intentionally does not set the content length, since it may be used for generating 304 response, etc. */
    /* req->res.content_length = buf.len; */

    h2o_start_response(req, &generator);

    if (h2o_memis(req->input.method.base, req->input.method.len, H2O_STRLIT("HEAD")))
        h2o_send(req, NULL, 0, H2O_SEND_STATE_FINAL);
    else
        h2o_send(req, &buf, 1, H2O_SEND_STATE_FINAL);
}