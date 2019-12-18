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
struct zip {int /*<<< orphan*/  requested_compression; } ;
struct TYPE_2__ {scalar_t__ archive_format; } ;
struct archive_write {TYPE_1__ archive; struct zip* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_FORMAT_ZIP ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_HEADER ; 
 int ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  COMPRESSION_DEFLATE ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int
archive_write_zip_set_compression_deflate(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	int ret = ARCHIVE_FAILED;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
		"archive_write_zip_set_compression_deflate");
	if (a->archive.archive_format != ARCHIVE_FORMAT_ZIP) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		"Can only use archive_write_zip_set_compression_deflate"
		" with zip format");
		ret = ARCHIVE_FATAL;
	} else {
#ifdef HAVE_ZLIB_H
		struct zip *zip = a->format_data;
		zip->requested_compression = COMPRESSION_DEFLATE;
		ret = ARCHIVE_OK;
#else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			"deflate compression not supported");
		ret = ARCHIVE_FAILED;
#endif
	}
	return (ret);
}