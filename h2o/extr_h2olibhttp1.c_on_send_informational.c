#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  send_state; int /*<<< orphan*/  inbufcnt; int /*<<< orphan*/ * inbufs; } ;
struct TYPE_8__ {TYPE_1__ pending_final; scalar_t__ sending; } ;
struct st_h2o_http1_finalostream_t {TYPE_2__ informational; int /*<<< orphan*/  super; } ;
struct TYPE_10__ {scalar_t__ _ostr_top; } ;
struct st_h2o_http1_conn_t {TYPE_5__ req; } ;
struct TYPE_9__ {struct st_h2o_http1_conn_t* data; } ;
typedef  TYPE_3__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection (struct st_h2o_http1_conn_t*,int) ; 
 int /*<<< orphan*/  do_send_informational (struct st_h2o_http1_finalostream_t*,TYPE_3__*) ; 
 int /*<<< orphan*/  finalostream_send (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_send_informational(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1_conn_t *conn = sock->data;
    struct st_h2o_http1_finalostream_t *self = (struct st_h2o_http1_finalostream_t *)conn->req._ostr_top;
    if (err != NULL) {
        close_connection(conn, 1);
        return;
    }

    self->informational.sending = 0;

    if (self->informational.pending_final.inbufs != NULL) {
        finalostream_send(&self->super, &conn->req, self->informational.pending_final.inbufs,
                          self->informational.pending_final.inbufcnt, self->informational.pending_final.send_state);
        return;
    }

    do_send_informational(self, sock);
}