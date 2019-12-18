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
typedef  int /*<<< orphan*/  archive ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFDIR ; 
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_MTREE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_memory (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_read_format_mtree2(void)
{
	static char archive[] =
	    "#mtree\n"
	    "d type=dir content=.\n";
	struct archive_entry *ae;
	struct archive *a;

	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_set_options(a, "mtree:checkfs"));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_open_memory(a, archive, sizeof(archive)));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_MTREE);
	assertEqualString(archive_entry_pathname(ae), "d");
	assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_file_count(a));
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}