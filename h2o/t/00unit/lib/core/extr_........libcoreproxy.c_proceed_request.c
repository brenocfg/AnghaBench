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
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_4__ {struct rp_generator_t* data; } ;
typedef  TYPE_1__ h2o_httpclient_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* proceed_req ) (TYPE_2__*,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  detach_client (struct rp_generator_t*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proceed_request(h2o_httpclient_t *client, size_t written, h2o_send_state_t send_state)
{
    struct rp_generator_t *self = client->data;
    if (self == NULL) {
        return;
    }
    if (send_state == H2O_SEND_STATE_ERROR) {
        detach_client(self);
    }
    if (self->src_req->proceed_req != NULL)
        self->src_req->proceed_req(self->src_req, written, send_state);
}