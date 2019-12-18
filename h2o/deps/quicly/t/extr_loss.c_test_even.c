#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct loss_cond_t {int /*<<< orphan*/  (* cb ) (struct loss_cond_t*) ;} ;
typedef  void* quicly_loss_conf_t ;
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {void* loss; } ;

/* Variables and functions */
 scalar_t__ QUICLY_DELAYED_ACK_TIMEOUT ; 
 void* QUICLY_LOSS_SPEC_CONF ; 
 scalar_t__ QUICLY_STATE_CONNECTED ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  decode_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 TYPE_4__ fake_address ; 
 int /*<<< orphan*/  free_packets (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  init_cond_even (struct loss_cond_t*) ; 
 int /*<<< orphan*/  new_master_id () ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ quic_ctx ; 
 scalar_t__ quic_now ; 
 int quicly_accept (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quicly_connect (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_connection_is_ready (int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_get_state (int /*<<< orphan*/ ) ; 
 int quicly_send (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  stub1 (struct loss_cond_t*) ; 
 int transmit_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,struct loss_cond_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_even(void)
{
    quicly_loss_conf_t lossconf = QUICLY_LOSS_SPEC_CONF;
    struct loss_cond_t cond_down, cond_up;
    size_t num_sent, num_received;
    int ret;

    quic_ctx.loss = lossconf;
    init_cond_even(&cond_down);
    init_cond_even(&cond_up);

    quic_now = 0;

    { /* transmit first flight */
        quicly_datagram_t *raw;
        size_t num_packets;
        quicly_decoded_packet_t decoded;

        ret = quicly_connect(&client, &quic_ctx, "example.com", &fake_address.sa, NULL, new_master_id(), ptls_iovec_init(NULL, 0),
                             NULL, NULL);
        ok(ret == 0);
        num_packets = 1;
        ret = quicly_send(client, &raw, &num_packets);
        ok(ret == 0);
        ok(num_packets == 1);
        decode_packets(&decoded, &raw, 1);
        ok(num_packets == 1);
        ret = quicly_accept(&server, &quic_ctx, NULL, &fake_address.sa, &decoded, NULL, new_master_id(), NULL);
        ok(ret == 0);
        free_packets(&raw, 1);
        cond_up.cb(&cond_up);
    }

    /* drop 2nd packet from server */
    ret = transmit_cond(server, client, &num_sent, &num_received, &cond_down, 0);
    ok(ret == 0);
    ok(num_sent == 2);
    ok(num_received == 1);
    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(!quicly_connection_is_ready(client));

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;

    /* client sends delayed-ack that gets dropped */
    ret = transmit_cond(client, server, &num_sent, &num_received, &cond_up, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 0);

    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(!quicly_connection_is_ready(client));

    quic_now += 1000;

    /* server resends the contents of all the packets (in cleartext) */
    ret = transmit_cond(server, client, &num_sent, &num_received, &cond_down, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 1);
    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(!quicly_connection_is_ready(client));

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;

    /* client arms the retransmit timer */
    ret = transmit_cond(client, server, &num_sent, &num_received, &cond_up, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 1);

    quic_now += 1000;

    /* server resends the contents of all the packets (in cleartext) */
    ret = transmit_cond(server, client, &num_sent, &num_received, &cond_down, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 0);

    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(!quicly_connection_is_ready(client));

    /* client sends a probe, that gets lost */
    ret = transmit_cond(client, server, &num_sent, &num_received, &cond_up, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 0);

    quic_now += 1000;

    /* server retransmits the handshake packets */
    ret = transmit_cond(server, client, &num_sent, &num_received, &cond_down, 0);
    ok(ret == 0);
    ok(num_sent == 1);
    ok(num_received == 1);

    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(quicly_connection_is_ready(client));

    quic_ctx.loss = (quicly_loss_conf_t)QUICLY_LOSS_SPEC_CONF;
}