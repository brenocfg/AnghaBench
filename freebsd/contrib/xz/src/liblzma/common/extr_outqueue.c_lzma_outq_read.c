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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  lzma_vli ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {scalar_t__ bufs_used; size_t bufs_pos; scalar_t__ read_pos; TYPE_2__* bufs; scalar_t__ bufs_allocated; } ;
typedef  TYPE_1__ lzma_outq ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  unpadded_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  finished; } ;
typedef  TYPE_2__ lzma_outbuf ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_STREAM_END ; 
 int /*<<< orphan*/  lzma_bufcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,size_t*,size_t) ; 

extern lzma_ret
lzma_outq_read(lzma_outq *restrict outq, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size,
		lzma_vli *restrict unpadded_size,
		lzma_vli *restrict uncompressed_size)
{
	// There must be at least one buffer from which to read.
	if (outq->bufs_used == 0)
		return LZMA_OK;

	// Get the buffer.
	uint32_t i = outq->bufs_pos - outq->bufs_used;
	if (outq->bufs_pos < outq->bufs_used)
		i += outq->bufs_allocated;

	lzma_outbuf *buf = &outq->bufs[i];

	// If it isn't finished yet, we cannot read from it.
	if (!buf->finished)
		return LZMA_OK;

	// Copy from the buffer to output.
	lzma_bufcpy(buf->buf, &outq->read_pos, buf->size,
			out, out_pos, out_size);

	// Return if we didn't get all the data from the buffer.
	if (outq->read_pos < buf->size)
		return LZMA_OK;

	// The buffer was finished. Tell the caller its size information.
	*unpadded_size = buf->unpadded_size;
	*uncompressed_size = buf->uncompressed_size;

	// Free this buffer for further use.
	--outq->bufs_used;
	outq->read_pos = 0;

	return LZMA_STREAM_END;
}