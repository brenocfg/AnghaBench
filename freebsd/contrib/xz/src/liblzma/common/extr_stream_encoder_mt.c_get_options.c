#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {int /*<<< orphan*/ * filters; } ;
typedef  TYPE_1__ lzma_options_easy ;
struct TYPE_7__ {scalar_t__ flags; scalar_t__ threads; scalar_t__ block_size; int /*<<< orphan*/  preset; int /*<<< orphan*/ * filters; } ;
typedef  TYPE_2__ lzma_mt ;
typedef  int /*<<< orphan*/  lzma_filter ;

/* Variables and functions */
 scalar_t__ BLOCK_SIZE_MAX ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 scalar_t__ LZMA_THREADS_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lzma_block_buffer_bound64 (scalar_t__) ; 
 scalar_t__ lzma_easy_preset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_mt_block_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static lzma_ret
get_options(const lzma_mt *options, lzma_options_easy *opt_easy,
		const lzma_filter **filters, uint64_t *block_size,
		uint64_t *outbuf_size_max)
{
	// Validate some of the options.
	if (options == NULL)
		return LZMA_PROG_ERROR;

	if (options->flags != 0 || options->threads == 0
			|| options->threads > LZMA_THREADS_MAX)
		return LZMA_OPTIONS_ERROR;

	if (options->filters != NULL) {
		// Filter chain was given, use it as is.
		*filters = options->filters;
	} else {
		// Use a preset.
		if (lzma_easy_preset(opt_easy, options->preset))
			return LZMA_OPTIONS_ERROR;

		*filters = opt_easy->filters;
	}

	// Block size
	if (options->block_size > 0) {
		if (options->block_size > BLOCK_SIZE_MAX)
			return LZMA_OPTIONS_ERROR;

		*block_size = options->block_size;
	} else {
		// Determine the Block size from the filter chain.
		*block_size = lzma_mt_block_size(*filters);
		if (*block_size == 0)
			return LZMA_OPTIONS_ERROR;

		assert(*block_size <= BLOCK_SIZE_MAX);
	}

	// Calculate the maximum amount output that a single output buffer
	// may need to hold. This is the same as the maximum total size of
	// a Block.
	*outbuf_size_max = lzma_block_buffer_bound64(*block_size);
	if (*outbuf_size_max == 0)
		return LZMA_MEM_ERROR;

	return LZMA_OK;
}