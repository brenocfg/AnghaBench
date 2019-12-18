#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  worker_thread ;
typedef  scalar_t__ uint64_t ;
struct TYPE_19__ {scalar_t__ check; scalar_t__ version; } ;
struct TYPE_16__ {int threads_max; size_t block_size; int /*<<< orphan*/  progress_out; scalar_t__ progress_in; scalar_t__ header_pos; int /*<<< orphan*/  header; TYPE_8__ stream_flags; int /*<<< orphan*/ * index; TYPE_13__* filters; int /*<<< orphan*/  timeout; int /*<<< orphan*/  outq; int /*<<< orphan*/ * threads; int /*<<< orphan*/ * threads_free; scalar_t__ threads_initialized; int /*<<< orphan*/ * thr; int /*<<< orphan*/  thread_error; int /*<<< orphan*/  sequence; int /*<<< orphan*/  index_encoder; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ lzma_stream_coder ;
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_options_easy ;
struct TYPE_17__ {int /*<<< orphan*/ * get_progress; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; TYPE_1__* coder; } ;
typedef  TYPE_2__ lzma_next_coder ;
struct TYPE_18__ {int threads; scalar_t__ check; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ lzma_mt ;
typedef  int /*<<< orphan*/  lzma_filter ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_15__ {scalar_t__ id; TYPE_1__* options; } ;

/* Variables and functions */
 unsigned int LZMA_CHECK_ID_MAX ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  LZMA_STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  LZMA_UNSUPPORTED_CHECK ; 
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  SEQ_STREAM_HEADER ; 
 scalar_t__ SIZE_MAX ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_options (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  get_progress ; 
 void* lzma_alloc (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_check_is_supported (scalar_t__) ; 
 int /*<<< orphan*/  lzma_filters_copy (int /*<<< orphan*/  const*,TYPE_13__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * lzma_index_init (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_3__ const*),TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_outq_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 scalar_t__ lzma_raw_encoder_memusage (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_stream_header_encode (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mythread_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mythread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mythread_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_encode_mt ; 
 int /*<<< orphan*/  stream_encoder_mt_end ; 
 int /*<<< orphan*/  threads_end (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  threads_stop (TYPE_1__*,int) ; 

__attribute__((used)) static lzma_ret
stream_encoder_mt_init(lzma_next_coder *next, const lzma_allocator *allocator,
		const lzma_mt *options)
{
	lzma_next_coder_init(&stream_encoder_mt_init, next, allocator);

	// Get the filter chain.
	lzma_options_easy easy;
	const lzma_filter *filters;
	uint64_t block_size;
	uint64_t outbuf_size_max;
	return_if_error(get_options(options, &easy, &filters,
			&block_size, &outbuf_size_max));

#if SIZE_MAX < UINT64_MAX
	if (block_size > SIZE_MAX)
		return LZMA_MEM_ERROR;
#endif

	// Validate the filter chain so that we can give an error in this
	// function instead of delaying it to the first call to lzma_code().
	// The memory usage calculation verifies the filter chain as
	// a side effect so we take advatange of that.
	if (lzma_raw_encoder_memusage(filters) == UINT64_MAX)
		return LZMA_OPTIONS_ERROR;

	// Validate the Check ID.
	if ((unsigned int)(options->check) > LZMA_CHECK_ID_MAX)
		return LZMA_PROG_ERROR;

	if (!lzma_check_is_supported(options->check))
		return LZMA_UNSUPPORTED_CHECK;

	// Allocate and initialize the base structure if needed.
	lzma_stream_coder *coder = next->coder;
	if (coder == NULL) {
		coder = lzma_alloc(sizeof(lzma_stream_coder), allocator);
		if (coder == NULL)
			return LZMA_MEM_ERROR;

		next->coder = coder;

		// For the mutex and condition variable initializations
		// the error handling has to be done here because
		// stream_encoder_mt_end() doesn't know if they have
		// already been initialized or not.
		if (mythread_mutex_init(&coder->mutex)) {
			lzma_free(coder, allocator);
			next->coder = NULL;
			return LZMA_MEM_ERROR;
		}

		if (mythread_cond_init(&coder->cond)) {
			mythread_mutex_destroy(&coder->mutex);
			lzma_free(coder, allocator);
			next->coder = NULL;
			return LZMA_MEM_ERROR;
		}

		next->code = &stream_encode_mt;
		next->end = &stream_encoder_mt_end;
		next->get_progress = &get_progress;
// 		next->update = &stream_encoder_mt_update;

		coder->filters[0].id = LZMA_VLI_UNKNOWN;
		coder->index_encoder = LZMA_NEXT_CODER_INIT;
		coder->index = NULL;
		memzero(&coder->outq, sizeof(coder->outq));
		coder->threads = NULL;
		coder->threads_max = 0;
		coder->threads_initialized = 0;
	}

	// Basic initializations
	coder->sequence = SEQ_STREAM_HEADER;
	coder->block_size = (size_t)(block_size);
	coder->thread_error = LZMA_OK;
	coder->thr = NULL;

	// Allocate the thread-specific base structures.
	assert(options->threads > 0);
	if (coder->threads_max != options->threads) {
		threads_end(coder, allocator);

		coder->threads = NULL;
		coder->threads_max = 0;

		coder->threads_initialized = 0;
		coder->threads_free = NULL;

		coder->threads = lzma_alloc(
				options->threads * sizeof(worker_thread),
				allocator);
		if (coder->threads == NULL)
			return LZMA_MEM_ERROR;

		coder->threads_max = options->threads;
	} else {
		// Reuse the old structures and threads. Tell the running
		// threads to stop and wait until they have stopped.
		threads_stop(coder, true);
	}

	// Output queue
	return_if_error(lzma_outq_init(&coder->outq, allocator,
			outbuf_size_max, options->threads));

	// Timeout
	coder->timeout = options->timeout;

	// Free the old filter chain and copy the new one.
	for (size_t i = 0; coder->filters[i].id != LZMA_VLI_UNKNOWN; ++i)
		lzma_free(coder->filters[i].options, allocator);

	return_if_error(lzma_filters_copy(
			filters, coder->filters, allocator));

	// Index
	lzma_index_end(coder->index, allocator);
	coder->index = lzma_index_init(allocator);
	if (coder->index == NULL)
		return LZMA_MEM_ERROR;

	// Stream Header
	coder->stream_flags.version = 0;
	coder->stream_flags.check = options->check;
	return_if_error(lzma_stream_header_encode(
			&coder->stream_flags, coder->header));

	coder->header_pos = 0;

	// Progress info
	coder->progress_in = 0;
	coder->progress_out = LZMA_STREAM_HEADER_SIZE;

	return LZMA_OK;
}