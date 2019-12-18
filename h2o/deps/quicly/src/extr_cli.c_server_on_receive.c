#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sendstate; int /*<<< orphan*/  recvstate; } ;
typedef  TYPE_1__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_request (int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  quicly_streambuf_ingress_get (TYPE_1__*) ; 
 int quicly_streambuf_ingress_receive (TYPE_1__*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  quicly_streambuf_ingress_shift (TYPE_1__*,size_t) ; 
 scalar_t__ send_file (TYPE_1__*,int,char*,char*) ; 
 int /*<<< orphan*/  send_header (TYPE_1__*,int,int,char*) ; 
 scalar_t__ send_sized_text (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  send_str (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ validate_path (char*) ; 

__attribute__((used)) static int server_on_receive(quicly_stream_t *stream, size_t off, const void *src, size_t len)
{
    char *path;
    int is_http1;
    int ret;

    if ((ret = quicly_streambuf_ingress_receive(stream, off, src, len)) != 0)
        return ret;

    if (!parse_request(quicly_streambuf_ingress_get(stream), &path, &is_http1)) {
        if (!quicly_recvstate_transfer_complete(&stream->recvstate))
            return 0;
        /* failed to parse request */
        send_header(stream, 1, 500, "text/plain; charset=utf-8");
        send_str(stream, "failed to parse HTTP request\n");
        goto Sent;
    }
    if (!quicly_recvstate_transfer_complete(&stream->recvstate))
        quicly_request_stop(stream, QUICLY_ERROR_FROM_APPLICATION_ERROR_CODE(0));

    if (strcmp(path, "/logo.jpg") == 0 && send_file(stream, is_http1, "assets/logo.jpg", "image/jpeg"))
        goto Sent;
    if (strcmp(path, "/main.jpg") == 0 && send_file(stream, is_http1, "assets/main.jpg", "image/jpeg"))
        goto Sent;
    if (send_sized_text(stream, path, is_http1))
        goto Sent;
    if (validate_path(path) && send_file(stream, is_http1, path + 1, "text/plain"))
        goto Sent;

    if (!quicly_sendstate_is_open(&stream->sendstate))
        return 0;

    send_header(stream, is_http1, 404, "text/plain; charset=utf-8");
    send_str(stream, "not found\n");
Sent:
    quicly_streambuf_egress_shutdown(stream);
    quicly_streambuf_ingress_shift(stream, len);
    return 0;
}