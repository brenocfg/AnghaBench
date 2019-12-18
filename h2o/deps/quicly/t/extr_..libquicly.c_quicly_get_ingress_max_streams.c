#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
struct TYPE_8__ {int /*<<< orphan*/  max_committed; } ;
typedef  TYPE_3__ quicly_maxsender_t ;
struct TYPE_6__ {TYPE_3__* bidi; TYPE_3__* uni; } ;
struct TYPE_7__ {TYPE_1__ max_streams; } ;
struct TYPE_9__ {TYPE_2__ ingress; } ;
typedef  TYPE_4__ quicly_conn_t ;

/* Variables and functions */

quicly_stream_id_t quicly_get_ingress_max_streams(quicly_conn_t *conn, int uni)
{
    quicly_maxsender_t *maxsender = uni ? conn->ingress.max_streams.uni : conn->ingress.max_streams.bidi;
    return maxsender->max_committed;
}