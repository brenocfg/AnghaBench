#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_conn_streamgroup_state_t {int next_stream_id; int /*<<< orphan*/  num_streams; } ;
typedef  int /*<<< orphan*/  quicly_maxsender_t ;
struct TYPE_10__ {struct st_quicly_conn_streamgroup_state_t bidi; struct st_quicly_conn_streamgroup_state_t uni; } ;
struct TYPE_9__ {TYPE_4__ peer; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bidi; int /*<<< orphan*/ * uni; } ;
struct TYPE_8__ {TYPE_1__ max_streams; } ;
struct TYPE_11__ {TYPE_3__ super; TYPE_2__ ingress; } ;
typedef  TYPE_5__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_maxsender_should_send_max (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int should_send_max_streams(quicly_conn_t *conn, int uni)
{
    quicly_maxsender_t *maxsender;
    if ((maxsender = uni ? conn->ingress.max_streams.uni : conn->ingress.max_streams.bidi) == NULL)
        return 0;

    struct st_quicly_conn_streamgroup_state_t *group = uni ? &conn->super.peer.uni : &conn->super.peer.bidi;
    if (!quicly_maxsender_should_send_max(maxsender, group->next_stream_id / 4, group->num_streams, 768))
        return 0;

    return 1;
}