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
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct _7zip {int temp_fd; scalar_t__ temp_offset; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int __archive_mktemp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ write (int,unsigned char const*,size_t) ; 

__attribute__((used)) static int
write_to_temp(struct archive_write *a, const void *buff, size_t s)
{
	struct _7zip *zip;
	const unsigned char *p;
	ssize_t ws;

	zip = (struct _7zip *)a->format_data;

	/*
	 * Open a temporary file.
	 */
	if (zip->temp_fd == -1) {
		zip->temp_offset = 0;
		zip->temp_fd = __archive_mktemp(NULL);
		if (zip->temp_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't create temporary file");
			return (ARCHIVE_FATAL);
		}
	}

	p = (const unsigned char *)buff;
	while (s) {
		ws = write(zip->temp_fd, p, s);
		if (ws < 0) {
			archive_set_error(&(a->archive), errno,
			    "fwrite function failed");
			return (ARCHIVE_FATAL);
		}
		s -= ws;
		p += ws;
		zip->temp_offset += ws;
	}
	return (ARCHIVE_OK);
}