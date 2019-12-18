#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  packets ;
struct TYPE_12__ {TYPE_2__* callbacks; TYPE_7__* ctx; int /*<<< orphan*/  quic; } ;
typedef  TYPE_3__ h2o_http3_conn_t ;
struct TYPE_14__ {TYPE_1__* quic; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* free_packet ) (TYPE_5__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* destroy_connection ) (TYPE_3__*) ;} ;
struct TYPE_10__ {TYPE_5__* packet_allocator; } ;

/* Variables and functions */
#define  QUICLY_ERROR_FREE_CONNECTION 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  h2o_http3_schedule_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_http3_send_datagram (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 

int h2o_http3_send(h2o_http3_conn_t *conn)
{
    quicly_datagram_t *packets[16];
    size_t num_packets, i;

    do {
        num_packets = sizeof(packets) / sizeof(packets[0]);
        int ret = quicly_send(conn->quic, packets, &num_packets);
        switch (ret) {
        case 0:
            for (i = 0; i != num_packets; ++i) {
                if (!h2o_http3_send_datagram(conn->ctx, packets[i])) {
                    /* FIXME close the connection immediately */
                    break;
                }
                conn->ctx->quic->packet_allocator->free_packet(conn->ctx->quic->packet_allocator, packets[i]);
            }
            for (; i != num_packets; ++i)
                conn->ctx->quic->packet_allocator->free_packet(conn->ctx->quic->packet_allocator, packets[i]);
            break;
        case QUICLY_ERROR_FREE_CONNECTION:
            conn->callbacks->destroy_connection(conn);
            return 0;
        default:
            fprintf(stderr, "quicly_send returned %d\n", ret);
            abort();
        }
    } while (num_packets == sizeof(packets) / sizeof(packets[0]));

    h2o_http3_schedule_timer(conn);

    return 1;
}