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
struct TYPE_5__ {int bufs_used; int bufs_allocated; size_t bufs_pos; int buf_size_max; int /*<<< orphan*/  bufs_mem; TYPE_2__* bufs; } ;
typedef  TYPE_1__ lzma_outq ;
struct TYPE_6__ {int finished; scalar_t__ size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ lzma_outbuf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

extern lzma_outbuf *
lzma_outq_get_buf(lzma_outq *outq)
{
	// Caller must have checked it with lzma_outq_has_buf().
	assert(outq->bufs_used < outq->bufs_allocated);

	// Initialize the new buffer.
	lzma_outbuf *buf = &outq->bufs[outq->bufs_pos];
	buf->buf = outq->bufs_mem + outq->bufs_pos * outq->buf_size_max;
	buf->size = 0;
	buf->finished = false;

	// Update the queue state.
	if (++outq->bufs_pos == outq->bufs_allocated)
		outq->bufs_pos = 0;

	++outq->bufs_used;

	return buf;
}