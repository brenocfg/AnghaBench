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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t pos; size_t filtered; size_t size; int allocated; scalar_t__ end_was_reached; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ lzma_simple_coder ;
typedef  scalar_t__ const lzma_ret ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  int /*<<< orphan*/  lzma_action ;

/* Variables and functions */
 scalar_t__ const LZMA_OK ; 
 scalar_t__ const LZMA_OPTIONS_ERROR ; 
 scalar_t__ const LZMA_STREAM_END ; 
 int /*<<< orphan*/  LZMA_SYNC_FLUSH ; 
 int /*<<< orphan*/  assert (int) ; 
 void* call_filter (TYPE_1__*,int /*<<< orphan*/ *,size_t const) ; 
 scalar_t__ copy_or_code (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_bufcpy (int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 

__attribute__((used)) static lzma_ret
simple_code(void *coder_ptr, const lzma_allocator *allocator,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size, lzma_action action)
{
	lzma_simple_coder *coder = coder_ptr;

	// TODO: Add partial support for LZMA_SYNC_FLUSH. We can support it
	// in cases when the filter is able to filter everything. With most
	// simple filters it can be done at offset that is a multiple of 2,
	// 4, or 16. With x86 filter, it needs good luck, and thus cannot
	// be made to work predictably.
	if (action == LZMA_SYNC_FLUSH)
		return LZMA_OPTIONS_ERROR;

	// Flush already filtered data from coder->buffer[] to out[].
	if (coder->pos < coder->filtered) {
		lzma_bufcpy(coder->buffer, &coder->pos, coder->filtered,
				out, out_pos, out_size);

		// If we couldn't flush all the filtered data, return to
		// application immediately.
		if (coder->pos < coder->filtered)
			return LZMA_OK;

		if (coder->end_was_reached) {
			assert(coder->filtered == coder->size);
			return LZMA_STREAM_END;
		}
	}

	// If we get here, there is no filtered data left in the buffer.
	coder->filtered = 0;

	assert(!coder->end_was_reached);

	// If there is more output space left than there is unfiltered data
	// in coder->buffer[], flush coder->buffer[] to out[], and copy/code
	// more data to out[] hopefully filling it completely. Then filter
	// the data in out[]. This step is where most of the data gets
	// filtered if the buffer sizes used by the application are reasonable.
	const size_t out_avail = out_size - *out_pos;
	const size_t buf_avail = coder->size - coder->pos;
	if (out_avail > buf_avail || buf_avail == 0) {
		// Store the old position so that we know from which byte
		// to start filtering.
		const size_t out_start = *out_pos;

		// Flush data from coder->buffer[] to out[], but don't reset
		// coder->pos and coder->size yet. This way the coder can be
		// restarted if the next filter in the chain returns e.g.
		// LZMA_MEM_ERROR.
		memcpy(out + *out_pos, coder->buffer + coder->pos, buf_avail);
		*out_pos += buf_avail;

		// Copy/Encode/Decode more data to out[].
		{
			const lzma_ret ret = copy_or_code(coder, allocator,
					in, in_pos, in_size,
					out, out_pos, out_size, action);
			assert(ret != LZMA_STREAM_END);
			if (ret != LZMA_OK)
				return ret;
		}

		// Filter out[].
		const size_t size = *out_pos - out_start;
		const size_t filtered = call_filter(
				coder, out + out_start, size);

		const size_t unfiltered = size - filtered;
		assert(unfiltered <= coder->allocated / 2);

		// Now we can update coder->pos and coder->size, because
		// the next coder in the chain (if any) was successful.
		coder->pos = 0;
		coder->size = unfiltered;

		if (coder->end_was_reached) {
			// The last byte has been copied to out[] already.
			// They are left as is.
			coder->size = 0;

		} else if (unfiltered > 0) {
			// There is unfiltered data left in out[]. Copy it to
			// coder->buffer[] and rewind *out_pos appropriately.
			*out_pos -= unfiltered;
			memcpy(coder->buffer, out + *out_pos, unfiltered);
		}
	} else if (coder->pos > 0) {
		memmove(coder->buffer, coder->buffer + coder->pos, buf_avail);
		coder->size -= coder->pos;
		coder->pos = 0;
	}

	assert(coder->pos == 0);

	// If coder->buffer[] isn't empty, try to fill it by copying/decoding
	// more data. Then filter coder->buffer[] and copy the successfully
	// filtered data to out[]. It is probable, that some filtered and
	// unfiltered data will be left to coder->buffer[].
	if (coder->size > 0) {
		{
			const lzma_ret ret = copy_or_code(coder, allocator,
					in, in_pos, in_size,
					coder->buffer, &coder->size,
					coder->allocated, action);
			assert(ret != LZMA_STREAM_END);
			if (ret != LZMA_OK)
				return ret;
		}

		coder->filtered = call_filter(
				coder, coder->buffer, coder->size);

		// Everything is considered to be filtered if coder->buffer[]
		// contains the last bytes of the data.
		if (coder->end_was_reached)
			coder->filtered = coder->size;

		// Flush as much as possible.
		lzma_bufcpy(coder->buffer, &coder->pos, coder->filtered,
				out, out_pos, out_size);
	}

	// Check if we got everything done.
	if (coder->end_was_reached && coder->pos == coder->size)
		return LZMA_STREAM_END;

	return LZMA_OK;
}