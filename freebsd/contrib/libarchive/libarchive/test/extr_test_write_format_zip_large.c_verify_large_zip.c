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
struct fileblocks {int dummy; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open1 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_set_callback_data (struct archive*,struct fileblocks*) ; 
 int /*<<< orphan*/  archive_read_set_open_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_set_read_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_seek_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_skip_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_read ; 
 int /*<<< orphan*/  memory_read_open ; 
 int /*<<< orphan*/  memory_read_seek ; 
 int /*<<< orphan*/  memory_read_skip ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__* test_sizes ; 

__attribute__((used)) static void
verify_large_zip(struct archive *a, struct fileblocks *fileblocks)
{
	char namebuff[64];
	struct archive_entry *ae;
	int i;

	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_options(a, "zip:ignorecrc32"));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_open_callback(a, memory_read_open));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_read_callback(a, memory_read));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_skip_callback(a, memory_read_skip));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_seek_callback(a, memory_read_seek));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_callback_data(a, fileblocks));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open1(a));

	/*
	 * Read entries back.
	 */
	for (i = 0; test_sizes[i] > 0; i++) {
		assertEqualIntA(a, ARCHIVE_OK,
		    archive_read_next_header(a, &ae));
		sprintf(namebuff, "file_%d", i);
		assertEqualString(namebuff, archive_entry_pathname(ae));
		assertEqualInt(test_sizes[i], archive_entry_size(ae));
	}
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assertEqualString("lastfile", archive_entry_pathname(ae));

	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
}