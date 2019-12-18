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
typedef  int /*<<< orphan*/  uintmax_t ;
struct archive_write_disk {int todo; scalar_t__ filesize; int /*<<< orphan*/  archive; int /*<<< orphan*/  offset; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_DATA ; 
 scalar_t__ ARCHIVE_WARN ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int TODO_HFS_COMPRESSION ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hfs_write_data_block (struct archive_write_disk*,void const*,size_t) ; 
 scalar_t__ write_data_block (struct archive_write_disk*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
_archive_write_disk_data_block(struct archive *_a,
    const void *buff, size_t size, int64_t offset)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	ssize_t r;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_DATA, "archive_write_data_block");

	a->offset = offset;
	if (a->todo & TODO_HFS_COMPRESSION)
		r = hfs_write_data_block(a, buff, size);
	else
		r = write_data_block(a, buff, size);
	if (r < ARCHIVE_OK)
		return (r);
	if ((size_t)r < size) {
		archive_set_error(&a->archive, 0,
		    "Too much data: Truncating file at %ju bytes",
		    (uintmax_t)a->filesize);
		return (ARCHIVE_WARN);
	}
#if ARCHIVE_VERSION_NUMBER < 3999000
	return (ARCHIVE_OK);
#else
	return (size);
#endif
}