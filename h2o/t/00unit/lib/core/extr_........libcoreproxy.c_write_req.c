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
struct rp_generator_t {int req_done; scalar_t__ res_done; TYPE_2__* src_req; TYPE_3__* client; } ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_7__ {int (* write_req ) (TYPE_3__*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_3__ h2o_httpclient_t ;
struct TYPE_5__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_6__ {TYPE_1__ write_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_client (struct rp_generator_t*) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_req(void *ctx, h2o_iovec_t chunk, int is_end_stream)
{
    struct rp_generator_t *self = ctx;
    h2o_httpclient_t *client = self->client;

    if (client == NULL) {
        return -1;
    }

    if (is_end_stream) {
        self->src_req->write_req.cb = NULL;
        self->req_done = 1;
        if (self->res_done)
            detach_client(self);
    }

    return client->write_req(client, chunk, is_end_stream);
}