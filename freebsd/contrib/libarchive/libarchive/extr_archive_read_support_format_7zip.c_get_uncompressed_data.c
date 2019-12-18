#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct _7zip {scalar_t__ codec; unsigned long codec2; size_t uncompressed_buffer_bytes_remaining; void* uncompressed_buffer_pointer; scalar_t__ pack_stream_bytes_unconsumed; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ _7Z_COPY ; 
 void* __archive_read_ahead (struct archive_read*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ extract_pack_stream (struct archive_read*,size_t) ; 

__attribute__((used)) static ssize_t
get_uncompressed_data(struct archive_read *a, const void **buff, size_t size,
    size_t minimum)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	ssize_t bytes_avail;

	if (zip->codec == _7Z_COPY && zip->codec2 == (unsigned long)-1) {
		/* Copy mode. */

		*buff = __archive_read_ahead(a, minimum, &bytes_avail);
		if (bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated 7-Zip file data");
			return (ARCHIVE_FATAL);
		}
		if ((size_t)bytes_avail >
		    zip->uncompressed_buffer_bytes_remaining)
			bytes_avail = (ssize_t)
			    zip->uncompressed_buffer_bytes_remaining;
		if ((size_t)bytes_avail > size)
			bytes_avail = (ssize_t)size;

		zip->pack_stream_bytes_unconsumed = bytes_avail;
	} else if (zip->uncompressed_buffer_pointer == NULL) {
		/* Decompression has failed. */
		archive_set_error(&(a->archive),
		    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");
		return (ARCHIVE_FATAL);
	} else {
		/* Packed mode. */
		if (minimum > zip->uncompressed_buffer_bytes_remaining) {
			/*
			 * If remaining uncompressed data size is less than
			 * the minimum size, fill the buffer up to the
			 * minimum size.
			 */
			if (extract_pack_stream(a, minimum) < 0)
				return (ARCHIVE_FATAL);
		}
		if (size > zip->uncompressed_buffer_bytes_remaining)
			bytes_avail = (ssize_t)
			    zip->uncompressed_buffer_bytes_remaining;
		else
			bytes_avail = (ssize_t)size;
		*buff = zip->uncompressed_buffer_pointer;
		zip->uncompressed_buffer_pointer += bytes_avail;
	}
	zip->uncompressed_buffer_bytes_remaining -= bytes_avail;
	return (bytes_avail);
}