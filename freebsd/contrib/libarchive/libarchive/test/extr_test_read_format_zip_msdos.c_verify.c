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
 int AE_IFDIR ; 
 int AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify(struct archive *a, int streaming) {
	struct archive_entry *ae;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("abc", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG | 0664, archive_entry_mode(ae));

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	if (streaming) {
		/* Streaming reader has no basis for making this a dir */
		assertEqualString("def", archive_entry_pathname(ae));
		assertEqualInt(AE_IFREG | 0664, archive_entry_mode(ae));
	} else {
		/* Since 'def' is a dir, '/' should be added */
		assertEqualString("def/", archive_entry_pathname(ae));
		assertEqualInt(AE_IFDIR | 0775, archive_entry_mode(ae));
	}

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("def/foo", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG | 0664, archive_entry_mode(ae));

	/* Streaming reader can tell this is a dir because it ends in '/' */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("ghi/", archive_entry_pathname(ae));
	assertEqualInt(AE_IFDIR | 0775, archive_entry_mode(ae));

	/* Streaming reader can tell this is a dir because it has xl
	 * extension */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	/* '/' gets added because this is a dir */
	assertEqualString("jkl/", archive_entry_pathname(ae));
	assertEqualInt(AE_IFDIR | 0775, archive_entry_mode(ae));

	/* Streaming reader can tell this is a dir because it ends in
	 * '/' and has xl extension */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("mno/", archive_entry_pathname(ae));
	assertEqualInt(AE_IFDIR | 0775, archive_entry_mode(ae));

	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
}