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

/* Variables and functions */
 scalar_t__ AE_IFDIR ; 
 scalar_t__ AE_IFLNK ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_hardlink (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_symlink (struct archive_entry*) ; 
 int archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void verify1(struct archive_entry *ae)
{
	/* A hardlink is not a symlink. */
	assert(archive_entry_filetype(ae) != AE_IFLNK);
	/* Nor is it a directory. */
	assert(archive_entry_filetype(ae) != AE_IFDIR);
	assertEqualInt(archive_entry_mode(ae) & 0777, 0644);
	assertEqualInt(archive_entry_uid(ae), 1000);
	assertEqualInt(archive_entry_gid(ae), 1000);
	assertEqualString(archive_entry_uname(ae), "tim");
	assertEqualString(archive_entry_gname(ae), "tim");
	assertEqualString(archive_entry_pathname(ae), "hardlink");
	assertEqualString(archive_entry_hardlink(ae), "file");
	assert(archive_entry_symlink(ae) == NULL);
	assertEqualInt(archive_entry_mtime(ae), 1184388530);
}