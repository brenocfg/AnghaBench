#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_18__ {scalar_t__ size; } ;
struct TYPE_19__ {TYPE_1__ vecs; } ;
struct TYPE_20__ {TYPE_2__ egress; int /*<<< orphan*/  ingress; } ;
struct TYPE_22__ {TYPE_3__ super; } ;
typedef  TYPE_5__ test_streambuf_t ;
struct TYPE_23__ {TYPE_5__* data; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_6__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
struct TYPE_24__ {scalar_t__ (* cb ) (TYPE_7__*) ;} ;
struct TYPE_21__ {int max_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  sa; } ;
struct TYPE_16__ {TYPE_4__ transport_params; TYPE_7__* now; } ;

/* Variables and functions */
 scalar_t__ QUICLY_DELAYED_ACK_TIMEOUT ; 
 scalar_t__ QUICLY_STATE_CONNECTED ; 
 int buffer_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  decode_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 TYPE_15__ fake_address ; 
 int /*<<< orphan*/  free_packets (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  new_master_id () ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_12__ quic_ctx ; 
 int /*<<< orphan*/  quic_now ; 
 int quicly_accept (int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int quicly_connect (int /*<<< orphan*/ *,TYPE_12__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int quicly_connection_is_ready (int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_get_first_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_get_state (int /*<<< orphan*/ ) ; 
 TYPE_6__* quicly_get_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quicly_open_stream (int /*<<< orphan*/ ,TYPE_6__**,int /*<<< orphan*/ ) ; 
 int quicly_send (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_write (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_streambuf_ingress_shift (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tiny_connection_window(void)
{
    uint64_t max_data_orig = quic_ctx.transport_params.max_data;
    quicly_stream_t *client_stream, *server_stream;
    test_streambuf_t *client_streambuf, *server_streambuf;
    size_t i;
    int ret;
    char testdata[1025];

    quic_ctx.transport_params.max_data = 1024;
    for (i = 0; i < 1024 / 16; ++i)
        strcpy(testdata + i * 16, "0123456789abcdef");
    testdata[1024] = '\0';

    { /* create connection and write 16KB */
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
        ok(quicly_get_first_timeout(client) > quic_ctx.now->cb(quic_ctx.now));
        decode_packets(&decoded, &raw, 1);
        ok(num_packets == 1);
        ret = quicly_accept(&server, &quic_ctx, NULL, &fake_address.sa, &decoded, NULL, new_master_id(), NULL);
        ok(ret == 0);
        free_packets(&raw, 1);
    }

    transmit(server, client);
    ok(quicly_get_state(client) == QUICLY_STATE_CONNECTED);
    ok(quicly_connection_is_ready(client));

    ret = quicly_open_stream(client, &client_stream, 0);
    ok(ret == 0);
    client_streambuf = client_stream->data;
    for (i = 0; i < 16; ++i)
        quicly_streambuf_egress_write(client_stream, testdata, strlen(testdata));

    transmit(client, server);

    server_stream = quicly_get_stream(server, client_stream->stream_id);
    ok(server_stream != NULL);
    server_streambuf = server_stream->data;
    ok(buffer_is(&server_streambuf->super.ingress, testdata));
    quicly_streambuf_ingress_shift(server_stream, strlen(testdata));

    for (i = 1; i < 16; ++i) {
        transmit(server, client);
        transmit(client, server);
        ok(buffer_is(&server_streambuf->super.ingress, testdata));
        quicly_streambuf_ingress_shift(server_stream, strlen(testdata));
    }

    quic_now += QUICLY_DELAYED_ACK_TIMEOUT;
    transmit(server, client);

    ok(client_streambuf->super.egress.vecs.size == 0);

    quic_ctx.transport_params.max_data = max_data_orig;
}