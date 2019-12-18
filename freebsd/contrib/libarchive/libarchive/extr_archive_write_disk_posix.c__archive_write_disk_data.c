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
struct archive_write_disk {int todo; int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_STATE_DATA ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int TODO_HFS_COMPRESSION ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfs_write_data_block (struct archive_write_disk*,void const*,size_t) ; 
 int /*<<< orphan*/  write_data_block (struct archive_write_disk*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
_archive_write_disk_data(struct archive *_a, const void *buff, size_t size)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_DATA, "archive_write_data");

	if (a->todo & TODO_HFS_COMPRESSION)
		return (hfs_write_data_block(a, buff, size));
	return (write_data_block(a, buff, size));
}