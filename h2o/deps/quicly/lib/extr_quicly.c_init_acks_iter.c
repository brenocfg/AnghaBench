#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_sentmap_iter_t ;
struct TYPE_9__ {scalar_t__ sent_at; scalar_t__ bytes_in_flight; } ;
typedef  TYPE_2__ quicly_sent_packet_t ;
struct TYPE_8__ {int /*<<< orphan*/  sentmap; } ;
struct TYPE_10__ {TYPE_1__ egress; } ;
typedef  TYPE_3__ quicly_conn_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_SENTMAP_EVENT_EXPIRED ; 
 scalar_t__ get_sentmap_expiration_time (TYPE_3__*) ; 
 scalar_t__ now ; 
 TYPE_2__* quicly_sentmap_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_init_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void init_acks_iter(quicly_conn_t *conn, quicly_sentmap_iter_t *iter)
{
    /* TODO find a better threshold */
    int64_t retire_before = now - get_sentmap_expiration_time(conn);
    const quicly_sent_packet_t *sent;

    quicly_sentmap_init_iter(&conn->egress.sentmap, iter);

    while ((sent = quicly_sentmap_get(iter))->sent_at <= retire_before && sent->bytes_in_flight == 0)
        quicly_sentmap_update(&conn->egress.sentmap, iter, QUICLY_SENTMAP_EVENT_EXPIRED, conn);
}