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
 int AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify(struct archive *a) {
	struct archive_entry *ae;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("a", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG | 0664, archive_entry_mode(ae));
	assertEqualInt(0x5c1558d2, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualInt(0x5c1558db, archive_entry_atime(ae));

	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
}