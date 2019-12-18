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
struct archive_write_disk {int skip_file_set; void* skip_file_ino; void* skip_file_dev; int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;
typedef  void* la_int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_ANY ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
archive_write_disk_set_skip_file(struct archive *_a, la_int64_t d, la_int64_t i)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	archive_check_magic(&a->archive, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_ANY, "archive_write_disk_set_skip_file");
	a->skip_file_set = 1;
	a->skip_file_dev = d;
	a->skip_file_ino = i;
	return (ARCHIVE_OK);
}