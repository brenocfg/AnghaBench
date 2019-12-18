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
typedef  int uint64_t ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct TYPE_2__ {scalar_t__ total_in; unsigned char const* next_in; size_t avail_in; int avail_out; void const* next_out; } ;
struct _7zip {int crc32flg; void const* wbuff; void* encoded_crc32; TYPE_1__ stream; void* precode_crc32; } ;
typedef  size_t ssize_t ;
typedef  enum la_zaction { ____Placeholder_la_zaction } la_zaction ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 size_t ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_Z_FINISH ; 
 int ENCODED_CRC32 ; 
 int PRECODE_CRC32 ; 
 int compression_code (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 void* crc32 (void*,void const*,unsigned int) ; 
 int write_to_temp (struct archive_write*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
compress_out(struct archive_write *a, const void *buff, size_t s,
    enum la_zaction run)
{
	struct _7zip *zip = (struct _7zip *)a->format_data;
	int r;

	if (run == ARCHIVE_Z_FINISH && zip->stream.total_in == 0 && s == 0)
		return (0);

	if ((zip->crc32flg & PRECODE_CRC32) && s)
		zip->precode_crc32 = crc32(zip->precode_crc32, buff,
		    (unsigned)s);
	zip->stream.next_in = (const unsigned char *)buff;
	zip->stream.avail_in = s;
	for (;;) {
		/* Compress file data. */
		r = compression_code(&(a->archive), &(zip->stream), run);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			return (ARCHIVE_FATAL);
		if (zip->stream.avail_out == 0) {
			if (write_to_temp(a, zip->wbuff, sizeof(zip->wbuff))
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			zip->stream.next_out = zip->wbuff;
			zip->stream.avail_out = sizeof(zip->wbuff);
			if (zip->crc32flg & ENCODED_CRC32)
				zip->encoded_crc32 = crc32(zip->encoded_crc32,
				    zip->wbuff, sizeof(zip->wbuff));
			if (run == ARCHIVE_Z_FINISH && r != ARCHIVE_EOF)
				continue;
		}
		if (zip->stream.avail_in == 0)
			break;
	}
	if (run == ARCHIVE_Z_FINISH) {
		uint64_t bytes = sizeof(zip->wbuff) - zip->stream.avail_out;
		if (write_to_temp(a, zip->wbuff, (size_t)bytes) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		if ((zip->crc32flg & ENCODED_CRC32) && bytes)
			zip->encoded_crc32 = crc32(zip->encoded_crc32,
			    zip->wbuff, (unsigned)bytes);
	}

	return (s);
}