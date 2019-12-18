#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int size; TYPE_1__* entries; } ;
struct st_brotli_context_t {scalar_t__ buf_capacity; TYPE_2__ bufs; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ raw; } ;
typedef  int /*<<< orphan*/  BrotliEncoderOperation ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliEncoderCompressStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_buf (struct st_brotli_context_t*) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 

__attribute__((used)) static void compress_core(struct st_brotli_context_t *self, BrotliEncoderOperation op, const uint8_t **src, size_t *srclen)
{
    size_t bufindex = self->bufs.size - 1;

    if (self->bufs.entries[bufindex].len == self->buf_capacity) {
        expand_buf(self);
        ++bufindex;
    }
    uint8_t *dst = (uint8_t *)self->bufs.entries[bufindex].raw + self->bufs.entries[bufindex].len;
    size_t dstlen = self->buf_capacity - self->bufs.entries[bufindex].len;

    if (!BrotliEncoderCompressStream(self->state, op, srclen, src, &dstlen, &dst, NULL))
        h2o_fatal("BrotliEncoderCompressStream");

    self->bufs.entries[bufindex].len = self->buf_capacity - dstlen;
}