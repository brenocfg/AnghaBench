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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int AE_IFDIR ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_ZIP ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int archive_entry_size_is_set (struct archive_entry*) ; 
 scalar_t__ archive_errno (struct archive*) ; 
 char* archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 char* archive_format_name (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char**,int) ; 
 int /*<<< orphan*/  archive_read_data_block (struct archive*,void const**,size_t*,int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  memset (char**,char,int) ; 

__attribute__((used)) static void
verify_basic(struct archive *a, int seek_checks)
{
	struct archive_entry *ae;
	char *buff[128];
	const void *pv;
	size_t s;
	int64_t o;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("ZIP 1.0 (uncompressed)", archive_format_name(a));
	assertEqualString("dir/", archive_entry_pathname(ae));
	assertEqualInt(1179604249, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_size(ae));
	if (seek_checks)
		assertEqualInt(AE_IFDIR | 0755, archive_entry_mode(ae));
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), 0);
	assertEqualIntA(a, ARCHIVE_EOF,
	    archive_read_data_block(a, &pv, &s, &o));
	assertEqualInt((int)s, 0);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("ZIP 2.0 (deflation)", archive_format_name(a));
	assertEqualString("file1", archive_entry_pathname(ae));
	assertEqualInt(1179604289, archive_entry_mtime(ae));
	if (seek_checks)
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assertEqualInt(18, archive_entry_size(ae));
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), 0);
	failure("archive_read_data() returns number of bytes read");
	if (archive_zlib_version() != NULL) {
		assertEqualInt(18, archive_read_data(a, buff, 19));
		assertEqualMem(buff, "hello\nhello\nhello\n", 18);
	} else {
		assertEqualInt(ARCHIVE_FAILED, archive_read_data(a, buff, 19));
		assertEqualString(archive_error_string(a),
		    "Unsupported ZIP compression method (8: deflation)");
		assert(archive_errno(a) != 0);
	}

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("ZIP 2.0 (deflation)", archive_format_name(a));
	assertEqualString("file2", archive_entry_pathname(ae));
	assertEqualInt(1179605932, archive_entry_mtime(ae));
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), 0);
	if (seek_checks) {
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	}
	assert(archive_entry_size_is_set(ae));
	assertEqualInt(18, archive_entry_size(ae));
	if (archive_zlib_version() != NULL) {
		failure("file2 has a bad CRC, so read should fail and not change buff");
		memset(buff, 'a', 19);
		assertEqualInt(ARCHIVE_WARN, archive_read_data(a, buff, 19));
		assertEqualMem(buff, "aaaaaaaaaaaaaaaaaaa", 19);
	} else {
		assertEqualInt(ARCHIVE_FAILED, archive_read_data(a, buff, 19));
		assertEqualString(archive_error_string(a),
		    "Unsupported ZIP compression method (8: deflation)");
		assert(archive_errno(a) != 0);
	}
	assertEqualInt(ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualString("ZIP 2.0 (deflation)", archive_format_name(a));
	/* Verify the number of files read. */
	failure("the archive file has three files");
	assertEqualInt(3, archive_file_count(a));
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_ZIP, archive_format(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}