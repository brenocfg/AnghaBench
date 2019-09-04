#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  cb; } ;
struct TYPE_9__ {int /*<<< orphan*/  request_end_at; } ;
struct TYPE_11__ {TYPE_6__ _timeout; TYPE_2__* ctx; TYPE_1__ timings; } ;
struct st_h2o_http1client_t {TYPE_3__ super; int /*<<< orphan*/  sock; scalar_t__ _is_chunked; } ;
struct TYPE_12__ {struct st_h2o_http1client_t* data; } ;
typedef  TYPE_4__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_10__ {int /*<<< orphan*/  first_byte_timeout; int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void (*) (TYPE_4__*,char const*)) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_6__*) ; 
 int /*<<< orphan*/  on_error_before_head (struct st_h2o_http1client_t*,char*) ; 
 int /*<<< orphan*/  on_head ; 
 int /*<<< orphan*/  on_head_timeout ; 

__attribute__((used)) static void on_send_request(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1client_t *client = sock->data;

    h2o_timer_unlink(&client->super._timeout);

    if (err != NULL) {
        on_error_before_head(client, "I/O error (send request)");
        return;
    }

    if (client->_is_chunked) {
        client->_is_chunked = 0;
        h2o_iovec_t last = h2o_iovec_init(H2O_STRLIT("0\r\n"));
        h2o_socket_write(client->sock, &last, 1, on_send_request);
        return;
    }

    client->super.timings.request_end_at = h2o_gettimeofday(client->super.ctx->loop);

    h2o_socket_read_start(client->sock, on_head);
    client->super._timeout.cb = on_head_timeout;
    h2o_timer_link(client->super.ctx->loop, client->super.ctx->first_byte_timeout, &client->super._timeout);
}