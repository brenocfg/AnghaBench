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
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
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
 int archive_read_free (struct archive*) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertChdir (char*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  failure (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_parent(void)
{
	struct archive *a;
	struct archive_entry *ae;
	const void *p;
	size_t size;
	int64_t offset;
	int file_count;
	int match_count;
	int r;

	assertMakeDir("lock", 0311);
	assertMakeDir("lock/dir1", 0755);
	assertMakeFile("lock/dir1/f1", 0644, "0123456789");
	assertMakeDir("lock/lock2", 0311);
	assertMakeDir("lock/lock2/dir1", 0755);
	assertMakeFile("lock/lock2/dir1/f1", 0644, "0123456789");

	assert((ae = archive_entry_new()) != NULL);
	assert((a = archive_read_disk_new()) != NULL);

	/*
	 * Test1: Traverse lock/dir1 as .
	 */
	assertChdir("lock/dir1");

	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "."));

	file_count = 2;
	match_count = 0;
	while (file_count--) {
		archive_entry_clear(ae);
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), ".") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			++match_count;
		} else if (strcmp(archive_entry_pathname(ae), "./f1") == 0) {
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
			++match_count;
		}
		if (archive_read_disk_can_descend(a)) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	failure("Did not match expected filenames");
	assertEqualInt(match_count, 2);
	/*
	 * There is no entry. This will however fail if the directory traverse
	 * tries to ascend past the initial directory, since it lacks permission
	 * to do so.
	 */
	failure("There should be no entry and no error");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	assertChdir("../..");

	/*
	 * Test2: Traverse lock/dir1 directly
	 */
	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "lock/dir1"));

	file_count = 2;
	match_count = 0;
	while (file_count--) {
		archive_entry_clear(ae);
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "lock/dir1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			++match_count;
		} else if (strcmp(archive_entry_pathname(ae), "lock/dir1/f1") == 0) {
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
			++match_count;
		}
		if (archive_read_disk_can_descend(a)) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	failure("Did not match expected filenames");
	assertEqualInt(match_count, 2);
	/*
	 * There is no entry. This will however fail if the directory traverse
	 * tries to ascend past the initial directory, since it lacks permission
	 * to do so.
	 */
	failure("There should be no entry and no error");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test3: Traverse lock/dir1/.
	 */
	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "lock/dir1/."));

	file_count = 2;
	match_count = 0;
	while (file_count--) {
		archive_entry_clear(ae);
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header2(a, ae));
		if (strcmp(archive_entry_pathname(ae), "lock/dir1/.") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
			++match_count;
		} else if (strcmp(archive_entry_pathname(ae), "lock/dir1/./f1") == 0) {
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
			++match_count;
		}
		if (archive_read_disk_can_descend(a)) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	failure("Did not match expected filenames");
	assertEqualInt(match_count, 2);
	/*
	 * There is no entry. This will however fail if the directory traverse
	 * tries to ascend past the initial directory, since it lacks permission
	 * to do so.
	 */
	failure("There should be no entry and no error");
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header2(a, ae));

	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Test4: Traverse lock/lock2/dir1 from inside lock.
	 *
	 * This test is expected to fail on platforms with no O_EXEC or
	 * equivalent (e.g. O_PATH on Linux or O_SEARCH on SunOS), because
	 * the current traversal code can't handle the case where it can't
	 * obtain an open fd for the initial current directory. We need to
	 * check that condition here, because if O_EXEC _does_ exist, we don't
	 * want to overlook any failure.
	 */
	assertChdir("lock");

	failure("Directory traversals should work as well");
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "lock2/dir1"));

	archive_entry_clear(ae);
	r = archive_read_next_header2(a, ae);
	if (r == ARCHIVE_FAILED) {
#if defined(O_PATH) || defined(O_SEARCH) || defined(O_EXEC)
		assertEqualIntA(a, ARCHIVE_OK, r);
#endif
		/* Close the disk object. */
		archive_read_close(a);
	} else {
		file_count = 2;
		match_count = 0;
		while (file_count--) {
			if (file_count == 0)
				assertEqualIntA(a, ARCHIVE_OK,
				    archive_read_next_header2(a, ae));
			if (strcmp(archive_entry_pathname(ae),
				"lock2/dir1") == 0) {
				assertEqualInt(archive_entry_filetype(ae),
				    AE_IFDIR);
				++match_count;
			} else if (strcmp(archive_entry_pathname(ae),
				"lock2/dir1/f1") == 0) {
				assertEqualInt(archive_entry_filetype(ae),
				    AE_IFREG);
				assertEqualInt(archive_entry_size(ae), 10);
				assertEqualIntA(a, ARCHIVE_OK,
				    archive_read_data_block(a, &p, &size,
					&offset));
				assertEqualInt((int)size, 10);
				assertEqualInt((int)offset, 0);
				assertEqualMem(p, "0123456789", 10);
				assertEqualInt(ARCHIVE_EOF,
				    archive_read_data_block(a, &p, &size,
					&offset));
				assertEqualInt((int)size, 0);
				assertEqualInt((int)offset, 10);
				++match_count;
			}
			if (archive_read_disk_can_descend(a)) {
				/* Descend into the current object */
				assertEqualIntA(a, ARCHIVE_OK,
				    archive_read_disk_descend(a));
			}
		}
		failure("Did not match expected filenames");
		assertEqualInt(match_count, 2);
		/*
		 * There is no entry. This will however fail if the directory
		 * traverse tries to ascend past the initial directory, since
		 * it lacks permission to do so.
		 */
		failure("There should be no entry and no error");
		assertEqualIntA(a, ARCHIVE_EOF,
		    archive_read_next_header2(a, ae));

		/* Close the disk object. */
		assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	}

	assertChdir("..");

	/* Destroy the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	archive_entry_free(ae);
}