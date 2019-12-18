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
 int /*<<< orphan*/  ARCHIVE_FILTER_LZ4 ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_USTAR ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 int archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 char const* archive_filter_name (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_filename (struct archive*,char const*,int) ; 
 int archive_read_support_filter_all (struct archive*) ; 
 int archive_read_support_filter_lz4 (struct archive*) ; 
 int archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualString (char const*,char*) ; 
 int /*<<< orphan*/  copy_reference_file (char const*) ; 
 int /*<<< orphan*/  failure (char*,int,char const*,char const*) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void
verify(const char *name, const char *n[])
{
	struct archive_entry *ae;
	struct archive *a;
	int i,r;

	assert((a = archive_read_new()) != NULL);
	r = archive_read_support_filter_lz4(a);
	if (r == ARCHIVE_WARN) {
		skipping("lz4 reading not fully supported on this platform");
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}
	assertEqualIntA(a, ARCHIVE_OK, r);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	copy_reference_file(name);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_filename(a, name, 200));

	/* Read entries, match up names with list above. */
	for (i = 0; n[i] != NULL; ++i) {
		failure("Could not read file %d (%s) from %s", i, n[i], name);
		assertEqualIntA(a, ARCHIVE_OK,
		    archive_read_next_header(a, &ae));
		if (r != ARCHIVE_OK) {
			archive_read_free(a);
			return;
		}
		assertEqualString(n[i], archive_entry_pathname(ae));
	}

	/* Verify the end-of-archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify that the format detection worked. */
	assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_LZ4);
	assertEqualString(archive_filter_name(a, 0), "lz4");
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_TAR_USTAR);

	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}