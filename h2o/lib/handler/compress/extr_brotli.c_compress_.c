#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int size; TYPE_3__* entries; } ;
struct st_brotli_context_t {TYPE_2__ bufs; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {size_t len; scalar_t__ raw; TYPE_1__* callbacks; } ;
typedef  TYPE_3__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_compress_context_t ;
struct TYPE_6__ {scalar_t__ flatten; } ;
typedef  int /*<<< orphan*/  BrotliEncoderOperation ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_OPERATION_FINISH ; 
 int /*<<< orphan*/  BROTLI_OPERATION_FLUSH ; 
 int /*<<< orphan*/  BROTLI_OPERATION_PROCESS ; 
 scalar_t__ BrotliEncoderHasMoreOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compress_core (struct st_brotli_context_t*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t*) ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_sendvec_flatten_raw ; 
 int /*<<< orphan*/  shrink_buf (struct st_brotli_context_t*,int) ; 

__attribute__((used)) static h2o_send_state_t compress_(h2o_compress_context_t *_self, h2o_sendvec_t *inbufs, size_t inbufcnt, h2o_send_state_t state,
                                  h2o_sendvec_t **outbufs, size_t *outbufcnt)
{
    struct st_brotli_context_t *self = (void *)_self;
    BrotliEncoderOperation final_op = h2o_send_state_is_in_progress(state) ? BROTLI_OPERATION_FLUSH : BROTLI_OPERATION_FINISH;
    const uint8_t *src;
    size_t i, srclen;

    shrink_buf(self, 1);
    self->bufs.entries[0].len = 0;

    /* encode chunks and flush */
    if (inbufcnt != 0) {
        for (i = 0; i < inbufcnt; ++i) {
            assert(inbufs[i].callbacks->flatten == h2o_sendvec_flatten_raw);
            src = (void *)inbufs[i].raw;
            srclen = inbufs[i].len;
            BrotliEncoderOperation op = i + 1 == inbufcnt ? final_op : BROTLI_OPERATION_PROCESS;
            while (srclen != 0)
                compress_core(self, op, &src, &srclen);
        }
    } else {
        src = NULL;
        srclen = 0;
        compress_core(self, final_op, &src, &srclen);
    }

    /* emit pending output, if any */
    while (BrotliEncoderHasMoreOutput(self->state)) {
        src = NULL;
        srclen = 0;
        compress_core(self, final_op, &src, &srclen);
    }

    *outbufs = self->bufs.entries;
    *outbufcnt = self->bufs.size - (self->bufs.entries[self->bufs.size - 1].len == 0);

    return state;
}