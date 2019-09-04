#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int avail_in; scalar_t__ avail_out; void* next_out; void* next_in; } ;
struct TYPE_7__ {size_t size; TYPE_1__* entries; } ;
struct st_gzip_context_t {TYPE_2__ zs; TYPE_4__ bufs; } ;
typedef  int (* processor ) (TYPE_2__*,int) ;
struct TYPE_5__ {scalar_t__ len; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BUF_SIZE ; 
 int Z_BUF_ERROR ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  expand_buf (TYPE_4__*) ; 

__attribute__((used)) static size_t process_chunk(struct st_gzip_context_t *self, const void *src, size_t len, int flush, size_t bufindex, processor proc)
{
    int ret;

    self->zs.next_in = (void *)src;
    self->zs.avail_in = (unsigned)len;

    /* man says: If inflate/deflate returns with avail_out == 0, this function must be called again with the same value of the flush
     * parameter and more output space (updated avail_out), until the flush is complete (function returns with non-zero avail_out).
     */
    do {
        /* expand buffer (note: in case of Z_SYNC_FLUSH we need to supply at least 6 bytes of output buffer) */
        if (self->bufs.entries[bufindex].len + 32 > BUF_SIZE) {
            ++bufindex;
            if (bufindex == self->bufs.size)
                expand_buf(&self->bufs);
            self->bufs.entries[bufindex].len = 0;
        }
        self->zs.next_out = (void *)(self->bufs.entries[bufindex].base + self->bufs.entries[bufindex].len);
        self->zs.avail_out = (unsigned)(BUF_SIZE - self->bufs.entries[bufindex].len);
        ret = proc(&self->zs, flush);
        /* inflate() returns Z_BUF_ERROR if flush is set to Z_FINISH at the middle of the compressed data */
        assert(ret == Z_OK || ret == Z_STREAM_END || ret == Z_BUF_ERROR);
        self->bufs.entries[bufindex].len = BUF_SIZE - self->zs.avail_out;
    } while (self->zs.avail_out == 0 && ret != Z_STREAM_END);

    return bufindex;
}