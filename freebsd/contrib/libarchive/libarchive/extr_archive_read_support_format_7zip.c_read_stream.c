#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct TYPE_8__ {size_t numFolders; TYPE_5__* folders; } ;
struct TYPE_9__ {TYPE_3__ ci; } ;
struct _7zip {scalar_t__ uncompressed_buffer_bytes_remaining; scalar_t__ pack_stream_inbytes_remaining; scalar_t__ folder_outbytes_remaining; scalar_t__ pack_stream_remaining; size_t folder_index; scalar_t__ pack_stream_bytes_unconsumed; TYPE_4__ si; TYPE_2__* entry; scalar_t__ header_is_being_read; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_10__ {scalar_t__ skipped_bytes; } ;
struct TYPE_7__ {size_t folderIndex; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ extract_pack_stream (struct archive_read*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_uncompressed_data (struct archive_read*,void const**,size_t,size_t) ; 
 int /*<<< orphan*/  read_consume (struct archive_read*) ; 
 scalar_t__ seek_pack (struct archive_read*) ; 
 scalar_t__ setup_decode_folder (struct archive_read*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
read_stream(struct archive_read *a, const void **buff, size_t size,
    size_t minimum)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	uint64_t skip_bytes = 0;
	ssize_t r;

	if (zip->uncompressed_buffer_bytes_remaining == 0) {
		if (zip->pack_stream_inbytes_remaining > 0) {
			r = extract_pack_stream(a, 0);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size, minimum));
		} else if (zip->folder_outbytes_remaining > 0) {
			/* Extract a remaining pack stream. */
			r = extract_pack_stream(a, 0);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size, minimum));
		}
	} else
		return (get_uncompressed_data(a, buff, size, minimum));

	/*
	 * Current pack stream has been consumed.
	 */
	if (zip->pack_stream_remaining == 0) {
		if (zip->header_is_being_read) {
			/* Invalid sequence. This might happen when
			 * reading a malformed archive. */
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 * All current folder's pack streams have been
		 * consumed. Switch to next folder.
		 */
		if (zip->folder_index == 0 &&
		    (zip->si.ci.folders[zip->entry->folderIndex].skipped_bytes
		     || zip->folder_index != zip->entry->folderIndex)) {
			zip->folder_index = zip->entry->folderIndex;
			skip_bytes =
			    zip->si.ci.folders[zip->folder_index].skipped_bytes;
		}

		if (zip->folder_index >= zip->si.ci.numFolders) {
			/*
			 * We have consumed all folders and its pack streams.
			 */
			*buff = NULL;
			return (0);
		}
		r = setup_decode_folder(a,
			&(zip->si.ci.folders[zip->folder_index]), 0);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);

		zip->folder_index++;
	}

	/*
	 * Switch to next pack stream.
	 */
	r = seek_pack(a);
	if (r < 0)
		return (r);

	/* Extract a new pack stream. */
	r = extract_pack_stream(a, 0);
	if (r < 0)
		return (r);

	/*
	 * Skip the bytes we already has skipped in skip_stream().
	 */
	while (skip_bytes) {
		ssize_t skipped;

		if (zip->uncompressed_buffer_bytes_remaining == 0) {
			if (zip->pack_stream_inbytes_remaining > 0) {
				r = extract_pack_stream(a, 0);
				if (r < 0)
					return (r);
			} else if (zip->folder_outbytes_remaining > 0) {
				/* Extract a remaining pack stream. */
				r = extract_pack_stream(a, 0);
				if (r < 0)
					return (r);
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Truncated 7-Zip file body");
				return (ARCHIVE_FATAL);
			}
		}
		skipped = get_uncompressed_data(
			a, buff, (size_t)skip_bytes, 0);
		if (skipped < 0)
			return (skipped);
		skip_bytes -= skipped;
		if (zip->pack_stream_bytes_unconsumed)
			read_consume(a);
	}

	return (get_uncompressed_data(a, buff, size, minimum));
}