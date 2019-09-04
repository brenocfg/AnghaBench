#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rp_generator_t {TYPE_2__* src_req; } ;
struct TYPE_4__ {struct rp_generator_t* data; } ;
typedef  TYPE_1__ h2o_httpclient_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* proceed_req ) (TYPE_2__*,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int) ; 

__attribute__((used)) static void proceed_request(h2o_httpclient_t *client, size_t written, int is_end_stream)
{
    struct rp_generator_t *self = client->data;
    if (self->src_req->proceed_req != NULL)
        self->src_req->proceed_req(self->src_req, written, is_end_stream);
}