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
struct TYPE_6__ {int /*<<< orphan*/ * proceed_req; scalar_t__ http1_is_persistent; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct st_h2o_http1_conn_t {TYPE_2__ req; TYPE_1__ _ostr_final; } ;
struct TYPE_7__ {struct st_h2o_http1_conn_t* data; } ;
typedef  TYPE_3__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSTREAM_STATE_DONE ; 
 int /*<<< orphan*/  cleanup_connection (struct st_h2o_http1_conn_t*) ; 

__attribute__((used)) static void on_send_complete_post_trailers(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1_conn_t *conn = sock->data;

    if (err != NULL)
        conn->req.http1_is_persistent = 0;

    conn->_ostr_final.state = OSTREAM_STATE_DONE;
    if (conn->req.proceed_req == NULL)
        cleanup_connection(conn);
}