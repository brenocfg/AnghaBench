#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {scalar_t__ buf_size_max; int bufs_allocated; scalar_t__ read_pos; scalar_t__ bufs_used; scalar_t__ bufs_pos; int /*<<< orphan*/ * bufs_mem; int /*<<< orphan*/ * bufs; } ;
typedef  TYPE_1__ lzma_outq ;
typedef  int /*<<< orphan*/  lzma_outbuf ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  get_options (scalar_t__*,int*,scalar_t__,int) ; 
 void* lzma_alloc (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_outq_end (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 

extern lzma_ret
lzma_outq_init(lzma_outq *outq, const lzma_allocator *allocator,
		uint64_t buf_size_max, uint32_t threads)
{
	uint64_t bufs_alloc_size;
	uint32_t bufs_count;

	// Set bufs_count and bufs_alloc_size.
	return_if_error(get_options(&bufs_alloc_size, &bufs_count,
			buf_size_max, threads));

	// Allocate memory if needed.
	if (outq->buf_size_max != buf_size_max
			|| outq->bufs_allocated != bufs_count) {
		lzma_outq_end(outq, allocator);

#if SIZE_MAX < UINT64_MAX
		if (bufs_alloc_size > SIZE_MAX)
			return LZMA_MEM_ERROR;
#endif

		outq->bufs = lzma_alloc(bufs_count * sizeof(lzma_outbuf),
				allocator);
		outq->bufs_mem = lzma_alloc((size_t)(bufs_alloc_size),
				allocator);

		if (outq->bufs == NULL || outq->bufs_mem == NULL) {
			lzma_outq_end(outq, allocator);
			return LZMA_MEM_ERROR;
		}
	}

	// Initialize the rest of the main structure. Initialization of
	// outq->bufs[] is done when they are actually needed.
	outq->buf_size_max = (size_t)(buf_size_max);
	outq->bufs_allocated = bufs_count;
	outq->bufs_pos = 0;
	outq->bufs_used = 0;
	outq->read_pos = 0;

	return LZMA_OK;
}