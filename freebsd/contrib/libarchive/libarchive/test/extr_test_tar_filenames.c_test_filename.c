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
 int ARCHIVE_OK ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 scalar_t__ archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 int archive_write_free (struct archive*) ; 
 scalar_t__ archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_memory (struct archive*,char*,int,size_t*) ; 
 scalar_t__ archive_write_set_bytes_per_block (struct archive*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_write_set_format_pax_restricted (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
test_filename(const char *prefix, int dlen, int flen)
{
	char buff[8192];
	char filename[400];
	char dirname[400];
	struct archive_entry *ae;
	struct archive *a;
	size_t used;
	char *p;
	int i;

	p = filename;
	if (prefix) {
		strcpy(filename, prefix);
		p += strlen(p);
	}
	if (dlen > 0) {
		for (i = 0; i < dlen; i++)
			*p++ = 'a';
		*p++ = '/';
	}
	for (i = 0; i < flen; i++)
		*p++ = 'b';
	*p = '\0';

	strcpy(dirname, filename);

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertA(0 == archive_write_set_format_pax_restricted(a));
	assertA(0 == archive_write_add_filter_none(a));
	assertA(0 == archive_write_set_bytes_per_block(a,0));
	assertA(0 == archive_write_open_memory(a, buff, sizeof(buff), &used));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, filename);
	archive_entry_set_mode(ae, S_IFREG | 0755);
	failure("Pathname %d/%d", dlen, flen);
	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * Write a dir to it (without trailing '/').
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, dirname);
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	failure("Dirname %d/%d", dlen, flen);
	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);

	/* Tar adds a '/' to directory names. */
	strcat(dirname, "/");

	/*
	 * Write a dir to it (with trailing '/').
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, dirname);
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	failure("Dirname %d/%d", dlen, flen);
	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/*
	 * Now, read the data back.
	 */
	assert((a = archive_read_new()) != NULL);
	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_support_filter_all(a));
	assertA(0 == archive_read_open_memory(a, buff, used));

	/* Read the file and check the filename. */
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString(filename, archive_entry_pathname(ae));
	assertEqualInt((S_IFREG | 0755), archive_entry_mode(ae));

	/*
	 * Read the two dirs and check the names.
	 *
	 * Both dirs should read back with the same name, since
	 * tar should add a trailing '/' to any dir that doesn't
	 * already have one.  We only report the first such failure
	 * here.
	 */
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString(dirname, archive_entry_pathname(ae));
	assert((S_IFDIR | 0755) == archive_entry_mode(ae));

	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString(dirname, archive_entry_pathname(ae));
	assert((S_IFDIR | 0755) == archive_entry_mode(ae));

	/* Verify the end of the archive. */
	assert(1 == archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}