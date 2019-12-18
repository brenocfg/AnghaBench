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
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_ZIP ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 scalar_t__ archive_errno (struct archive*) ; 
 char* archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char**,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/ * archive_zlib_version () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char**,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,char*) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
verify_info_zip_ux(struct archive *a, int seek_checks)
{
	struct archive_entry *ae;
	char *buff[128];

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("file1", archive_entry_pathname(ae));
	assertEqualInt(1300668680, archive_entry_mtime(ae));
	assertEqualInt(18, archive_entry_size(ae));
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), 0);
	if (seek_checks)
		assertEqualInt(AE_IFREG | 0644, archive_entry_mode(ae));
	failure("zip reader should read Info-ZIP New Unix Extra Field");
	assertEqualInt(1001, archive_entry_uid(ae));
	assertEqualInt(1001, archive_entry_gid(ae));
	if (archive_zlib_version() != NULL) {
		failure("archive_read_data() returns number of bytes read");
		assertEqualInt(18, archive_read_data(a, buff, 19));
		assertEqualMem(buff, "hello\nhello\nhello\n", 18);
	} else {
		assertEqualInt(ARCHIVE_FAILED, archive_read_data(a, buff, 19));
		assertEqualString(archive_error_string(a),
		    "Unsupported ZIP compression method (8: deflation)");
		assert(archive_errno(a) != 0);
	}
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify the number of files read. */
	failure("the archive file has just one file");
	assertEqualInt(1, archive_file_count(a));

	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_ZIP, archive_format(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}