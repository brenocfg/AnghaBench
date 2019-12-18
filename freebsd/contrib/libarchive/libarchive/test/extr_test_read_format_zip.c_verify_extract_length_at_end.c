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
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int archive_entry_size_is_set (struct archive_entry*) ; 
 scalar_t__ archive_errno (struct archive*) ; 
 char* archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_extract (struct archive*,struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_has_encrypted_entries (struct archive*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/ * archive_zlib_version () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,char*) ; 
 int /*<<< orphan*/  assertFileContents (char*,int,char*) ; 

__attribute__((used)) static void
verify_extract_length_at_end(struct archive *a, int seek_checks)
{
	struct archive_entry *ae;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));

	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), 0);
	assertEqualString("hello.txt", archive_entry_pathname(ae));
	if (seek_checks) {
		assertEqualInt(AE_IFREG | 0644, archive_entry_mode(ae));
		assert(archive_entry_size_is_set(ae));
		assertEqualInt(6, archive_entry_size(ae));
	} else {
		assert(!archive_entry_size_is_set(ae));
		assertEqualInt(0, archive_entry_size(ae));
	}

	if (archive_zlib_version() != NULL) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_extract(a, ae, 0));
		assertFileContents("hello\x0A", 6, "hello.txt");
	} else {
		assertEqualIntA(a, ARCHIVE_FAILED, archive_read_extract(a, ae, 0));
		assertEqualString(archive_error_string(a),
		    "Unsupported ZIP compression method (8: deflation)");
		assert(archive_errno(a) != 0);
	}

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_free(a));
}