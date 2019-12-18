#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ lzma_ret ;
typedef  scalar_t__ lzma_action ;
struct TYPE_13__ {int src_eof; int /*<<< orphan*/  src_name; } ;
typedef  TYPE_1__ file_pair ;
struct TYPE_16__ {int /*<<< orphan*/  u8; } ;
struct TYPE_15__ {int /*<<< orphan*/  u8; } ;
struct TYPE_14__ {scalar_t__ avail_out; int avail_in; int /*<<< orphan*/  next_out; int /*<<< orphan*/  next_in; } ;

/* Variables and functions */
 scalar_t__ FORMAT_XZ ; 
 void* IO_BUFFER_SIZE ; 
 scalar_t__ LZMA_DATA_ERROR ; 
 scalar_t__ LZMA_FINISH ; 
 scalar_t__ LZMA_FULL_BARRIER ; 
 scalar_t__ LZMA_MEMLIMIT_ERROR ; 
 scalar_t__ LZMA_NO_CHECK ; 
 scalar_t__ LZMA_OK ; 
 scalar_t__ LZMA_RUN ; 
 scalar_t__ LZMA_STREAM_END ; 
 scalar_t__ LZMA_SYNC_FLUSH ; 
 scalar_t__ LZMA_UNSUPPORTED_CHECK ; 
 scalar_t__ MODE_COMPRESS ; 
 scalar_t__ MODE_TEST ; 
 int SIZE_MAX ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  V_ERROR ; 
 int /*<<< orphan*/  assert (int const) ; 
 scalar_t__ flush_needed ; 
 int hardware_threads_get () ; 
 TYPE_9__ in_buf ; 
 int /*<<< orphan*/  io_fix_src_pos (TYPE_1__*,int) ; 
 void* io_read (TYPE_1__*,TYPE_9__*,int) ; 
 scalar_t__ io_write (TYPE_1__*,TYPE_3__*,void*) ; 
 scalar_t__ lzma_code (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lzma_memusage (TYPE_2__*) ; 
 int /*<<< orphan*/  message_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_mem_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_progress_update () ; 
 int /*<<< orphan*/  message_strm (scalar_t__) ; 
 int /*<<< orphan*/  message_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int my_min (scalar_t__,void*) ; 
 int /*<<< orphan*/  mytime_set_flush_time () ; 
 scalar_t__* opt_block_list ; 
 scalar_t__ opt_block_size ; 
 scalar_t__ opt_format ; 
 scalar_t__ opt_mode ; 
 scalar_t__ opt_single_stream ; 
 TYPE_3__ out_buf ; 
 int /*<<< orphan*/  split_block (scalar_t__*,scalar_t__*,size_t*) ; 
 TYPE_2__ strm ; 
 int /*<<< orphan*/  user_abort ; 

__attribute__((used)) static bool
coder_normal(file_pair *pair)
{
	// Encoder needs to know when we have given all the input to it.
	// The decoders need to know it too when we are using
	// LZMA_CONCATENATED. We need to check for src_eof here, because
	// the first input chunk has been already read if decompressing,
	// and that may have been the only chunk we will read.
	lzma_action action = pair->src_eof ? LZMA_FINISH : LZMA_RUN;

	lzma_ret ret;

	// Assume that something goes wrong.
	bool success = false;

	// block_remaining indicates how many input bytes to encode before
	// finishing the current .xz Block. The Block size is set with
	// --block-size=SIZE and --block-list. They have an effect only when
	// compressing to the .xz format. If block_remaining == UINT64_MAX,
	// only a single block is created.
	uint64_t block_remaining = UINT64_MAX;

	// next_block_remining for when we are in single-threaded mode and
	// the Block in --block-list is larger than the --block-size=SIZE.
	uint64_t next_block_remaining = 0;

	// Position in opt_block_list. Unused if --block-list wasn't used.
	size_t list_pos = 0;

	// Handle --block-size for single-threaded mode and the first step
	// of --block-list.
	if (opt_mode == MODE_COMPRESS && opt_format == FORMAT_XZ) {
		// --block-size doesn't do anything here in threaded mode,
		// because the threaded encoder will take care of splitting
		// to fixed-sized Blocks.
		if (hardware_threads_get() == 1 && opt_block_size > 0)
			block_remaining = opt_block_size;

		// If --block-list was used, start with the first size.
		//
		// For threaded case, --block-size specifies how big Blocks
		// the encoder needs to be prepared to create at maximum
		// and --block-list will simultaneously cause new Blocks
		// to be started at specified intervals. To keep things
		// logical, the same is done in single-threaded mode. The
		// output is still not identical because in single-threaded
		// mode the size info isn't written into Block Headers.
		if (opt_block_list != NULL) {
			if (block_remaining < opt_block_list[list_pos]) {
				assert(hardware_threads_get() == 1);
				next_block_remaining = opt_block_list[list_pos]
						- block_remaining;
			} else {
				block_remaining = opt_block_list[list_pos];
			}
		}
	}

	strm.next_out = out_buf.u8;
	strm.avail_out = IO_BUFFER_SIZE;

	while (!user_abort) {
		// Fill the input buffer if it is empty and we aren't
		// flushing or finishing.
		if (strm.avail_in == 0 && action == LZMA_RUN) {
			strm.next_in = in_buf.u8;
			strm.avail_in = io_read(pair, &in_buf,
					my_min(block_remaining,
						IO_BUFFER_SIZE));

			if (strm.avail_in == SIZE_MAX)
				break;

			if (pair->src_eof) {
				action = LZMA_FINISH;

			} else if (block_remaining != UINT64_MAX) {
				// Start a new Block after every
				// opt_block_size bytes of input.
				block_remaining -= strm.avail_in;
				if (block_remaining == 0)
					action = LZMA_FULL_BARRIER;
			}

			if (action == LZMA_RUN && flush_needed)
				action = LZMA_SYNC_FLUSH;
		}

		// Let liblzma do the actual work.
		ret = lzma_code(&strm, action);

		// Write out if the output buffer became full.
		if (strm.avail_out == 0) {
			if (opt_mode != MODE_TEST && io_write(pair, &out_buf,
					IO_BUFFER_SIZE - strm.avail_out))
				break;

			strm.next_out = out_buf.u8;
			strm.avail_out = IO_BUFFER_SIZE;
		}

		if (ret == LZMA_STREAM_END && (action == LZMA_SYNC_FLUSH
				|| action == LZMA_FULL_BARRIER)) {
			if (action == LZMA_SYNC_FLUSH) {
				// Flushing completed. Write the pending data
				// out immediatelly so that the reading side
				// can decompress everything compressed so far.
				if (io_write(pair, &out_buf, IO_BUFFER_SIZE
						- strm.avail_out))
					break;

				strm.next_out = out_buf.u8;
				strm.avail_out = IO_BUFFER_SIZE;

				// Set the time of the most recent flushing.
				mytime_set_flush_time();
			} else {
				// Start a new Block after LZMA_FULL_BARRIER.
				if (opt_block_list == NULL) {
					assert(hardware_threads_get() == 1);
					assert(opt_block_size > 0);
					block_remaining = opt_block_size;
				} else {
					split_block(&block_remaining,
							&next_block_remaining,
							&list_pos);
				}
			}

			// Start a new Block after LZMA_FULL_FLUSH or continue
			// the same block after LZMA_SYNC_FLUSH.
			action = LZMA_RUN;

		} else if (ret != LZMA_OK) {
			// Determine if the return value indicates that we
			// won't continue coding.
			const bool stop = ret != LZMA_NO_CHECK
					&& ret != LZMA_UNSUPPORTED_CHECK;

			if (stop) {
				// Write the remaining bytes even if something
				// went wrong, because that way the user gets
				// as much data as possible, which can be good
				// when trying to get at least some useful
				// data out of damaged files.
				if (opt_mode != MODE_TEST && io_write(pair,
						&out_buf, IO_BUFFER_SIZE
							- strm.avail_out))
					break;
			}

			if (ret == LZMA_STREAM_END) {
				if (opt_single_stream) {
					io_fix_src_pos(pair, strm.avail_in);
					success = true;
					break;
				}

				// Check that there is no trailing garbage.
				// This is needed for LZMA_Alone and raw
				// streams.
				if (strm.avail_in == 0 && !pair->src_eof) {
					// Try reading one more byte.
					// Hopefully we don't get any more
					// input, and thus pair->src_eof
					// becomes true.
					strm.avail_in = io_read(
							pair, &in_buf, 1);
					if (strm.avail_in == SIZE_MAX)
						break;

					assert(strm.avail_in == 0
							|| strm.avail_in == 1);
				}

				if (strm.avail_in == 0) {
					assert(pair->src_eof);
					success = true;
					break;
				}

				// We hadn't reached the end of the file.
				ret = LZMA_DATA_ERROR;
				assert(stop);
			}

			// If we get here and stop is true, something went
			// wrong and we print an error. Otherwise it's just
			// a warning and coding can continue.
			if (stop) {
				message_error("%s: %s", pair->src_name,
						message_strm(ret));
			} else {
				message_warning("%s: %s", pair->src_name,
						message_strm(ret));

				// When compressing, all possible errors set
				// stop to true.
				assert(opt_mode != MODE_COMPRESS);
			}

			if (ret == LZMA_MEMLIMIT_ERROR) {
				// Display how much memory it would have
				// actually needed.
				message_mem_needed(V_ERROR,
						lzma_memusage(&strm));
			}

			if (stop)
				break;
		}

		// Show progress information under certain conditions.
		message_progress_update();
	}

	return success;
}