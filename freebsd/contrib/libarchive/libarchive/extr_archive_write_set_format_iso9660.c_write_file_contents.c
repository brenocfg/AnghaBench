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
struct iso9660 {int /*<<< orphan*/  temp_fd; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,scalar_t__) ; 
 size_t wb_remaining (struct archive_write*) ; 

__attribute__((used)) static int
write_file_contents(struct archive_write *a, int64_t offset, int64_t size)
{
	struct iso9660 *iso9660 = a->format_data;
	int r;

	lseek(iso9660->temp_fd, offset, SEEK_SET);

	while (size) {
		size_t rsize;
		ssize_t rs;
		unsigned char *wb;

		wb = wb_buffptr(a);
		rsize = wb_remaining(a);
		if (rsize > (size_t)size)
			rsize = (size_t)size;
		rs = read(iso9660->temp_fd, wb, rsize);
		if (rs <= 0) {
			archive_set_error(&a->archive, errno,
			    "Can't read temporary file(%jd)", (intmax_t)rs);
			return (ARCHIVE_FATAL);
		}
		size -= rs;
		r = wb_consume(a, rs);
		if (r < 0)
			return (r);
	}
	return (ARCHIVE_OK);
}