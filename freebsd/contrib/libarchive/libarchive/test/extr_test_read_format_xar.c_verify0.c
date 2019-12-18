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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 int GID ; 
 char* GNAME ; 
 int UID ; 
 char* UNAME ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_hardlink (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_symlink (struct archive_entry*) ; 
 int archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void verify0(struct archive *a, struct archive_entry *ae)
{
	const void *p;
	size_t size;
	int64_t offset;

	assert(archive_entry_filetype(ae) == AE_IFREG);
	assertEqualInt(archive_entry_mode(ae) & 0777, 0644);
	assertEqualInt(archive_entry_uid(ae), UID);
	assertEqualInt(archive_entry_gid(ae), GID);
	assertEqualString(archive_entry_uname(ae), UNAME);
	assertEqualString(archive_entry_gname(ae), GNAME);
	assertEqualString(archive_entry_pathname(ae), "f1");
	assert(archive_entry_hardlink(ae) == NULL);
	assert(archive_entry_symlink(ae) == NULL);
	assertEqualInt(archive_entry_mtime(ae), 86401);
	assertEqualInt(archive_entry_size(ae), 16);
	assertEqualInt(archive_read_data_block(a, &p, &size, &offset), 0);
	assertEqualInt((int)size, 16);
	assertEqualInt((int)offset, 0);
	assertEqualMem(p, "hellohellohello\n", 16);
}