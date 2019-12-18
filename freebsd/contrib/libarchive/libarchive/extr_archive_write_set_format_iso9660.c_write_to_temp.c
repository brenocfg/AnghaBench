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

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ write (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

__attribute__((used)) static int
write_to_temp(struct archive_write *a, const void *buff, size_t s)
{
	struct iso9660 *iso9660 = a->format_data;
	ssize_t written;
	const unsigned char *b;

	b = (const unsigned char *)buff;
	while (s) {
		written = write(iso9660->temp_fd, b, s);
		if (written < 0) {
			archive_set_error(&a->archive, errno,
			    "Can't write to temporary file");
			return (ARCHIVE_FATAL);
		}
		s -= written;
		b += written;
	}
	return (ARCHIVE_OK);
}