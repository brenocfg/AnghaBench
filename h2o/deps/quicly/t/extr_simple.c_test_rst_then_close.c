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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {scalar_t__ reset_stream; scalar_t__ stop_sending; } ;
struct TYPE_9__ {int is_detached; TYPE_1__ error_received; } ;
typedef  TYPE_2__ test_streambuf_t ;
struct TYPE_10__ {int /*<<< orphan*/  recvstate; int /*<<< orphan*/  sendstate; TYPE_2__* data; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_3__ quicly_stream_t ;

/* Variables and functions */
 scalar_t__ QUICLY_DELAYED_ACK_TIMEOUT ; 
 scalar_t__ QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE (int) ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  quic_now ; 
 TYPE_3__* quicly_get_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quicly_num_streams (int /*<<< orphan*/ ) ; 
 int quicly_open_stream (int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_3__*,scalar_t__) ; 
 int quicly_sendstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_rst_then_close(void)
{
    quicly_stream_t *client_stream, *server_stream;
    test_streambuf_t *client_streambuf, *server_streambuf;
    uint64_t stream_id;
    int ret;

    /* client sends STOP_SENDING and RST_STREAM */
    ret = quicly_open_stream(client, &client_stream, 0);
    ok(ret == 0);
    stream_id = client_stream->stream_id;
    client_streambuf = client_stream->data;
    quicly_reset_stream(client_stream, QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(12345));
    quicly_request_stop(client_stream, QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(54321));

    transmit(client, server);

    /* server sends RST_STREAM and ACKs to the packets received */
    ok(quicly_num_streams(server) == 1);
    server_stream = quicly_get_stream(server, stream_id);
    ok(server_stream != NULL);
    server_streambuf = server_stream->data;
    ok(quicly_sendstate_transfer_complete(&server_stream->sendstate));
    ok(quicly_recvstate_transfer_complete(&server_stream->recvstate));
    ok(server_streambuf->error_received.reset_stream == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(12345));
    ok(server_streambuf->error_received.stop_sending == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(54321));

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;
    transmit(server, client);

    /* client closes the stream */
    ok(client_streambuf->is_detached);
    ok(client_streambuf->error_received.stop_sending == -1);
    ok(client_streambuf->error_received.reset_stream == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(54321));
    ok(quicly_num_streams(client) == 0);

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;
    transmit(client, server);

    ok(server_streambuf->is_detached);
    ok(quicly_num_streams(server) == 0);
}