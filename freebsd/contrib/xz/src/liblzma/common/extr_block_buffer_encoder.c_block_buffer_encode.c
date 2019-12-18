#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_10__ {int /*<<< orphan*/  u8; } ;
struct TYPE_11__ {TYPE_1__ buffer; } ;
typedef  TYPE_2__ lzma_check_state ;
struct TYPE_12__ {int version; size_t uncompressed_size; scalar_t__ compressed_size; int* raw_check; scalar_t__ check; int /*<<< orphan*/ * filters; } ;
typedef  TYPE_3__ lzma_block ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 scalar_t__ LZMA_BUF_ERROR ; 
 unsigned int LZMA_CHECK_ID_MAX ; 
 scalar_t__ LZMA_DATA_ERROR ; 
 scalar_t__ LZMA_OK ; 
 scalar_t__ LZMA_OPTIONS_ERROR ; 
 scalar_t__ LZMA_PROG_ERROR ; 
 scalar_t__ LZMA_UNSUPPORTED_CHECK ; 
 size_t const UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ block_encode_normal (TYPE_3__*,int /*<<< orphan*/  const*,int const*,size_t,int*,size_t*,size_t) ; 
 int /*<<< orphan*/  block_encode_uncompressed (TYPE_3__*,int const*,size_t,int*,size_t*,size_t) ; 
 scalar_t__ lzma2_bound (size_t) ; 
 int /*<<< orphan*/  lzma_check_finish (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lzma_check_init (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lzma_check_is_supported (scalar_t__) ; 
 size_t lzma_check_size (scalar_t__) ; 
 int /*<<< orphan*/  lzma_check_update (TYPE_2__*,scalar_t__,int const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
block_buffer_encode(lzma_block *block, const lzma_allocator *allocator,
		const uint8_t *in, size_t in_size,
		uint8_t *out, size_t *out_pos, size_t out_size,
		bool try_to_compress)
{
	// Validate the arguments.
	if (block == NULL || (in == NULL && in_size != 0) || out == NULL
			|| out_pos == NULL || *out_pos > out_size)
		return LZMA_PROG_ERROR;

	// The contents of the structure may depend on the version so
	// check the version before validating the contents of *block.
	if (block->version > 1)
		return LZMA_OPTIONS_ERROR;

	if ((unsigned int)(block->check) > LZMA_CHECK_ID_MAX
			|| (try_to_compress && block->filters == NULL))
		return LZMA_PROG_ERROR;

	if (!lzma_check_is_supported(block->check))
		return LZMA_UNSUPPORTED_CHECK;

	// Size of a Block has to be a multiple of four, so limit the size
	// here already. This way we don't need to check it again when adding
	// Block Padding.
	out_size -= (out_size - *out_pos) & 3;

	// Get the size of the Check field.
	const size_t check_size = lzma_check_size(block->check);
	assert(check_size != UINT32_MAX);

	// Reserve space for the Check field.
	if (out_size - *out_pos <= check_size)
		return LZMA_BUF_ERROR;

	out_size -= check_size;

	// Initialize block->uncompressed_size and calculate the worst-case
	// value for block->compressed_size.
	block->uncompressed_size = in_size;
	block->compressed_size = lzma2_bound(in_size);
	if (block->compressed_size == 0)
		return LZMA_DATA_ERROR;

	// Do the actual compression.
	lzma_ret ret = LZMA_BUF_ERROR;
	if (try_to_compress)
		ret = block_encode_normal(block, allocator,
				in, in_size, out, out_pos, out_size);

	if (ret != LZMA_OK) {
		// If the error was something else than output buffer
		// becoming full, return the error now.
		if (ret != LZMA_BUF_ERROR)
			return ret;

		// The data was uncompressible (at least with the options
		// given to us) or the output buffer was too small. Use the
		// uncompressed chunks of LZMA2 to wrap the data into a valid
		// Block. If we haven't been given enough output space, even
		// this may fail.
		return_if_error(block_encode_uncompressed(block, in, in_size,
				out, out_pos, out_size));
	}

	assert(*out_pos <= out_size);

	// Block Padding. No buffer overflow here, because we already adjusted
	// out_size so that (out_size - out_start) is a multiple of four.
	// Thus, if the buffer is full, the loop body can never run.
	for (size_t i = (size_t)(block->compressed_size); i & 3; ++i) {
		assert(*out_pos < out_size);
		out[(*out_pos)++] = 0x00;
	}

	// If there's no Check field, we are done now.
	if (check_size > 0) {
		// Calculate the integrity check. We reserved space for
		// the Check field earlier so we don't need to check for
		// available output space here.
		lzma_check_state check;
		lzma_check_init(&check, block->check);
		lzma_check_update(&check, block->check, in, in_size);
		lzma_check_finish(&check, block->check);

		memcpy(block->raw_check, check.buffer.u8, check_size);
		memcpy(out + *out_pos, check.buffer.u8, check_size);
		*out_pos += check_size;
	}

	return LZMA_OK;
}