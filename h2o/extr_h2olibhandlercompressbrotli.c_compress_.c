#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int size; TYPE_2__* entries; } ;
struct st_brotli_context_t {TYPE_1__ bufs; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_6__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_compress_context_t ;
typedef  int /*<<< orphan*/  BrotliEncoderOperation ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_OPERATION_FINISH ; 
 int /*<<< orphan*/  BROTLI_OPERATION_FLUSH ; 
 int /*<<< orphan*/  BROTLI_OPERATION_PROCESS ; 
 scalar_t__ BrotliEncoderHasMoreOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compress_core (struct st_brotli_context_t*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t*) ; 
 scalar_t__ h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shrink_buf (struct st_brotli_context_t*,int) ; 

__attribute__((used)) static void compress_(h2o_compress_context_t *_self, h2o_iovec_t *inbufs, size_t inbufcnt, h2o_send_state_t state,
                      h2o_iovec_t **outbufs, size_t *outbufcnt)
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
            src = (void *)inbufs[i].base;
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
}