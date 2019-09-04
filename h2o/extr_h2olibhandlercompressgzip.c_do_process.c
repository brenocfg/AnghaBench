#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ transform; } ;
struct TYPE_7__ {TYPE_3__* entries; } ;
struct st_gzip_context_t {scalar_t__ zs_is_open; int /*<<< orphan*/  zs; TYPE_2__ super; TYPE_1__ bufs; } ;
typedef  int /*<<< orphan*/  processor ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_compress_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ do_compress ; 
 TYPE_3__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 size_t process_chunk (struct st_gzip_context_t*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_process(h2o_compress_context_t *_self, h2o_iovec_t *inbufs, size_t inbufcnt, h2o_send_state_t state,
                       h2o_iovec_t **outbufs, size_t *outbufcnt, processor proc)
{
    struct st_gzip_context_t *self = (void *)_self;
    size_t outbufindex;
    h2o_iovec_t last_buf;

    outbufindex = 0;
    self->bufs.entries[0].len = 0;

    if (inbufcnt != 0) {
        size_t i;
        for (i = 0; i != inbufcnt - 1; ++i)
            outbufindex = process_chunk(self, inbufs[i].base, inbufs[i].len, Z_NO_FLUSH, outbufindex, proc);
        last_buf = inbufs[i];
    } else {
        last_buf = h2o_iovec_init(NULL, 0);
    }
    outbufindex = process_chunk(self, last_buf.base, last_buf.len, h2o_send_state_is_in_progress(state) ? Z_SYNC_FLUSH : Z_FINISH,
                                outbufindex, proc);

    *outbufs = self->bufs.entries;
    *outbufcnt = outbufindex + 1;

    if (!h2o_send_state_is_in_progress(state)) {
        if (self->super.transform == do_compress) {
            deflateEnd(&self->zs);
        } else {
            inflateEnd(&self->zs);
        }
        self->zs_is_open = 0;
    }
}