#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {size_t size; TYPE_5__* entries; } ;
struct TYPE_9__ {size_t off_within_first_vec; int proceed_called; TYPE_2__ vecs; } ;
struct st_h2o_http3_server_stream_t {scalar_t__ send_state; int /*<<< orphan*/  quic; int /*<<< orphan*/  req; TYPE_3__ sendbuf; } ;
struct TYPE_10__ {struct st_h2o_http3_server_stream_t* data; } ;
typedef  TYPE_4__ quicly_stream_t ;
struct TYPE_11__ {size_t len; TYPE_1__* callbacks; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* flatten ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_INTERNAL ; 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT ; 
 scalar_t__ H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  h2o_proceed_response_deferred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_reset_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retain_sendvecs (struct st_h2o_http3_server_stream_t*) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int on_send_emit(quicly_stream_t *qs, size_t off, void *_dst, size_t *len, int *wrote_all)
{
    struct st_h2o_http3_server_stream_t *stream = qs->data;
    uint8_t *dst = _dst, *dst_end = dst + *len;
    size_t vec_index = 0, off_within_vec = stream->sendbuf.off_within_first_vec;

    /* find the start position */
    while (off != 0) {
        assert(vec_index < stream->sendbuf.vecs.size);
        if (off < stream->sendbuf.vecs.entries[vec_index].len - off_within_vec)
            break;
        off -= stream->sendbuf.vecs.entries[vec_index].len - off_within_vec;
        off_within_vec = 0;
        ++vec_index;
    }

    /* write */
    *wrote_all = 0;
    while (dst != dst_end) {
        if (vec_index == stream->sendbuf.vecs.size) {
            *wrote_all = 1;
            break;
        }
        size_t sz = stream->sendbuf.vecs.entries[vec_index].len - (off + off_within_vec);
        if (dst_end - dst < sz)
            sz = dst_end - dst;
        if (!(stream->sendbuf.vecs.entries[vec_index].callbacks->flatten)(stream->sendbuf.vecs.entries + vec_index, &stream->req,
                                                                          h2o_iovec_init(dst, sz), off + off_within_vec))
            goto Error;
        dst += sz;
        /* prepare to write next */
        off = 0;
        off_within_vec = 0;
        ++vec_index;
    }

    *len = dst - (uint8_t *)_dst;

    if (*wrote_all && stream->send_state == H2O_SEND_STATE_IN_PROGRESS && !stream->sendbuf.proceed_called) {
        if (!retain_sendvecs(stream))
            goto Error;
        stream->sendbuf.proceed_called = 1;
        h2o_proceed_response_deferred(&stream->req);
    }

    return 0;

Error:
    *len = 0;
    *wrote_all = 1;
    quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_INTERNAL);
    set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
    return 0;
}