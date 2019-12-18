#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  recvstate; int /*<<< orphan*/  sendstate; } ;
typedef  TYPE_1__ quicly_stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ ptls_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_server () ; 
 int /*<<< orphan*/  quicly_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_sendstate_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ quicly_streambuf_ingress_get (TYPE_1__*) ; 
 int quicly_streambuf_ingress_receive (TYPE_1__*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  quicly_streambuf_ingress_shift (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int on_receive(quicly_stream_t *stream, size_t off, const void *src, size_t len)
{
    int ret;

    /* read input to receive buffer */
    if ((ret = quicly_streambuf_ingress_receive(stream, off, src, len)) != 0)
        return ret;

    /* obtain contiguous bytes from the receive buffer */
    ptls_iovec_t input = quicly_streambuf_ingress_get(stream);

    if (is_server()) {
        /* server: echo back to the client */
        if (quicly_sendstate_is_open(&stream->sendstate)) {
            quicly_streambuf_egress_write(stream, input.base, input.len);
            /* shutdown the stream after echoing all data */
            if (quicly_recvstate_transfer_complete(&stream->recvstate))
                quicly_streambuf_egress_shutdown(stream);
        }
    } else {
        /* client: print to stdout */
        fwrite(input.base, 1, input.len, stdout);
        fflush(stdout);
        /* initiate connection close after receiving all data */
        if (quicly_recvstate_transfer_complete(&stream->recvstate))
            quicly_close(stream->conn, 0, "");
    }

    /* remove used bytes from receive buffer */
    quicly_streambuf_ingress_shift(stream, input.len);

    return 0;
}