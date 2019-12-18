#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* on_body ) (TYPE_4__*,char const*) ;int /*<<< orphan*/  (* on_head ) (TYPE_4__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_3__ _cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* proceed_req ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int res; } ;
struct st_h2o_http2client_stream_t {TYPE_4__ super; TYPE_1__ streaming; TYPE_2__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
#define  STREAM_STATE_BODY 130 
#define  STREAM_STATE_CLOSED 129 
#define  STREAM_STATE_HEAD 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void call_callback_with_error(struct st_h2o_http2client_stream_t *stream, const char *errstr)
{
    assert(errstr != NULL);
    switch (stream->state.res) {
    case STREAM_STATE_HEAD:
        stream->super._cb.on_head(&stream->super, errstr, 0x200, 0, h2o_iovec_init(NULL, 0), NULL, 0, 0);
        break;
    case STREAM_STATE_BODY:
        stream->super._cb.on_body(&stream->super, errstr);
        break;
    case STREAM_STATE_CLOSED:
        if (stream->streaming.proceed_req != NULL) {
            stream->streaming.proceed_req(&stream->super, 0, H2O_SEND_STATE_ERROR);
        }
        break;
    }
}