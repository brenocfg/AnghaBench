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
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ARCHIVE_ERRNO_FILE_FORMAT ; 
 scalar_t__ ARCHIVE_WARN ; 
 char* __archive_read_ahead (struct archive_read*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_le16dec (char const*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t
zip_get_local_file_header_size(struct archive_read *a, size_t extra)
{
	const char *p;
	ssize_t filename_length, extra_length;

	if ((p = __archive_read_ahead(a, extra + 30, NULL)) == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated ZIP file header");
		return (ARCHIVE_WARN);
	}
	p += extra;

	if (memcmp(p, "PK\003\004", 4) != 0) {
		archive_set_error(&a->archive, -1, "Damaged Zip archive");
		return ARCHIVE_WARN;
	}
	filename_length = archive_le16dec(p + 26);
	extra_length = archive_le16dec(p + 28);

	return (30 + filename_length + extra_length);
}