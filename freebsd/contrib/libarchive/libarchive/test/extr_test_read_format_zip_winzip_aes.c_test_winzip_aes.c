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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_ZIP ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int /*<<< orphan*/  archive_entry_is_data_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_is_metadata_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_errno (struct archive*) ; 
 char* archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_add_passphrase (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_set_format_zip (struct archive*) ; 
 int archive_write_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/ * archive_zlib_version () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,char*) ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void
test_winzip_aes(const char *refname, int need_libz)
{
	struct archive_entry *ae;
	struct archive *a;
	char buff[512];

	/* Check if running system has cryptographic functionality. */
	assert((a = archive_write_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_format_zip(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_add_filter_none(a));
	if (ARCHIVE_OK != archive_write_set_options(a,
				"zip:encryption=aes256")) {
		skipping("This system does not have cryptographic liberary");
		archive_write_free(a);
		return;
	}
	archive_write_free(a);


	extract_reference_file(refname);

	/*
	 * Extract a zip file without password.
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, 
               archive_read_open_filename(a, refname, 10240));

	assertEqualIntA(a, ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW,
		archive_read_has_encrypted_entries(a));

	/* Verify encrypted file "README" */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt((AE_IFREG | 0644), archive_entry_mode(ae));
	assertEqualString("README", archive_entry_pathname(ae));
	assertEqualInt(6818, archive_entry_size(ae));
	assertEqualInt(1, archive_entry_is_data_encrypted(ae));
	assertEqualInt(0, archive_entry_is_metadata_encrypted(ae));
	assertEqualIntA(a, 1, archive_read_has_encrypted_entries(a));
	assertEqualInt(ARCHIVE_FAILED, archive_read_data(a, buff, sizeof(buff)));
	assertEqualInt(1, archive_file_count(a));

	/* End of archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify archive format. */
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_ZIP, archive_format(a));

	/* Close the archive. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));


	/*
	 * Extract a zip file with password.
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	/* Pass three passphrases to decrypt a file content. */
	assertEqualIntA(a, ARCHIVE_OK,
		archive_read_add_passphrase(a, "invalid_pass"));
	assertEqualIntA(a, ARCHIVE_OK,
		archive_read_add_passphrase(a, "invalid_phrase"));
	assertEqualIntA(a, ARCHIVE_OK,
		archive_read_add_passphrase(a, "password"));
	assertEqualIntA(a, ARCHIVE_OK, 
		archive_read_open_filename(a, refname, 10240));

	assertEqualIntA(a, ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW,
		archive_read_has_encrypted_entries(a));

	/* Verify encrypted file "README" */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt((AE_IFREG | 0644), archive_entry_mode(ae));
	assertEqualString("README", archive_entry_pathname(ae));
	assertEqualInt(6818, archive_entry_size(ae));
	assertEqualInt(1, archive_entry_is_data_encrypted(ae));
	assertEqualInt(0, archive_entry_is_metadata_encrypted(ae));
	assertEqualIntA(a, 1, archive_read_has_encrypted_entries(a));
	if (!need_libz || archive_zlib_version() != NULL) {
		assertEqualInt(512, archive_read_data(a, buff, sizeof(buff)));
	} else {
		assertEqualInt(ARCHIVE_FAILED, archive_read_data(a, buff, 19));
		assertEqualString(archive_error_string(a),
		    "Unsupported ZIP compression method (deflation)");
		assert(archive_errno(a) != 0);
	}
	
	assertEqualInt(1, archive_file_count(a));

	/* End of archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify archive format. */
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_ZIP, archive_format(a));

	/* Close the archive. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}