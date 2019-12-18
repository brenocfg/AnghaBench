#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_conn_streamgroup_state_t {int dummy; } ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
struct TYPE_8__ {struct st_quicly_conn_streamgroup_state_t bidi; struct st_quicly_conn_streamgroup_state_t uni; } ;
struct TYPE_7__ {struct st_quicly_conn_streamgroup_state_t bidi; struct st_quicly_conn_streamgroup_state_t uni; } ;
struct TYPE_9__ {TYPE_2__ peer; TYPE_1__ host; } ;
struct TYPE_10__ {TYPE_3__ super; } ;
typedef  TYPE_4__ quicly_conn_t ;

/* Variables and functions */
 scalar_t__ quicly_is_client (TYPE_4__*) ; 
 scalar_t__ quicly_stream_is_client_initiated (int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_stream_is_unidirectional (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct st_quicly_conn_streamgroup_state_t *get_streamgroup_state(quicly_conn_t *conn, quicly_stream_id_t stream_id)
{
    if (quicly_is_client(conn) == quicly_stream_is_client_initiated(stream_id)) {
        return quicly_stream_is_unidirectional(stream_id) ? &conn->super.host.uni : &conn->super.host.bidi;
    } else {
        return quicly_stream_is_unidirectional(stream_id) ? &conn->super.peer.uni : &conn->super.peer.bidi;
    }
}