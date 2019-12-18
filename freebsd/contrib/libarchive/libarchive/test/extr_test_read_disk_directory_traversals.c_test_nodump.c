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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AE_IFDIR ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_READDISK_HONOR_NODUMP ; 
 int ARCHIVE_READDISK_RESTORE_ATIME ; 
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 scalar_t__ archive_read_disk_can_descend (struct archive*) ; 
 int archive_read_disk_descend (struct archive*) ; 
 struct archive* archive_read_disk_new () ; 
 int archive_read_disk_open (struct archive*,char*) ; 
 int archive_read_disk_set_behavior (struct archive*,int) ; 
 int archive_read_free (struct archive*) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertFileAtime (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  assertSetNodump (char*) ; 
 int /*<<< orphan*/  assertUtimes (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canNodump () ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  skipping (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_nodump(void)
{
	struct archive *a;
	struct archive_entry *ae;
	const void *p;
	size_t size;
	int64_t offset;
	int file_count;

	if (!canNodump()) {
		skipping("Can't test nodump on this filesystem");
		return;
	}

	assertMakeDir("nd", 0755);
	assertMakeFile("nd/f1", 0644, "0123456789");
	assertMakeFile("nd/f2", 0644, "hello world");
	assertMakeFile("nd/fe", 0644, NULL);
	assertSetNodump("nd/f2");
	assertUtimes("nd/f1", 886600, 0, 886600, 0);
	assertUtimes("nd/f2", 886611, 0, 886611, 0);
	assertUtimes("nd/fe", 886611, 0, 886611, 0);
	assertUtimes("nd", 886622, 0, 886622, 0);

	assert((ae = archive_entry_new()) != NULL);
	assert((a = archive_read_disk_new()) != NULL);

	/*
	 * Test1: Traversals without ARCHIVE_READDISK_HONOR_NODUMP
	 */
	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "nd"));

	file_count = 4;
	while (file_count--) {
		archive_entry_clear(ae);
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "nd") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "nd/f1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
		} else if (strcmp(archive_entry_pathname(ae), "nd/f2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 11);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 11);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "hello world", 11);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 11);
		} else if (strcmp(archive_entry_pathname(ae), "nd/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_read_disk_can_descend(a)) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There should be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test2: Traversals with ARCHIVE_READDISK_HONOR_NODUMP
	 */
	assertUtimes("nd/f1", 886600, 0, 886600, 0);
	assertUtimes("nd/f2", 886611, 0, 886611, 0);
	assertUtimes("nd/fe", 886611, 0, 886611, 0);
	assertUtimes("nd", 886622, 0, 886622, 0);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_set_behavior(a,
		ARCHIVE_READDISK_RESTORE_ATIME | ARCHIVE_READDISK_HONOR_NODUMP));
	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "nd"));

	file_count = 3;
	while (file_count--) {
		archive_entry_clear(ae);
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		failure("File 'nd/f2' should be exclueded");
		assert(strcmp(archive_entry_pathname(ae), "nd/f2") != 0);
		if (strcmp(archive_entry_pathname(ae), "nd") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "nd/f1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 10);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "0123456789", 10);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 10);
		} else if (strcmp(archive_entry_pathname(ae), "nd/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_read_disk_can_descend(a)) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There should be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	failure("Atime should be restored");
	assertFileAtime("nd/f2", 886611, 0);

	/* Destroy the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	archive_entry_free(ae);
}