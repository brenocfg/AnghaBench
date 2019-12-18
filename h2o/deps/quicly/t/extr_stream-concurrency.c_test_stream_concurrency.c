#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ reset_stream; scalar_t__ stop_sending; } ;
struct TYPE_18__ {int is_detached; TYPE_2__ error_received; } ;
typedef  TYPE_3__ test_streambuf_t ;
struct TYPE_19__ {int streams_blocked; TYPE_3__* data; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_4__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_16__ {size_t max_streams_bidi; } ;
struct TYPE_15__ {int /*<<< orphan*/  sa; } ;
struct TYPE_14__ {TYPE_1__ transport_params; } ;

/* Variables and functions */
 scalar_t__ QUICLY_DELAYED_ACK_TIMEOUT ; 
 scalar_t__ QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int decode_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 TYPE_13__ fake_address ; 
 int /*<<< orphan*/  free_packets (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  new_master_id () ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_10__ quic_ctx ; 
 int /*<<< orphan*/  quic_now ; 
 int quicly_accept (int /*<<< orphan*/ **,TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quicly_connect (int /*<<< orphan*/ **,TYPE_10__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int quicly_open_stream (int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_4__*,scalar_t__) ; 
 int quicly_send (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int quicly_streambuf_egress_write (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  transmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_stream_concurrency(void)
{
    quicly_conn_t *client, *server;
    size_t limit = quic_ctx.transport_params.max_streams_bidi;
    quicly_stream_t *client_streams[limit + 2], *server_stream;
    test_streambuf_t *client_streambufs[limit + 1], *server_streambuf;
    size_t i;
    int ret;

    { /* connect */
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
        ok(decode_packets(&decoded, &raw, 1) == 1);
        ok(num_packets == 1);
        ret = quicly_accept(&server, &quic_ctx, NULL, &fake_address.sa, &decoded, NULL, new_master_id(), NULL);
        ok(ret == 0);
        free_packets(&raw, 1);
        transmit(server, client);
    }

    /* open as many streams as we can */
    for (i = 0; i < limit + 1; ++i) {
        ret = quicly_open_stream(client, client_streams + i, 0);
        assert(ret == 0);
        client_streambufs[i] = client_streams[i]->data;
        if (client_streams[i]->streams_blocked)
            break;
        ret = quicly_streambuf_egress_write(client_streams[i], "hello", 5);
        assert(ret == 0);
    }
    ok(i == limit);

    transmit(client, server);
    transmit(server, client);

    /* the last stream is still ID-blocked after 1RT */
    ok(client_streams[i]->streams_blocked);

    /* reset one stream in both directions and close on the client-side */
    server_stream = quicly_get_stream(server, client_streams[i - 1]->stream_id);
    ok(server_stream != NULL);
    server_streambuf = server_stream->data;
    quicly_reset_stream(client_streams[i - 1], QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(123));
    quicly_request_stop(client_streams[i - 1], QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(456));
    transmit(client, server);
    transmit(server, client);
    ok(server_streambuf->error_received.reset_stream == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(123));
    ok(server_streambuf->error_received.stop_sending == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(456));
    ok(!server_streambuf->is_detached); /* haven't gotten ACK for reset */
    ok(client_streambufs[i - 1]->error_received.reset_stream == QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(456));
    ok(client_streambufs[i - 1]->is_detached);

    /* the last stream is still ID-blocked */
    ok(client_streams[i]->streams_blocked);

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;
    transmit(client, server);
    transmit(server, client);

    /* we would have free room now that RST of the server-sent side is ACKed */
    ok(server_streambuf->is_detached);
    ok(!client_streams[i]->streams_blocked);
    ++i;

    /* but we cannot open one more */
    ret = quicly_open_stream(client, client_streams + i, 0);
    ok(ret == 0);
    ok(client_streams[i]->streams_blocked);

    quicly_free(client);
    quicly_free(server);
}