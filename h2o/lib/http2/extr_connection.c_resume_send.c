#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_8__ {TYPE_1__ list; } ;
struct TYPE_9__ {TYPE_2__ scheduler; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ h2o_http2_conn_get_buffer_window (TYPE_3__*) ; 
 int /*<<< orphan*/  request_gathered_write (TYPE_3__*) ; 

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