#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/ * idx; int /*<<< orphan*/  stream_padding; } ;
typedef  TYPE_2__ xz_file_info ;
typedef  scalar_t__ uint64_t ;
typedef  int off_t ;
typedef  scalar_t__ lzma_vli ;
struct TYPE_23__ {scalar_t__ version; scalar_t__ backward_size; } ;
typedef  TYPE_3__ lzma_stream_flags ;
struct TYPE_24__ {int avail_in; int /*<<< orphan*/  next_in; } ;
typedef  TYPE_4__ lzma_stream ;
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_index ;
struct TYPE_25__ {scalar_t__* u32; int /*<<< orphan*/  u8; } ;
typedef  TYPE_5__ io_buf ;
struct TYPE_21__ {int st_size; } ;
struct TYPE_26__ {int /*<<< orphan*/  src_name; TYPE_1__ src_st; } ;
typedef  TYPE_6__ file_pair ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_SIZE ; 
 int /*<<< orphan*/  LZMA_BUF_ERROR ; 
 int /*<<< orphan*/  LZMA_DATA_ERROR ; 
 int /*<<< orphan*/  LZMA_MEMLIMIT_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_STREAM_END ; 
 int LZMA_STREAM_HEADER_SIZE ; 
 TYPE_4__ LZMA_STREAM_INIT ; 
 int /*<<< orphan*/  MODE_LIST ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  V_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ hardware_memlimit_get (int /*<<< orphan*/ ) ; 
 scalar_t__ io_pread (TYPE_6__*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  lzma_code (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_end (TYPE_4__*) ; 
 int /*<<< orphan*/  lzma_index_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_decoder (TYPE_4__*,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_index_memused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_stream_flags (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lzma_index_stream_padding (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lzma_index_total_size (int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_memusage (TYPE_4__*) ; 
 int /*<<< orphan*/  lzma_stream_flags_compare (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  lzma_stream_footer_decode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_stream_header_decode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_bug () ; 
 int /*<<< orphan*/  message_error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  message_mem_needed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  message_strm (int /*<<< orphan*/ ) ; 
 int my_min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
parse_indexes(xz_file_info *xfi, file_pair *pair)
{
	if (pair->src_st.st_size <= 0) {
		message_error(_("%s: File is empty"), pair->src_name);
		return true;
	}

	if (pair->src_st.st_size < 2 * LZMA_STREAM_HEADER_SIZE) {
		message_error(_("%s: Too small to be a valid .xz file"),
				pair->src_name);
		return true;
	}

	io_buf buf;
	lzma_stream_flags header_flags;
	lzma_stream_flags footer_flags;
	lzma_ret ret;

	// lzma_stream for the Index decoder
	lzma_stream strm = LZMA_STREAM_INIT;

	// All Indexes decoded so far
	lzma_index *combined_index = NULL;

	// The Index currently being decoded
	lzma_index *this_index = NULL;

	// Current position in the file. We parse the file backwards so
	// initialize it to point to the end of the file.
	off_t pos = pair->src_st.st_size;

	// Each loop iteration decodes one Index.
	do {
		// Check that there is enough data left to contain at least
		// the Stream Header and Stream Footer. This check cannot
		// fail in the first pass of this loop.
		if (pos < 2 * LZMA_STREAM_HEADER_SIZE) {
			message_error("%s: %s", pair->src_name,
					message_strm(LZMA_DATA_ERROR));
			goto error;
		}

		pos -= LZMA_STREAM_HEADER_SIZE;
		lzma_vli stream_padding = 0;

		// Locate the Stream Footer. There may be Stream Padding which
		// we must skip when reading backwards.
		while (true) {
			if (pos < LZMA_STREAM_HEADER_SIZE) {
				message_error("%s: %s", pair->src_name,
						message_strm(
							LZMA_DATA_ERROR));
				goto error;
			}

			if (io_pread(pair, &buf,
					LZMA_STREAM_HEADER_SIZE, pos))
				goto error;

			// Stream Padding is always a multiple of four bytes.
			int i = 2;
			if (buf.u32[i] != 0)
				break;

			// To avoid calling io_pread() for every four bytes
			// of Stream Padding, take advantage that we read
			// 12 bytes (LZMA_STREAM_HEADER_SIZE) already and
			// check them too before calling io_pread() again.
			do {
				stream_padding += 4;
				pos -= 4;
				--i;
			} while (i >= 0 && buf.u32[i] == 0);
		}

		// Decode the Stream Footer.
		ret = lzma_stream_footer_decode(&footer_flags, buf.u8);
		if (ret != LZMA_OK) {
			message_error("%s: %s", pair->src_name,
					message_strm(ret));
			goto error;
		}

		// Check that the Stream Footer doesn't specify something
		// that we don't support. This can only happen if the xz
		// version is older than liblzma and liblzma supports
		// something new.
		//
		// It is enough to check Stream Footer. Stream Header must
		// match when it is compared against Stream Footer with
		// lzma_stream_flags_compare().
		if (footer_flags.version != 0) {
			message_error("%s: %s", pair->src_name,
					message_strm(LZMA_OPTIONS_ERROR));
			goto error;
		}

		// Check that the size of the Index field looks sane.
		lzma_vli index_size = footer_flags.backward_size;
		if ((lzma_vli)(pos) < index_size + LZMA_STREAM_HEADER_SIZE) {
			message_error("%s: %s", pair->src_name,
					message_strm(LZMA_DATA_ERROR));
			goto error;
		}

		// Set pos to the beginning of the Index.
		pos -= index_size;

		// See how much memory we can use for decoding this Index.
		uint64_t memlimit = hardware_memlimit_get(MODE_LIST);
		uint64_t memused = 0;
		if (combined_index != NULL) {
			memused = lzma_index_memused(combined_index);
			if (memused > memlimit)
				message_bug();

			memlimit -= memused;
		}

		// Decode the Index.
		ret = lzma_index_decoder(&strm, &this_index, memlimit);
		if (ret != LZMA_OK) {
			message_error("%s: %s", pair->src_name,
					message_strm(ret));
			goto error;
		}

		do {
			// Don't give the decoder more input than the
			// Index size.
			strm.avail_in = my_min(IO_BUFFER_SIZE, index_size);
			if (io_pread(pair, &buf, strm.avail_in, pos))
				goto error;

			pos += strm.avail_in;
			index_size -= strm.avail_in;

			strm.next_in = buf.u8;
			ret = lzma_code(&strm, LZMA_RUN);

		} while (ret == LZMA_OK);

		// If the decoding seems to be successful, check also that
		// the Index decoder consumed as much input as indicated
		// by the Backward Size field.
		if (ret == LZMA_STREAM_END)
			if (index_size != 0 || strm.avail_in != 0)
				ret = LZMA_DATA_ERROR;

		if (ret != LZMA_STREAM_END) {
			// LZMA_BUFFER_ERROR means that the Index decoder
			// would have liked more input than what the Index
			// size should be according to Stream Footer.
			// The message for LZMA_DATA_ERROR makes more
			// sense in that case.
			if (ret == LZMA_BUF_ERROR)
				ret = LZMA_DATA_ERROR;

			message_error("%s: %s", pair->src_name,
					message_strm(ret));

			// If the error was too low memory usage limit,
			// show also how much memory would have been needed.
			if (ret == LZMA_MEMLIMIT_ERROR) {
				uint64_t needed = lzma_memusage(&strm);
				if (UINT64_MAX - needed < memused)
					needed = UINT64_MAX;
				else
					needed += memused;

				message_mem_needed(V_ERROR, needed);
			}

			goto error;
		}

		// Decode the Stream Header and check that its Stream Flags
		// match the Stream Footer.
		pos -= footer_flags.backward_size + LZMA_STREAM_HEADER_SIZE;
		if ((lzma_vli)(pos) < lzma_index_total_size(this_index)) {
			message_error("%s: %s", pair->src_name,
					message_strm(LZMA_DATA_ERROR));
			goto error;
		}

		pos -= lzma_index_total_size(this_index);
		if (io_pread(pair, &buf, LZMA_STREAM_HEADER_SIZE, pos))
			goto error;

		ret = lzma_stream_header_decode(&header_flags, buf.u8);
		if (ret != LZMA_OK) {
			message_error("%s: %s", pair->src_name,
					message_strm(ret));
			goto error;
		}

		ret = lzma_stream_flags_compare(&header_flags, &footer_flags);
		if (ret != LZMA_OK) {
			message_error("%s: %s", pair->src_name,
					message_strm(ret));
			goto error;
		}

		// Store the decoded Stream Flags into this_index. This is
		// needed so that we can print which Check is used in each
		// Stream.
		ret = lzma_index_stream_flags(this_index, &footer_flags);
		if (ret != LZMA_OK)
			message_bug();

		// Store also the size of the Stream Padding field. It is
		// needed to show the offsets of the Streams correctly.
		ret = lzma_index_stream_padding(this_index, stream_padding);
		if (ret != LZMA_OK)
			message_bug();

		if (combined_index != NULL) {
			// Append the earlier decoded Indexes
			// after this_index.
			ret = lzma_index_cat(
					this_index, combined_index, NULL);
			if (ret != LZMA_OK) {
				message_error("%s: %s", pair->src_name,
						message_strm(ret));
				goto error;
			}
		}

		combined_index = this_index;
		this_index = NULL;

		xfi->stream_padding += stream_padding;

	} while (pos > 0);

	lzma_end(&strm);

	// All OK. Make combined_index available to the caller.
	xfi->idx = combined_index;
	return false;

error:
	// Something went wrong, free the allocated memory.
	lzma_end(&strm);
	lzma_index_end(combined_index, NULL);
	lzma_index_end(this_index, NULL);
	return true;
}