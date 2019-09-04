#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ h2o_http2_conn_get_buffer_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_gathered_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resume_send(h2o_http2_conn_t *conn)
{
    if (h2o_http2_conn_get_buffer_window(conn) <= 0)
        return;
#if 0 /* TODO reenable this check for performance? */
    if (conn->scheduler.list.size == 0)
        return;
#endif
    request_gathered_write(conn);
}