#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_6__* sock; TYPE_4__ super; } ;
struct TYPE_12__ {TYPE_5__* input; } ;
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_9__ {TYPE_2__* globalconf; } ;
struct TYPE_7__ {int /*<<< orphan*/  req_timeout; } ;
struct TYPE_8__ {TYPE_1__ http1; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_incoming_request (struct st_h2o_http1_conn_t*) ; 
 int /*<<< orphan*/  reqread_on_read ; 
 int /*<<< orphan*/  reqread_on_timeout ; 
 int /*<<< orphan*/  set_timeout (struct st_h2o_http1_conn_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reqread_start(struct st_h2o_http1_conn_t *conn)
{
    set_timeout(conn, conn->super.ctx->globalconf->http1.req_timeout, reqread_on_timeout);
    h2o_socket_read_start(conn->sock, reqread_on_read);
    if (conn->sock->input->size != 0)
        handle_incoming_request(conn);
}