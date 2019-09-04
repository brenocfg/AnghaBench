#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http1client_t {int /*<<< orphan*/  sock; scalar_t__ _body_buf_is_done; int /*<<< orphan*/  super; TYPE_1__* _body_buf; TYPE_4__* _body_buf_in_flight; int /*<<< orphan*/  (* proceed_req ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_6__ {struct st_h2o_http1client_t* data; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_write_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_send_request (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void on_req_body_done(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1client_t *client = sock->data;

    if (client->_body_buf_in_flight != NULL) {
        client->proceed_req(&client->super, client->_body_buf_in_flight->size, client->_body_buf_is_done);
        h2o_buffer_consume(&client->_body_buf_in_flight, client->_body_buf_in_flight->size);
    }

    if (err) {
        on_send_request(client->sock, err);
        return;
    }

    if (client->_body_buf != NULL && client->_body_buf->size != 0)
        do_write_req(&client->super, h2o_iovec_init(NULL, 0), client->_body_buf_is_done);
    else if (client->_body_buf_is_done)
        on_send_request(client->sock, NULL);
}