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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_ctime_is_set (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_is_set (struct archive_entry*) ; 
 scalar_t__ archive_read_disk_can_descend (struct archive*) ; 
 scalar_t__ archive_read_disk_descend (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,scalar_t__) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static int
metadata_filter(struct archive *a, void *data, struct archive_entry *ae)
{
	(void)data; /* UNUSED */

	failure("CTime should be set");
	assertEqualInt(8, archive_entry_ctime_is_set(ae));
	failure("MTime should be set");
	assertEqualInt(16, archive_entry_mtime_is_set(ae));

	if (archive_entry_mtime(ae) < 886611)
		return (0);
	if (archive_read_disk_can_descend(a)) {
		/* Descend into the current object */
		failure("archive_read_disk_can_descend should work"
			" in metadata filter");
		assertEqualIntA(a, 1, archive_read_disk_can_descend(a));
		failure("archive_read_disk_descend should work"
			" in metadata filter");
		assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_descend(a));
	}
	return (1);
}