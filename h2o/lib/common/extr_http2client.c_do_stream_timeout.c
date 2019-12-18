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
struct TYPE_2__ {scalar_t__ res; } ;
struct st_h2o_http2client_stream_t {TYPE_1__ state; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 scalar_t__ STREAM_STATE_HEAD ; 
 int /*<<< orphan*/  call_callback_with_error (struct st_h2o_http2client_stream_t*,char const*) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 
 int /*<<< orphan*/  h2o_httpclient_error_connect_timeout ; 
 char* h2o_httpclient_error_first_byte_timeout ; 
 char* h2o_httpclient_error_io_timeout ; 
 int /*<<< orphan*/  on_connect_error (struct st_h2o_http2client_stream_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_stream_timeout(struct st_h2o_http2client_stream_t *stream)
{
    if (stream->conn == NULL) {
        on_connect_error(stream, h2o_httpclient_error_connect_timeout);
        return;
    }
    const char *errstr =
        stream->state.res == STREAM_STATE_HEAD ? h2o_httpclient_error_first_byte_timeout : h2o_httpclient_error_io_timeout;
    call_callback_with_error(stream, errstr);
    close_stream(stream);
}