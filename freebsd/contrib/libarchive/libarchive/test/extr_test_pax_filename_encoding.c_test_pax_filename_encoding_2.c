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
 int /*<<< orphan*/  AE_IFLNK ; 
 int /*<<< orphan*/  AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_WARN ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  archive_entry_copy_gname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_hardlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_uname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_hardlink (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_memory (struct archive*,char*,size_t) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 int /*<<< orphan*/  archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_open_memory (struct archive*,char*,int,size_t*) ; 
 int /*<<< orphan*/  archive_write_set_bytes_per_block (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_format_pax (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void
test_pax_filename_encoding_2(void)
{
	char filename[] = "abc\314\214mno\374xyz";
	struct archive *a;
	struct archive_entry *entry;
	char buff[65536];
	char longname[] = "abc\314\214mno\374xyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    "/abc\314\214mno\374xyz/abcdefghijklmnopqrstuvwxyz"
	    ;
	size_t used;

	/*
	 * We need a starting locale which has invalid sequences.
	 * en_US.UTF-8 seems to be commonly supported.
	 */
	/* If it doesn't exist, just warn and return. */
	if (NULL == setlocale(LC_ALL, "en_US.UTF-8")) {
		skipping("invalid encoding tests require a suitable locale;"
		    " en_US.UTF-8 not available on this system");
		return;
	}

	assert((a = archive_write_new()) != NULL);
	assertEqualIntA(a, 0, archive_write_set_format_pax(a));
	assertEqualIntA(a, 0, archive_write_add_filter_none(a));
	assertEqualIntA(a, 0, archive_write_set_bytes_per_block(a, 0));
	assertEqualInt(0,
	    archive_write_open_memory(a, buff, sizeof(buff), &used));

	assert((entry = archive_entry_new()) != NULL);
	/* Set pathname, gname, uname, hardlink to nonconvertible values. */
	archive_entry_copy_pathname(entry, filename);
	archive_entry_copy_gname(entry, filename);
	archive_entry_copy_uname(entry, filename);
	archive_entry_copy_hardlink(entry, filename);
	archive_entry_set_filetype(entry, AE_IFREG);
	failure("This should generate a warning for nonconvertible names.");
	assertEqualInt(ARCHIVE_WARN, archive_write_header(a, entry));
	archive_entry_free(entry);

	assert((entry = archive_entry_new()) != NULL);
	/* Set path, gname, uname, and symlink to nonconvertible values. */
	archive_entry_copy_pathname(entry, filename);
	archive_entry_copy_gname(entry, filename);
	archive_entry_copy_uname(entry, filename);
	archive_entry_copy_symlink(entry, filename);
	archive_entry_set_filetype(entry, AE_IFLNK);
	failure("This should generate a warning for nonconvertible names.");
	assertEqualInt(ARCHIVE_WARN, archive_write_header(a, entry));
	archive_entry_free(entry);

	assert((entry = archive_entry_new()) != NULL);
	/* Set pathname to a very long nonconvertible value. */
	archive_entry_copy_pathname(entry, longname);
	archive_entry_set_filetype(entry, AE_IFREG);
	failure("This should generate a warning for nonconvertible names.");
	assertEqualInt(ARCHIVE_WARN, archive_write_header(a, entry));
	archive_entry_free(entry);

	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/*
	 * Now read the entries back.
	 */

	assert((a = archive_read_new()) != NULL);
	assertEqualInt(0, archive_read_support_format_tar(a));
	assertEqualInt(0, archive_read_open_memory(a, buff, used));

	assertEqualInt(0, archive_read_next_header(a, &entry));
	assertEqualString(filename, archive_entry_pathname(entry));
	assertEqualString(filename, archive_entry_gname(entry));
	assertEqualString(filename, archive_entry_uname(entry));
	assertEqualString(filename, archive_entry_hardlink(entry));

	assertEqualInt(0, archive_read_next_header(a, &entry));
	assertEqualString(filename, archive_entry_pathname(entry));
	assertEqualString(filename, archive_entry_gname(entry));
	assertEqualString(filename, archive_entry_uname(entry));
	assertEqualString(filename, archive_entry_symlink(entry));

	assertEqualInt(0, archive_read_next_header(a, &entry));
	assertEqualString(longname, archive_entry_pathname(entry));

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}