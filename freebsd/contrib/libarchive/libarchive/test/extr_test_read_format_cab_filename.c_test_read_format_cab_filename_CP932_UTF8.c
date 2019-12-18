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
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_CAB ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int /*<<< orphan*/  LC_ALL ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int) ; 
 int archive_read_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualUTF8String (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void
test_read_format_cab_filename_CP932_UTF8(const char *refname)
{
	struct archive *a;
	struct archive_entry *ae;

	/*
	 * Read CAB filename in en_US.UTF-8 with "hdrcharset=CP932" option.
	 */
	if (NULL == setlocale(LC_ALL, "en_US.UTF-8")) {
		skipping("en_US.UTF-8 locale not available on this system.");
		return;
	}

	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	if (ARCHIVE_OK != archive_read_set_options(a, "hdrcharset=CP932")) {
		skipping("This system cannot convert character-set"
		    " from CP932 to UTF-8.");
		goto cleanup;
	}
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_open_filename(a, refname, 10240));

	/* Verify regular file. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
#if defined(__APPLE__)
	/* Compare NFD string. */
	assertEqualUTF8String(
	    "\xe8\xa1\xa8\xe3\x81\x9f\xe3\x82\x99\xe3\x82\x88\x2f"
	    "\xe6\xbc\xa2\xe5\xad\x97\x2e\x74\x78\x74",
	    archive_entry_pathname(ae));
	assertEqualInt(5, archive_entry_size(ae));
#else
	/* Compare NFC string. */
	assertEqualUTF8String(
	    "\xe8\xa1\xa8\xe3\x81\xa0\xe3\x82\x88\x2f"
	    "\xe6\xbc\xa2\xe5\xad\x97\x2e\x74\x78\x74",
	    archive_entry_pathname(ae));
	assertEqualInt(5, archive_entry_size(ae));
#endif
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify regular file. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
#if defined(__APPLE__)
	/* Compare NFD string. */
	assertEqualUTF8String(
	    "\xe8\xa1\xa8\xe3\x81\x9f\xe3\x82\x99\xe3\x82\x88\x2f"
	    "\xe4\xb8\x80\xe8\xa6\xa7\xe8\xa1\xa8\x2e\x74\x78\x74",
	    archive_entry_pathname(ae));
#else
	/* Compare NFC string. */
	assertEqualUTF8String(
	    "\xe8\xa1\xa8\xe3\x81\xa0\xe3\x82\x88\x2f"
	    "\xe4\xb8\x80\xe8\xa6\xa7\xe8\xa1\xa8\x2e\x74\x78\x74",
	    archive_entry_pathname(ae));
#endif
	assertEqualInt(5, archive_entry_size(ae));
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);


	/* End of archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify archive format. */
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_CAB, archive_format(a));

	/* Close the archive. */
cleanup:
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}