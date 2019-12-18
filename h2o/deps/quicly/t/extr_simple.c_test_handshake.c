#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
struct TYPE_7__ {int len; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
typedef  TYPE_2__ quicly_datagram_t ;
typedef  int /*<<< orphan*/  packets ;
struct TYPE_9__ {int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 scalar_t__ QUICLY_STATE_CONNECTED ; 
 int /*<<< orphan*/  client ; 
 size_t decode_packets (int /*<<< orphan*/ *,TYPE_2__**,size_t) ; 
 TYPE_5__ fake_address ; 
 int /*<<< orphan*/  free_packets (TYPE_2__**,size_t) ; 
 int /*<<< orphan*/  new_master_id () ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quic_ctx ; 
 int quicly_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quicly_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_connection_is_ready (int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_get_state (int /*<<< orphan*/ ) ; 
 int quicly_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ ,TYPE_2__**,size_t*) ; 
 int /*<<< orphan*/  server ; 

__attribute__((used)) static void test_handshake(void)
{
    quicly_datagram_t *packets[32];
    size_t num_packets, num_decoded;
    quicly_decoded_packet_t decoded[32];
    int ret, i;

    /* send CH */
    ret = quicly_connect(&client, &quic_ctx, "example.com", &fake_address.sa, NULL, new_master_id(), ptls_iovec_init(NULL, 0), NULL,
                         NULL);
    ok(ret == 0);
    num_packets = sizeof(packets) / sizeof(packets[0]);
    ret = quicly_send(client, packets, &num_packets);
    ok(ret == 0);
    ok(num_packets == 1);
    ok(packets[0]->data.len == 1280);

    /* receive CH, send handshake upto ServerFinished */
    num_decoded = decode_packets(decoded, packets, num_packets);
    ok(num_decoded == 1);
    ret = quicly_accept(&server, &quic_ctx, NULL, &fake_address.sa, decoded, NULL, new_master_id(), NULL);
    ok(ret == 0);
    free_packets(packets, num_packets);
    ok(quicly_get_state(server) == QUICLY_STATE_CONNECTED);
    ok(quicly_connection_is_ready(server));
    num_packets = sizeof(packets) / sizeof(packets[0]);
    ret = quicly_send(server, packets, &num_packets);
    ok(ret == 0);
    ok(num_packets != 0);

    /* receive ServerFinished */
    num_decoded = decode_packets(decoded, packets, num_packets);
    for (i = 0; i != num_decoded; ++i) {
        ret = quicly_receive(client, NULL, &fake_address.sa, decoded + i);
        ok(ret == 0);
    }
    free_packets(packets, num_packets);
    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(quicly_connection_is_ready(client));
}