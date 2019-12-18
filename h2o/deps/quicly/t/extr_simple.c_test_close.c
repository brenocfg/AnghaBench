#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ quicly_closed_by_peer_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {TYPE_1__* closed_by_peer; } ;

/* Variables and functions */
 int QUICLY_ERROR_FREE_CONNECTION ; 
 int /*<<< orphan*/  QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE (int) ; 
 scalar_t__ QUICLY_STATE_CLOSING ; 
 scalar_t__ QUICLY_STATE_DRAINING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * client ; 
 int /*<<< orphan*/  decode_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 TYPE_3__ fake_address ; 
 int /*<<< orphan*/  ok (int) ; 
 TYPE_2__ quic_ctx ; 
 scalar_t__ quic_now ; 
 int quicly_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  quicly_free (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_get_first_timeout (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_get_state (int /*<<< orphan*/ *) ; 
 int quicly_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_send (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/ * server ; 
 int test_close_error_code ; 
 int /*<<< orphan*/  test_closeed_by_peer ; 

__attribute__((used)) static void test_close(void)
{
    quicly_closed_by_peer_t closed_by_peer = {test_closeed_by_peer}, *orig_closed_by_peer = quic_ctx.closed_by_peer;
    quicly_datagram_t *datagram;
    size_t num_datagrams;
    int64_t client_timeout, server_timeout;
    int ret;

    quic_ctx.closed_by_peer = &closed_by_peer;

    /* client sends close */
    ret = quicly_close(client, QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(12345), "good bye");
    ok(ret == 0);
    ok(quicly_get_state(client) == QUICLY_STATE_CLOSING);
    ok(quicly_get_first_timeout(client) <= quic_now);
    num_datagrams = 1;
    ret = quicly_send(client, &datagram, &num_datagrams);
    assert(num_datagrams == 1);
    client_timeout = quicly_get_first_timeout(client);
    ok(quic_now < client_timeout && client_timeout < quic_now + 1000); /* 3 pto or something */

    { /* server receives close */
        quicly_decoded_packet_t decoded;
        decode_packets(&decoded, &datagram, 1);
        ret = quicly_receive(server, NULL, &fake_address.sa, &decoded);
        ok(ret == 0);
        ok(test_close_error_code == 12345);
        ok(quicly_get_state(server) == QUICLY_STATE_DRAINING);
        server_timeout = quicly_get_first_timeout(server);
        ok(quic_now < server_timeout && server_timeout < quic_now + 1000); /* 3 pto or something */
    }

    /* nothing sent by the server in response */
    num_datagrams = 1;
    ret = quicly_send(server, &datagram, &num_datagrams);
    ok(ret == 0);
    ok(num_datagrams == 0);

    /* endpoints request discarding state after timeout */
    quic_now = client_timeout < server_timeout ? server_timeout : client_timeout;
    num_datagrams = 1;
    ret = quicly_send(client, &datagram, &num_datagrams);
    ok(ret == QUICLY_ERROR_FREE_CONNECTION);
    quicly_free(client);
    num_datagrams = 1;
    ret = quicly_send(server, &datagram, &num_datagrams);
    ok(ret == QUICLY_ERROR_FREE_CONNECTION);
    quicly_free(server);

    client = NULL;
    server = NULL;
    quic_ctx.closed_by_peer = orig_closed_by_peer;
}