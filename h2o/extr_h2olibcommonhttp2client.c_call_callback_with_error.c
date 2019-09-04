#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* on_body ) (TYPE_2__*,char const*) ;int /*<<< orphan*/  (* on_head ) (TYPE_2__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ _cb; } ;
struct st_h2o_http2client_stream_t {int state; TYPE_2__ super; } ;

/* Variables and functions */
#define  H2O_HTTP2CLIENT_STREAM_STATE_RECV_BODY 131 
#define  H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS 130 
#define  H2O_HTTP2CLIENT_STREAM_STATE_SEND_BODY 129 
#define  H2O_HTTP2CLIENT_STREAM_STATE_SEND_HEADERS 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char const*) ; 

__attribute__((used)) static void call_callback_with_error(struct st_h2o_http2client_stream_t *stream, const char *errstr)
{
    assert(errstr != NULL);
    switch (stream->state) {
    case H2O_HTTP2CLIENT_STREAM_STATE_SEND_HEADERS:
    case H2O_HTTP2CLIENT_STREAM_STATE_SEND_BODY:
    case H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS:
        stream->super._cb.on_head(&stream->super, errstr, 0x200, 0, h2o_iovec_init(NULL, 0), NULL, 0, 0);
        break;
    case H2O_HTTP2CLIENT_STREAM_STATE_RECV_BODY:
        stream->super._cb.on_body(&stream->super, errstr);
        break;
    }
}