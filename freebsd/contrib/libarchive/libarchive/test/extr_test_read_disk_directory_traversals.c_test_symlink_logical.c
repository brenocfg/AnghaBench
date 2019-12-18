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
 int AE_IFLNK ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,scalar_t__*) ; 
 int archive_read_disk_descend (struct archive*) ; 
 struct archive* archive_read_disk_new () ; 
 int archive_read_disk_open (struct archive*,char*) ; 
 int archive_read_disk_set_symlink_logical (struct archive*) ; 
 int archive_read_free (struct archive*) ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertChdir (char*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (void const*,char*,int) ; 
 int /*<<< orphan*/  assertMakeDir (char*,int) ; 
 int /*<<< orphan*/  assertMakeFile (char*,int,char*) ; 
 int /*<<< orphan*/  assertMakeSymlink (char*,char*,int) ; 
 int /*<<< orphan*/  canSymlink () ; 
 int /*<<< orphan*/  skipping (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_symlink_logical(void)
{
	struct archive *a;
	struct archive_entry *ae;
	const void *p;
	size_t size;
	int64_t offset;
	int file_count;

	if (!canSymlink()) {
		skipping("Can't test symlinks on this filesystem");
		return;
	}

	/*
	 * Create a sample archive.
	 */
	assertMakeDir("l", 0755);
	assertChdir("l");
	assertMakeDir("d1", 0755);
	assertMakeSymlink("ld1", "d1", 1);
	assertMakeFile("d1/file1", 0644, "d1/file1");
	assertMakeFile("d1/file2", 0644, "d1/file2");
	assertMakeSymlink("d1/link1", "file1", 0);
	assertMakeSymlink("d1/linkX", "fileX", 0);
	assertMakeSymlink("link2", "d1/file2", 0);
	assertMakeSymlink("linkY", "d1/fileY", 0);
	assertChdir("..");

	/* Note: this test uses archive_read_next_header()
	   instead of archive_read_next_header2() */
	assert((a = archive_read_disk_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_disk_set_symlink_logical(a));

	/*
	 * Specified file is a symbolic link file.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "l/ld1"));
	file_count = 5;

	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
		if (strcmp(archive_entry_pathname(ae), "l/ld1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file2", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/link1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/linkX") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFLNK);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));

	/*
	 * Specified file is a directory and it has symbolic files.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_disk_open(a, "l"));
	file_count = 13;

	while (file_count--) {
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
		if (strcmp(archive_entry_pathname(ae), "l") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae), "l/d1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/d1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/d1/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file2", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/d1/link1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/d1/linkX") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFLNK);
		} else if (strcmp(archive_entry_pathname(ae), "l/ld1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFDIR);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/file1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/file2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file2", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/link1") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file1", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/ld1/linkX") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFLNK);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/link2") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFREG);
			assertEqualInt(archive_entry_size(ae), 8);
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 8);
			assertEqualInt((int)offset, 0);
			assertEqualMem(p, "d1/file2", 8);
			assertEqualInt(ARCHIVE_EOF,
			    archive_read_data_block(a, &p, &size, &offset));
			assertEqualInt((int)size, 0);
			assertEqualInt((int)offset, 8);
		} else if (strcmp(archive_entry_pathname(ae),
		    "l/linkY") == 0) {
			assertEqualInt(archive_entry_filetype(ae), AE_IFLNK);
		}
		if (archive_entry_filetype(ae) == AE_IFDIR) {
			/* Descend into the current object */
			assertEqualIntA(a, ARCHIVE_OK,
			    archive_read_disk_descend(a));
		}
	}
	/* There is no entry. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	/* Close the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	/* Destroy the disk object. */
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}