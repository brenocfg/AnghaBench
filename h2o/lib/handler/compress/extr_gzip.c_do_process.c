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
struct TYPE_9__ {scalar_t__ do_transform; } ;
struct TYPE_8__ {TYPE_4__* entries; } ;
struct st_gzip_context_t {scalar_t__ zs_is_open; int /*<<< orphan*/  zs; TYPE_3__ super; TYPE_2__ bufs; } ;
typedef  int /*<<< orphan*/  processor ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  raw; int /*<<< orphan*/  member_0; TYPE_1__* callbacks; } ;
typedef  TYPE_4__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_compress_context_t ;
struct TYPE_7__ {scalar_t__ flatten; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ do_compress ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_sendvec_flatten_raw ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 size_t process_chunk (struct st_gzip_context_t*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_send_state_t do_process(h2o_compress_context_t *_self, h2o_sendvec_t *inbufs, size_t inbufcnt, h2o_send_state_t state,
                                   h2o_sendvec_t **outbufs, size_t *outbufcnt, processor proc)
{
    struct st_gzip_context_t *self = (void *)_self;
    size_t outbufindex;
    h2o_sendvec_t *last_buf;

    outbufindex = 0;
    self->bufs.entries[0].len = 0;

    if (inbufcnt != 0) {
        size_t i;
        for (i = 0; i != inbufcnt - 1; ++i) {
            assert(inbufs[i].callbacks->flatten == h2o_sendvec_flatten_raw);
            outbufindex = process_chunk(self, inbufs[i].raw, inbufs[i].len, Z_NO_FLUSH, outbufindex, proc);
        }
        assert(inbufs[i].callbacks->flatten == h2o_sendvec_flatten_raw);
        last_buf = inbufs + i;
    } else {
        static const h2o_sendvec_t zero_buf = {0};
        last_buf = (h2o_sendvec_t *)&zero_buf;
    }
    outbufindex = process_chunk(self, last_buf->raw, last_buf->len, h2o_send_state_is_in_progress(state) ? Z_SYNC_FLUSH : Z_FINISH,
                                outbufindex, proc);

    *outbufs = self->bufs.entries;
    *outbufcnt = outbufindex + 1;

    if (!h2o_send_state_is_in_progress(state)) {
        if (self->super.do_transform == do_compress) {
            deflateEnd(&self->zs);
        } else {
            inflateEnd(&self->zs);
        }
        self->zs_is_open = 0;
    }

    return state;
}