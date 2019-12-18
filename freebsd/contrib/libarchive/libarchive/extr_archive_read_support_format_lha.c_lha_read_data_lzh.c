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
struct TYPE_5__ {size_t avail_out; int avail_in; scalar_t__ total_in; void* ref_ptr; int /*<<< orphan*/  next_in; scalar_t__ total_out; } ;
struct lha {int decompress_init; scalar_t__ entry_bytes_remaining; int end_of_entry; scalar_t__ entry_unconsumed; size_t entry_offset; int /*<<< orphan*/  entry_crc_calculated; TYPE_2__ strm; int /*<<< orphan*/ * method; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
typedef  scalar_t__ ssize_t ;
typedef  size_t int64_t ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
#define  ARCHIVE_EOF 130 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
#define  ARCHIVE_FAILED 129 
 int ARCHIVE_FATAL ; 
#define  ARCHIVE_OK 128 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  __archive_read_ahead (struct archive_read*,int,scalar_t__*) ; 
 int /*<<< orphan*/  archive_read_format_lha_read_data_skip (struct archive_read*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lha_crc16 (int /*<<< orphan*/ ,void const*,size_t) ; 
 int lha_end_of_entry (struct archive_read*) ; 
 int lzh_decode (TYPE_2__*,int) ; 
 int lzh_decode_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lha_read_data_lzh(struct archive_read *a, const void **buff,
    size_t *size, int64_t *offset)
{
	struct lha *lha = (struct lha *)(a->format->data);
	ssize_t bytes_avail;
	int r;

	/* If we haven't yet read any data, initialize the decompressor. */
	if (!lha->decompress_init) {
		r = lzh_decode_init(&(lha->strm), lha->method);
		switch (r) {
		case ARCHIVE_OK:
			break;
		case ARCHIVE_FAILED:
        		/* Unsupported compression. */
			*buff = NULL;
			*size = 0;
			*offset = 0;
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unsupported lzh compression method -%c%c%c-",
			    lha->method[0], lha->method[1], lha->method[2]);
			/* We know compressed size; just skip it. */
			archive_read_format_lha_read_data_skip(a);
			return (ARCHIVE_WARN);
		default:
			archive_set_error(&a->archive, ENOMEM,
			    "Couldn't allocate memory "
			    "for lzh decompression");
			return (ARCHIVE_FATAL);
		}
		/* We've initialized decompression for this stream. */
		lha->decompress_init = 1;
		lha->strm.avail_out = 0;
		lha->strm.total_out = 0;
	}

	/*
	 * Note: '1' here is a performance optimization.
	 * Recall that the decompression layer returns a count of
	 * available bytes; asking for more than that forces the
	 * decompressor to combine reads by copying data.
	 */
	lha->strm.next_in = __archive_read_ahead(a, 1, &bytes_avail);
	if (bytes_avail <= 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated LHa file body");
		return (ARCHIVE_FATAL);
	}
	if (bytes_avail > lha->entry_bytes_remaining)
		bytes_avail = (ssize_t)lha->entry_bytes_remaining;

	lha->strm.avail_in = (int)bytes_avail;
	lha->strm.total_in = 0;
	lha->strm.avail_out = 0;

	r = lzh_decode(&(lha->strm), bytes_avail == lha->entry_bytes_remaining);
	switch (r) {
	case ARCHIVE_OK:
		break;
	case ARCHIVE_EOF:
		lha->end_of_entry = 1;
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Bad lzh data");
		return (ARCHIVE_FAILED);
	}
	lha->entry_unconsumed = lha->strm.total_in;
	lha->entry_bytes_remaining -= lha->strm.total_in;

	if (lha->strm.avail_out) {
		*offset = lha->entry_offset;
		*size = lha->strm.avail_out;
		*buff = lha->strm.ref_ptr;
		lha->entry_crc_calculated =
		    lha_crc16(lha->entry_crc_calculated, *buff, *size);
		lha->entry_offset += *size;
	} else {
		*offset = lha->entry_offset;
		*size = 0;
		*buff = NULL;
		if (lha->end_of_entry)
			return (lha_end_of_entry(a));
	}
	return (ARCHIVE_OK);
}