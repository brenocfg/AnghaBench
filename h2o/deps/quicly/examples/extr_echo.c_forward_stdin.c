#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sendstate; } ;
typedef  TYPE_1__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 TYPE_1__* quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_write (TYPE_1__*,char*,size_t) ; 
 size_t read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int forward_stdin(quicly_conn_t *conn)
{
    quicly_stream_t *stream0;
    char buf[4096];
    size_t rret;

    if ((stream0 = quicly_get_stream(conn, 0)) == NULL || !quicly_sendstate_is_open(&stream0->sendstate))
        return 0;

    while ((rret = read(0, buf, sizeof(buf))) == -1 && errno == EINTR)
        ;
    if (rret == 0) {
        /* stdin closed, close the send-side of stream0 */
        quicly_streambuf_egress_shutdown(stream0);
        return 0;
    } else {
        /* write data to send buffer */
        quicly_streambuf_egress_write(stream0, buf, rret);
        return 1;
    }
}