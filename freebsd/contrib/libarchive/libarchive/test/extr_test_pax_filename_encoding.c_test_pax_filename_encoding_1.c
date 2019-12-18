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
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_pax_filename_encoding_1(void)
{
	static const char testname[] = "test_pax_filename_encoding.tar";
	/*
	 * \314\214 is a valid 2-byte UTF-8 sequence.
	 * \374 is invalid in UTF-8.
	 */
	char filename[] = "abc\314\214mno\374xyz";
	struct archive *a;
	struct archive_entry *entry;

	/*
	 * Read an archive that has non-UTF8 pax filenames in it.
	 */
	extract_reference_file(testname);
	a = archive_read_new();
	assertEqualInt(ARCHIVE_OK, archive_read_support_format_tar(a));
	assertEqualInt(ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualInt(ARCHIVE_OK,
	    archive_read_open_filename(a, testname, 10240));
	/*
	 * First entry in this test archive has an invalid UTF-8 sequence
	 * in it, but the header is not marked as hdrcharset=BINARY, so that
	 * requires a warning.
	 */
	failure("Invalid UTF8 in a pax archive pathname should cause a warning");
	assertEqualInt(ARCHIVE_WARN, archive_read_next_header(a, &entry));
	assertEqualString(filename, archive_entry_pathname(entry));
	/*
	 * Second entry is identical except that it does have
	 * hdrcharset=BINARY, so no warning should be generated.
	 */
	failure("A pathname with hdrcharset=BINARY can have invalid UTF8\n"
	    " characters in it without generating a warning");
	assertEqualInt(ARCHIVE_OK, archive_read_next_header(a, &entry));
	assertEqualString(filename, archive_entry_pathname(entry));
	archive_read_free(a);
}