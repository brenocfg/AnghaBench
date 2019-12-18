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
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_NONE ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_GNUTAR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_filename (struct archive*,char*,int) ; 
 int archive_read_support_filter_all (struct archive*) ; 
 int archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char*) ; 

__attribute__((used)) static void
test_compat_gtar_1(void)
{
	char name[] = "test_compat_gtar_1.tar";
	struct archive_entry *ae;
	struct archive *a;
	int r;

	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	extract_reference_file(name);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_filename(a, name, 10240));

	/* Read first entry. */
	assertEqualIntA(a, ARCHIVE_OK, r = archive_read_next_header(a, &ae));
	if (r != ARCHIVE_OK) {
		archive_read_free(a);
		return;
	}
	assertEqualString(
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890",
		archive_entry_pathname(ae));
	assertEqualInt(1197179003, archive_entry_mtime(ae));
	assertEqualInt(1000, archive_entry_uid(ae));
	assertEqualString("tim", archive_entry_uname(ae));
	assertEqualInt(1000, archive_entry_gid(ae));
	assertEqualString("tim", archive_entry_gname(ae));
	assertEqualInt(0100644, archive_entry_mode(ae));

	/* Read second entry. */
	assertEqualIntA(a, ARCHIVE_OK, r = archive_read_next_header(a, &ae));
	if (r != ARCHIVE_OK) {
		archive_read_free(a);
		return;
	}
	assertEqualString(
		"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij"
		"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij"
		"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij"
		"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij",
		archive_entry_pathname(ae));
	assertEqualString(
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890",
		archive_entry_symlink(ae));
	assertEqualInt(1197179043, archive_entry_mtime(ae));
	assertEqualInt(1000, archive_entry_uid(ae));
	assertEqualString("tim", archive_entry_uname(ae));
	assertEqualInt(1000, archive_entry_gid(ae));
	assertEqualString("tim", archive_entry_gname(ae));
	assertEqualInt(0120755, archive_entry_mode(ae));

	/* Verify the end-of-archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify that the format detection worked. */
	assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_NONE);
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_TAR_GNUTAR);

	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}