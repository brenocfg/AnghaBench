#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  request_gathered_write (TYPE_1__*) ; 

void h2o_http2_conn_request_write(h2o_http2_conn_t *conn)
{
    if (conn->state == H2O_HTTP2_CONN_STATE_IS_CLOSING)
        return;
    request_gathered_write(conn);
}