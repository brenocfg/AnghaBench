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
 int archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 int archive_read_disk_descend (struct archive*) ; 
 struct archive* archive_read_disk_new () ; 
 int archive_read_disk_open (struct archive*,char*) ; 
 int archive_read_disk_set_atime_restored (struct archive*) ; 
 int archive_read_disk_set_behavior (struct archive*,int) ; 
 int archive_read_free (struct archive*) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertFileAtime (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertFileAtimeRecent (char*) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  assertSetNodump (char*) ; 
 int /*<<< orphan*/  assertUtimes (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atimeIsUpdated () ; 
 int /*<<< orphan*/  canNodump () ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  skipping (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_restore_atime(void)
{
	struct archive *a;
	struct archive_entry *ae;
	const void *p;
	size_t size;
	int64_t offset;
	int file_count;

	if (!atimeIsUpdated()) {
		skipping("Can't test restoring atime on this filesystem");
		return;
	}

	assertMakeDir("at", 0755);
	assertMakeFile("at/f1", 0644, "0123456789");
	assertMakeFile("at/f2", 0644, "hello world");
	assertMakeFile("at/fe", 0644, NULL);
	assertUtimes("at/f1", 886600, 0, 886600, 0);
	assertUtimes("at/f2", 886611, 0, 886611, 0);
	assertUtimes("at/fe", 886611, 0, 886611, 0);
	assertUtimes("at", 886622, 0, 886622, 0);
	file_count = 4;

	assert((ae = archive_entry_new()) != NULL);
	assert((a = archive_read_disk_new()) != NULL);

	/*
	 * Test1: Traversals without archive_read_disk_set_atime_restored().
	 */
	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "at"));
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "at") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "at/f1") == 0) {
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
		} else if (strcmp(archive_entry_pathname(ae), "at/f2") == 0) {
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
		} else if (strcmp(archive_entry_pathname(ae), "at/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There must be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* On FreeBSD (and likely other systems), atime on
	   dirs does not change when it is read. */
	/* failure("Atime should be restored"); */
	/* assertFileAtimeRecent("at"); */
	failure("Atime should be restored");
	assertFileAtimeRecent("at/f1");
	failure("Atime should be restored");
	assertFileAtimeRecent("at/f2");
	failure("The atime of a empty file should not be changed");
	assertFileAtime("at/fe", 886611, 0);

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test2: Traversals with archive_read_disk_set_atime_restored().
	 */
	assertUtimes("at/f1", 886600, 0, 886600, 0);
	assertUtimes("at/f2", 886611, 0, 886611, 0);
	assertUtimes("at/fe", 886611, 0, 886611, 0);
	assertUtimes("at", 886622, 0, 886622, 0);
	file_count = 4;
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_set_atime_restored(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "at"));

	failure("Directory traversals should work as well");
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "at") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "at/f1") == 0) {
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
		} else if (strcmp(archive_entry_pathname(ae), "at/f2") == 0) {
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
		} else if (strcmp(archive_entry_pathname(ae), "at/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There must be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	failure("Atime should be restored");
	assertFileAtime("at", 886622, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f1", 886600, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f2", 886611, 0);
	failure("The atime of a empty file should not be changed");
	assertFileAtime("at/fe", 886611, 0);

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test3: Traversals with archive_read_disk_set_atime_restored() but
	 * no data read as a listing.
	 */
	assertUtimes("at/f1", 886600, 0, 886600, 0);
	assertUtimes("at/f2", 886611, 0, 886611, 0);
	assertUtimes("at/fe", 886611, 0, 886611, 0);
	assertUtimes("at", 886622, 0, 886622, 0);
	file_count = 4;
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_set_atime_restored(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "at"));

	failure("Directory traversals should work as well");
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "at") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "at/f1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 10);
		} else if (strcmp(archive_entry_pathname(ae), "at/f2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 11);
		} else if (strcmp(archive_entry_pathname(ae), "at/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There must be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	failure("Atime should be restored");
	assertFileAtime("at", 886622, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f1", 886600, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f2", 886611, 0);
	failure("The atime of a empty file should not be changed");
	assertFileAtime("at/fe", 886611, 0);

	if (!canNodump()) {
		/* Destroy the disk object. */
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		archive_entry_free(ae);
		skipping("Can't test atime with nodump on this filesystem");
		return;
	}

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test4: Traversals with ARCHIVE_READDISK_RESTORE_ATIME and
	 * ARCHIVE_READDISK_HONOR_NODUMP
	 */
	assertSetNodump("at/f1");
	assertSetNodump("at/f2");
	assertUtimes("at/f1", 886600, 0, 886600, 0);
	assertUtimes("at/f2", 886611, 0, 886611, 0);
	assertUtimes("at/fe", 886611, 0, 886611, 0);
	assertUtimes("at", 886622, 0, 886622, 0);
	file_count = 2;
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_set_behavior(a,
		ARCHIVE_READDISK_RESTORE_ATIME | ARCHIVE_READDISK_HONOR_NODUMP));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "at"));

	failure("Directory traversals should work as well");
	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "at") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "at/fe") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 0);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	failure("There must be no entry");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	failure("Atime should be restored");
	assertFileAtime("at", 886622, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f1", 886600, 0);
	failure("Atime should be restored");
	assertFileAtime("at/f2", 886611, 0);
	failure("The atime of a empty file should not be changed");
	assertFileAtime("at/fe", 886611, 0);

	/* Destroy the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	archive_entry_free(ae);
}