#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int /*<<< orphan*/  msg_name; TYPE_1__* msg_iov; } ;
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  next_cid ; 
 int /*<<< orphan*/  quicly_accept (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t quicly_decode_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 scalar_t__ quicly_is_destination (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_msg(int is_client, quicly_conn_t **conns, struct msghdr *msg, size_t dgram_len)
{
    size_t off, packet_len, i;

    /* split UDP datagram into multiple QUIC packets */
    for (off = 0; off < dgram_len; off += packet_len) {
        quicly_decoded_packet_t decoded;
        if ((packet_len = quicly_decode_packet(&ctx, &decoded, msg->msg_iov[0].iov_base + off, dgram_len - off)) == SIZE_MAX)
            return;
        /* find the corresponding connection (TODO handle version negotiation, rebinding, retry, etc.) */
        for (i = 0; conns[i] != NULL; ++i)
            if (quicly_is_destination(conns[i], NULL, msg->msg_name, &decoded))
                break;
        if (conns[i] != NULL) {
            /* let the current connection handle ingress packets */
            quicly_receive(conns[i], NULL, msg->msg_name, &decoded);
        } else if (!is_client) {
            /* assume that the packet is a new connection */
            quicly_accept(conns + i, &ctx, NULL, msg->msg_name, &decoded, NULL, &next_cid, NULL);
        }
    }
}