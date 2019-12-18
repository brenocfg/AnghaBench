#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {scalar_t__ st_size; } ;
struct TYPE_15__ {TYPE_1__ src_st; } ;
typedef  TYPE_2__ file_pair ;
typedef  enum coder_init_ret { ____Placeholder_coder_init_ret } coder_init_ret ;
struct TYPE_17__ {int /*<<< orphan*/ * u8; } ;
struct TYPE_16__ {scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;

/* Variables and functions */
 int const CODER_INIT_ERROR ; 
 int const CODER_INIT_NORMAL ; 
 int /*<<< orphan*/  IO_BUFFER_SIZE ; 
 scalar_t__ MODE_COMPRESS ; 
 scalar_t__ MODE_TEST ; 
 scalar_t__ SIZE_MAX ; 
 int coder_init (TYPE_2__*) ; 
 int coder_normal (TYPE_2__*) ; 
 int coder_passthru (TYPE_2__*) ; 
 TYPE_6__ in_buf ; 
 int /*<<< orphan*/  io_close (TYPE_2__*,int) ; 
 int /*<<< orphan*/  io_open_dest (TYPE_2__*) ; 
 TYPE_2__* io_open_src (char const*) ; 
 scalar_t__ io_read (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_filename (char const*) ; 
 int /*<<< orphan*/  message_progress_end (int) ; 
 int /*<<< orphan*/  message_progress_start (TYPE_3__*,scalar_t__ const) ; 
 int /*<<< orphan*/  mytime_set_start_time () ; 
 scalar_t__ opt_mode ; 
 TYPE_3__ strm ; 
 int /*<<< orphan*/  user_abort ; 

extern void
coder_run(const char *filename)
{
	// Set and possibly print the filename for the progress message.
	message_filename(filename);

	// Try to open the input file.
	file_pair *pair = io_open_src(filename);
	if (pair == NULL)
		return;

	// Assume that something goes wrong.
	bool success = false;

	if (opt_mode == MODE_COMPRESS) {
		strm.next_in = NULL;
		strm.avail_in = 0;
	} else {
		// Read the first chunk of input data. This is needed
		// to detect the input file type.
		strm.next_in = in_buf.u8;
		strm.avail_in = io_read(pair, &in_buf, IO_BUFFER_SIZE);
	}

	if (strm.avail_in != SIZE_MAX) {
		// Initialize the coder. This will detect the file format
		// and, in decompression or testing mode, check the memory
		// usage of the first Block too. This way we don't try to
		// open the destination file if we see that coding wouldn't
		// work at all anyway. This also avoids deleting the old
		// "target" file if --force was used.
		const enum coder_init_ret init_ret = coder_init(pair);

		if (init_ret != CODER_INIT_ERROR && !user_abort) {
			// Don't open the destination file when --test
			// is used.
			if (opt_mode == MODE_TEST || !io_open_dest(pair)) {
				// Remember the current time. It is needed
				// for progress indicator and for timed
				// flushing.
				mytime_set_start_time();

				// Initialize the progress indicator.
				const uint64_t in_size
						= pair->src_st.st_size <= 0
						? 0 : pair->src_st.st_size;
				message_progress_start(&strm, in_size);

				// Do the actual coding or passthru.
				if (init_ret == CODER_INIT_NORMAL)
					success = coder_normal(pair);
				else
					success = coder_passthru(pair);

				message_progress_end(success);
			}
		}
	}

	// Close the file pair. It needs to know if coding was successful to
	// know if the source or target file should be unlinked.
	io_close(pair, success);

	return;
}