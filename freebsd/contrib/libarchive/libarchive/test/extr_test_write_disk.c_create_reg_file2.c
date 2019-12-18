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
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int const) ; 
 int /*<<< orphan*/  archive_write_data_block (struct archive*,char*,int,int) ; 
 struct archive* archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileContents (char*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assertIsReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failure (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int const) ; 

__attribute__((used)) static void create_reg_file2(struct archive_entry *ae, const char *msg)
{
	const int datasize = 100000;
	char *data;
	struct archive *ad;
	int i;

	data = malloc(datasize);
	for (i = 0; i < datasize; i++)
		data[i] = (char)(i % 256);

	/* Write the entry to disk. */
	assert((ad = archive_write_disk_new()) != NULL);
	failure("%s", msg);
	/*
	 * See above for an explanation why this next call
	 * is necessary.
	 */
	archive_entry_set_size(ae, datasize);
	assertEqualIntA(ad, 0, archive_write_header(ad, ae));
	for (i = 0; i < datasize - 999; i += 1000) {
		assertEqualIntA(ad, ARCHIVE_OK,
		    archive_write_data_block(ad, data + i, 1000, i));
	}
	assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
	assertEqualInt(0, archive_write_free(ad));

	/* Test the entries on disk. */
	assertIsReg(archive_entry_pathname(ae), archive_entry_mode(ae) & 0777);
	assertFileSize(archive_entry_pathname(ae), i);
	assertFileContents(data, datasize, archive_entry_pathname(ae));
	free(data);
}