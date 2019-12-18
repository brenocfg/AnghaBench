#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  _timeout; TYPE_1__* connpool; } ;
struct st_h2o_http1client_t {int /*<<< orphan*/ * _body_buf_in_flight; int /*<<< orphan*/ * _body_buf; TYPE_2__ super; TYPE_4__* sock; scalar_t__ _do_keepalive; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct TYPE_10__ {TYPE_6__* input; } ;
struct TYPE_9__ {scalar_t__ timeout; } ;
struct TYPE_7__ {TYPE_3__* socketpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_6__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_socket_close (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_socketpool_return (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_client(struct st_h2o_http1client_t *client)
{
    if (client->sock != NULL) {
        if (client->super.connpool != NULL && client->_do_keepalive && client->super.connpool->socketpool->timeout > 0) {
            /* we do not send pipelined requests, and thus can trash all the received input at the end of the request */
            h2o_buffer_consume(&client->sock->input, client->sock->input->size);
            h2o_socketpool_return(client->super.connpool->socketpool, client->sock);
        } else {
            h2o_socket_close(client->sock);
        }
    }
    if (h2o_timer_is_linked(&client->super._timeout))
        h2o_timer_unlink(&client->super._timeout);
    if (client->_body_buf != NULL)
        h2o_buffer_dispose(&client->_body_buf);
    if (client->_body_buf_in_flight != NULL)
        h2o_buffer_dispose(&client->_body_buf_in_flight);
    free(client);
}