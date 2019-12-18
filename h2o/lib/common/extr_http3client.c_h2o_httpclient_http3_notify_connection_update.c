#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cb; } ;
struct st_h2o_http3client_conn_t {TYPE_1__ timeout; } ;
typedef  int /*<<< orphan*/  h2o_http3_ctx_t ;
typedef  int /*<<< orphan*/  h2o_http3_conn_t ;

/* Variables and functions */
 scalar_t__ h2o_timer_is_linked (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_1__*) ; 
 scalar_t__ on_connect_timeout ; 

void h2o_httpclient_http3_notify_connection_update(h2o_http3_ctx_t *ctx, h2o_http3_conn_t *_conn)
{
    struct st_h2o_http3client_conn_t *conn = (void *)_conn;

    if (h2o_timer_is_linked(&conn->timeout) && conn->timeout.cb == on_connect_timeout)
        h2o_timer_unlink(&conn->timeout);
}