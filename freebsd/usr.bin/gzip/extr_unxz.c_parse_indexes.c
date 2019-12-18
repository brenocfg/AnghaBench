#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * idx; int /*<<< orphan*/  stream_padding; } ;
typedef  TYPE_1__ xz_file_info ;
struct stat {int st_size; } ;
typedef  int off_t ;
typedef  scalar_t__ lzma_vli ;
struct TYPE_17__ {scalar_t__ version; scalar_t__ backward_size; } ;
typedef  TYPE_2__ lzma_stream_flags ;
struct TYPE_18__ {int avail_in; int /*<<< orphan*/  next_in; } ;
typedef  TYPE_3__ lzma_stream ;
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_index ;
struct TYPE_19__ {scalar_t__* u32; int /*<<< orphan*/  u8; } ;
typedef  TYPE_4__ io_buf ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_SIZE ; 
 int /*<<< orphan*/  LZMA_BUF_ERROR ; 
 int /*<<< orphan*/  LZMA_DATA_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_STREAM_END ; 
 int LZMA_STREAM_HEADER_SIZE ; 
 TYPE_3__ LZMA_STREAM_INIT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 scalar_t__ io_pread (int,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  lzma_code (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_end (TYPE_3__*) ; 
 int /*<<< orphan*/  lzma_index_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_decoder (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_stream_flags (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lzma_index_stream_padding (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lzma_index_total_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_stream_flags_compare (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lzma_stream_footer_decode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_stream_header_decode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int my_min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
parse_indexes(xz_file_info *xfi, int src_fd)
{
	struct stat st;

	fstat(src_fd, &st);
	if (st.st_size <= 0) {
		return true;
	}

	if (st.st_size < 2 * LZMA_STREAM_HEADER_SIZE) {
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
	off_t pos = st.st_size;

	// Each loop iteration decodes one Index.
	do {
		// Check that there is enough data left to contain at least
		// the Stream Header and Stream Footer. This check cannot
		// fail in the first pass of this loop.
		if (pos < 2 * LZMA_STREAM_HEADER_SIZE) {
			goto error;
		}

		pos -= LZMA_STREAM_HEADER_SIZE;
		lzma_vli stream_padding = 0;

		// Locate the Stream Footer. There may be Stream Padding which
		// we must skip when reading backwards.
		while (true) {
			if (pos < LZMA_STREAM_HEADER_SIZE) {
				goto error;
			}

			if (io_pread(src_fd, &buf,
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
			goto error;
		}

		// Check that the size of the Index field looks sane.
		lzma_vli index_size = footer_flags.backward_size;
		if ((lzma_vli)(pos) < index_size + LZMA_STREAM_HEADER_SIZE) {
			goto error;
		}

		// Set pos to the beginning of the Index.
		pos -= index_size;

		// Decode the Index.
		ret = lzma_index_decoder(&strm, &this_index, UINT64_MAX);
		if (ret != LZMA_OK) {
			goto error;
		}

		do {
			// Don't give the decoder more input than the
			// Index size.
			strm.avail_in = my_min(IO_BUFFER_SIZE, index_size);
			if (io_pread(src_fd, &buf, strm.avail_in, pos))
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

			goto error;
		}

		// Decode the Stream Header and check that its Stream Flags
		// match the Stream Footer.
		pos -= footer_flags.backward_size + LZMA_STREAM_HEADER_SIZE;
		if ((lzma_vli)(pos) < lzma_index_total_size(this_index)) {
			goto error;
		}

		pos -= lzma_index_total_size(this_index);
		if (io_pread(src_fd, &buf, LZMA_STREAM_HEADER_SIZE, pos))
			goto error;

		ret = lzma_stream_header_decode(&header_flags, buf.u8);
		if (ret != LZMA_OK) {
			goto error;
		}

		ret = lzma_stream_flags_compare(&header_flags, &footer_flags);
		if (ret != LZMA_OK) {
			goto error;
		}

		// Store the decoded Stream Flags into this_index. This is
		// needed so that we can print which Check is used in each
		// Stream.
		ret = lzma_index_stream_flags(this_index, &footer_flags);
		if (ret != LZMA_OK)
			goto error;

		// Store also the size of the Stream Padding field. It is
		// needed to show the offsets of the Streams correctly.
		ret = lzma_index_stream_padding(this_index, stream_padding);
		if (ret != LZMA_OK)
			goto error;

		if (combined_index != NULL) {
			// Append the earlier decoded Indexes
			// after this_index.
			ret = lzma_index_cat(
					this_index, combined_index, NULL);
			if (ret != LZMA_OK) {
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