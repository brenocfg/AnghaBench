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
struct TYPE_3__ {scalar_t__ num_packets; scalar_t__ max_packets; } ;
typedef  TYPE_1__ quicly_send_context_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */

int quicly_can_send_stream_data(quicly_conn_t *conn, quicly_send_context_t *s)
{
    return s->num_packets < s->max_packets;
}