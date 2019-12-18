#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  quic; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ h2o_http3_conn_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy_connection ) (TYPE_2__*) ;} ;

/* Variables and functions */
#define  QUICLY_STATE_CONNECTED 129 
#define  QUICLY_STATE_FIRSTFLIGHT 128 
 int /*<<< orphan*/  h2o_http3_schedule_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  quicly_close (int /*<<< orphan*/ ,int,char const*) ; 
 int quicly_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void h2o_http3_close_connection(h2o_http3_conn_t *conn, int err, const char *reason_phrase)
{
    switch (quicly_get_state(conn->quic)) {
    case QUICLY_STATE_FIRSTFLIGHT:
        conn->callbacks->destroy_connection(conn);
        break;
    case QUICLY_STATE_CONNECTED:
        quicly_close(conn->quic, err, reason_phrase);
        h2o_http3_schedule_timer(conn);
        break;
    default:
        /* only need to wait for the socket close */
        break;
    }
}