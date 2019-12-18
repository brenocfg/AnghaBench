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
 int AE_IFDIR ; 
 int AE_IFLNK ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int archive_entry_atime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_atime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_hardlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 int archive_entry_ctime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 char const* archive_entry_hardlink (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_mtime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_nlink (struct archive_entry*) ; 
 char const* archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 char const* archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_unset_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_xattr_add_entry (struct archive_entry*,char*,char*,int) ; 
 int /*<<< orphan*/  archive_entry_xattr_next (struct archive_entry*,char const**,void const**,size_t*) ; 
 int /*<<< orphan*/  archive_entry_xattr_reset (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_memory (struct archive*,char*,size_t) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 scalar_t__ archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_memory (struct archive*,char*,size_t,size_t*) ; 
 int archive_write_set_format_xar (struct archive*) ; 
 int archive_write_set_options (struct archive*,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  skipping (char*,...) ; 

__attribute__((used)) static void
test_xar(const char *option)
{
	char buff2[64];
	size_t buffsize = 1500;
	char *buff;
	struct archive_entry *ae;
	struct archive *a;
	size_t used;
	const char *name;
	const void *value;
	size_t size;

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	if (archive_write_set_format_xar(a) != ARCHIVE_OK) {
		skipping("xar is not supported on this platform");
		assertEqualIntA(a, ARCHIVE_OK, archive_write_free(a));
		return;
	}
	assertA(0 == archive_write_add_filter_none(a));
	if (option != NULL &&
	    archive_write_set_options(a, option) != ARCHIVE_OK) {
		skipping("option `%s` is not supported on this platform", option);
		assertEqualIntA(a, ARCHIVE_OK, archive_write_free(a));
		return;
	}

	buff = malloc(buffsize);
	assert(buff != NULL);

	assertA(0 == archive_write_open_memory(a, buff, buffsize, &used));

	/*
	 * "file" has a bunch of attributes and 8 bytes of data and
	 * 7 bytes of xattr data and 3 bytes of xattr.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "file");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_nlink(ae, 2);
	archive_entry_set_size(ae, 8);
	archive_entry_xattr_add_entry(ae, "user.data1", "ABCDEFG", 7);
	archive_entry_xattr_add_entry(ae, "user.data2", "XYZ", 3);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 8, archive_write_data(a, "12345678", 9));

	/*
	 * "file2" is symbolic link to file
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "file2");
	archive_entry_copy_symlink(ae, "file");
	archive_entry_set_mode(ae, AE_IFLNK | 0755);
	archive_entry_set_size(ae, 0);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * "dir/file3" has a bunch of attributes and 8 bytes of data.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "dir/file");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 8);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 8, archive_write_data(a, "abcdefgh", 9));

	/*
	 * "dir/dir2/file4" is hard link to file
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "dir/dir2/file4");
	archive_entry_copy_hardlink(ae, "file");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_nlink(ae, 2);
	archive_entry_set_size(ae, 0);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * "dir/dir3" is a directory
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "dir/dir3");
	archive_entry_set_mode(ae, AE_IFDIR | 0755);
	archive_entry_unset_size(ae);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * Add a wrong path "dir/dir2/file4/wrong"
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_atime(ae, 2, 20);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, "dir/dir2/file4/wrong");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_nlink(ae, 1);
	archive_entry_set_size(ae, 0);
	assertEqualIntA(a, ARCHIVE_FAILED, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * XXX TODO XXX Archive directory, other file types.
	 * Archive extended attributes, ACLs, other metadata.
	 * Verify they get read back correctly.
	 */

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_free(a));

	/*
	 *
	 * Now, read the data back.
	 *
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, 0, archive_read_support_format_all(a));
	assertEqualIntA(a, 0, archive_read_support_filter_all(a));
	assertEqualIntA(a, 0, archive_read_open_memory(a, buff, used));

	/*
	 * Read "file"
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assertEqualInt(4, archive_entry_ctime(ae));
	assertEqualInt(0, archive_entry_ctime_nsec(ae));
	assertEqualInt(5, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualString("file", archive_entry_pathname(ae));
	assert((AE_IFREG | 0755) == archive_entry_mode(ae));
	assertEqualInt(2, archive_entry_nlink(ae));
	assertEqualInt(8, archive_entry_size(ae));
	assertEqualInt(2, archive_entry_xattr_reset(ae));
	assertEqualInt(ARCHIVE_OK,
	    archive_entry_xattr_next(ae, &name, &value, &size));
	assertEqualString("user.data2", name);
	assertEqualMem(value, "XYZ", 3);
	assertEqualInt(ARCHIVE_OK,
	    archive_entry_xattr_next(ae, &name, &value, &size));
	assertEqualString("user.data1", name);
	assertEqualMem(value, "ABCDEFG", 7);
	assertEqualIntA(a, 8, archive_read_data(a, buff2, 10));
	assertEqualMem(buff2, "12345678", 8);

	/*
	 * Read "file2"
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assert(archive_entry_atime_is_set(ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assert(archive_entry_ctime_is_set(ae));
	assertEqualInt(4, archive_entry_ctime(ae));
	assertEqualInt(0, archive_entry_ctime_nsec(ae));
	assert(archive_entry_mtime_is_set(ae));
	assertEqualInt(5, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualString("file2", archive_entry_pathname(ae));
	assertEqualString("file", archive_entry_symlink(ae));
	assert((AE_IFLNK | 0755) == archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));

	/*
	 * Read "dir/file3"
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assertEqualInt(4, archive_entry_ctime(ae));
	assertEqualInt(0, archive_entry_ctime_nsec(ae));
	assertEqualInt(5, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualString("dir/file", archive_entry_pathname(ae));
	assert((AE_IFREG | 0755) == archive_entry_mode(ae));
	assertEqualInt(8, archive_entry_size(ae));
	assertEqualIntA(a, 8, archive_read_data(a, buff2, 10));
	assertEqualMem(buff2, "abcdefgh", 8);

	/*
	 * Read "dir/dir2/file4"
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assert(archive_entry_atime_is_set(ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assert(archive_entry_ctime_is_set(ae));
	assertEqualInt(4, archive_entry_ctime(ae));
	assertEqualInt(0, archive_entry_ctime_nsec(ae));
	assert(archive_entry_mtime_is_set(ae));
	assertEqualInt(5, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualString("dir/dir2/file4", archive_entry_pathname(ae));
	assertEqualString("file", archive_entry_hardlink(ae));
	assert((AE_IFREG | 0755) == archive_entry_mode(ae));
	assertEqualInt(2, archive_entry_nlink(ae));
	assertEqualInt(0, archive_entry_size(ae));

	/*
	 * Read "dir/dir3"
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assert(archive_entry_atime_is_set(ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assert(archive_entry_ctime_is_set(ae));
	assertEqualInt(4, archive_entry_ctime(ae));
	assertEqualInt(0, archive_entry_ctime_nsec(ae));
	assert(archive_entry_mtime_is_set(ae));
	assertEqualInt(5, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualString("dir/dir3", archive_entry_pathname(ae));
	assert((AE_IFDIR | 0755) == archive_entry_mode(ae));

	/*
	 * Verify the end of the archive.
	 */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_free(a));

	free(buff);
}