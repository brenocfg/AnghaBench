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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_EXTRACT_TIME ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_write_data (struct archive*,char const*,int) ; 
 struct archive* archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_disk_set_options (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileAtimeRecent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileMtime (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assertIsReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failure (char*,...) ; 

__attribute__((used)) static void create_reg_file(struct archive_entry *ae, const char *msg)
{
	static const char data[]="abcdefghijklmnopqrstuvwxyz";
	struct archive *ad;

	/* Write the entry to disk. */
	assert((ad = archive_write_disk_new()) != NULL);
        archive_write_disk_set_options(ad, ARCHIVE_EXTRACT_TIME);
	failure("%s", msg);
	/*
	 * A touchy API design issue: archive_write_data() does (as of
	 * 2.4.12) enforce the entry size as a limit on the data
	 * written to the file.  This was not enforced prior to
	 * 2.4.12.  The change was prompted by the refined
	 * hardlink-restore semantics introduced at that time.  In
	 * short, libarchive needs to know whether a "hardlink entry"
	 * is going to overwrite the contents so that it can know
	 * whether or not to open the file for writing.  This implies
	 * that there is a fundamental semantic difference between an
	 * entry with a zero size and one with a non-zero size in the
	 * case of hardlinks and treating the hardlink case
	 * differently from the regular file case is just asking for
	 * trouble.  So, a zero size must always mean that no data
	 * will be accepted, which is consistent with the file size in
	 * the entry being a maximum size.
	 */
	archive_entry_set_size(ae, sizeof(data));
	archive_entry_set_mtime(ae, 123456789, 0);
	assertEqualIntA(ad, 0, archive_write_header(ad, ae));
	assertEqualInt(sizeof(data), archive_write_data(ad, data, sizeof(data)));
	assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
	assertEqualInt(0, archive_write_free(ad));

	/* Test the entries on disk. */
	assertIsReg(archive_entry_pathname(ae), archive_entry_mode(ae) & 0777);
	assertFileSize(archive_entry_pathname(ae), sizeof(data));
	/* test_write_disk_times has more detailed tests of this area. */
	assertFileMtime(archive_entry_pathname(ae), 123456789, 0);
        failure("No atime given, so atime should get set to current time");
	assertFileAtimeRecent(archive_entry_pathname(ae));
}