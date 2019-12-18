#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct _7zip {scalar_t__ temp_offset; scalar_t__ wbuff_remaining; unsigned char* wbuff; int /*<<< orphan*/  temp_fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int flush_wbuff (struct archive_write*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int
copy_out(struct archive_write *a, uint64_t offset, uint64_t length)
{
	struct _7zip *zip;
	int r;

	zip = (struct _7zip *)a->format_data;
	if (zip->temp_offset > 0 &&
	    lseek(zip->temp_fd, offset, SEEK_SET) < 0) {
		archive_set_error(&(a->archive), errno, "lseek failed");
		return (ARCHIVE_FATAL);
	}
	while (length) {
		size_t rsize;
		ssize_t rs;
		unsigned char *wb;

		if (length > zip->wbuff_remaining)
			rsize = zip->wbuff_remaining;
		else
			rsize = (size_t)length;
		wb = zip->wbuff + (sizeof(zip->wbuff) - zip->wbuff_remaining);
		rs = read(zip->temp_fd, wb, rsize);
		if (rs < 0) {
			archive_set_error(&(a->archive), errno,
			    "Can't read temporary file(%jd)",
			    (intmax_t)rs);
			return (ARCHIVE_FATAL);
		}
		if (rs == 0) {
			archive_set_error(&(a->archive), 0,
			    "Truncated 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		zip->wbuff_remaining -= rs;
		length -= rs;
		if (zip->wbuff_remaining == 0) {
			r = flush_wbuff(a);
			if (r != ARCHIVE_OK)
				return (r);
		}
	}
	return (ARCHIVE_OK);
}