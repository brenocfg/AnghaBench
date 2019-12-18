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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int AE_IFDIR ; 
 int AE_IFLNK ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_LHA ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_data_block (struct archive*,void const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  file1 ; 
 int file1_size ; 
 int /*<<< orphan*/  file2 ; 
 int file2_size ; 

__attribute__((used)) static void
verify(const char *refname, int posix)
{
	struct archive_entry *ae;
	struct archive *a;
	char buff[128];
	const void *pv;
	size_t s;
	int64_t o;
	int uid, gid;

	if (posix)
		uid = gid = 1001;
	else
		uid = gid = 0;

	extract_reference_file(refname);
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_open_filename(a, refname, 10240));

	/* Verify directory1.  */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	if (posix)
		assertEqualInt((AE_IFDIR | 0750), archive_entry_mode(ae));
	else
		assertEqualInt((AE_IFDIR | 0755), archive_entry_mode(ae));
	assertEqualString("dir/", archive_entry_pathname(ae));
	assertEqualInt(86401, archive_entry_mtime(ae));
	assertEqualInt(uid, archive_entry_uid(ae));
	assertEqualInt(gid, archive_entry_gid(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualIntA(a, ARCHIVE_EOF,
	    archive_read_data_block(a, &pv, &s, &o));
	assertEqualInt(s, 0);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify directory2.  */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt((AE_IFDIR | 0755), archive_entry_mode(ae));
	assertEqualString("dir2/", archive_entry_pathname(ae));
	assertEqualInt(86401, archive_entry_mtime(ae));
	assertEqualInt(uid, archive_entry_uid(ae));
	assertEqualInt(gid, archive_entry_gid(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualIntA(a, ARCHIVE_EOF,
	    archive_read_data_block(a, &pv, &s, &o));
	assertEqualInt(s, 0);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	if (posix) {
		/* Verify symbolic link file1. */
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
		assertEqualInt((AE_IFLNK | 0755), archive_entry_mode(ae));
		assertEqualString("dir2/symlink1", archive_entry_pathname(ae));
		assertEqualString("../file1", archive_entry_symlink(ae));
		assertEqualInt(172802, archive_entry_mtime(ae));
		assertEqualInt(uid, archive_entry_uid(ae));
		assertEqualInt(gid, archive_entry_gid(ae));
		assertEqualInt(0, archive_entry_size(ae));
		assertEqualInt(archive_entry_is_encrypted(ae), 0);
		assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

		/* Verify symbolic link file2. */
		assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
		assertEqualInt((AE_IFLNK | 0755), archive_entry_mode(ae));
		assertEqualString("dir2/symlink2", archive_entry_pathname(ae));
		assertEqualString("../file2", archive_entry_symlink(ae));
		assertEqualInt(172802, archive_entry_mtime(ae));
		assertEqualInt(uid, archive_entry_uid(ae));
		assertEqualInt(gid, archive_entry_gid(ae));
		assertEqualInt(0, archive_entry_size(ae));
		assertEqualInt(archive_entry_is_encrypted(ae), 0);
		assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);
	}

	/* Verify regular file1. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt((AE_IFREG | 0644), archive_entry_mode(ae));
	assertEqualString("file1", archive_entry_pathname(ae));
	assertEqualInt(86401, archive_entry_mtime(ae));
	assertEqualInt(uid, archive_entry_uid(ae));
	assertEqualInt(gid, archive_entry_gid(ae));
	assertEqualInt(file1_size, archive_entry_size(ae));
	assertEqualInt(file1_size, archive_read_data(a, buff, file1_size));
	assertEqualMem(buff, file1, file1_size);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify regular file2. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	if (posix)
		assertEqualInt((AE_IFREG | 0666), archive_entry_mode(ae));
	else
		assertEqualInt((AE_IFREG | 0644), archive_entry_mode(ae));
	assertEqualString("file2", archive_entry_pathname(ae));
	assertEqualInt(86401, archive_entry_mtime(ae));
	assertEqualInt(uid, archive_entry_uid(ae));
	assertEqualInt(gid, archive_entry_gid(ae));
	assertEqualInt(file2_size, archive_entry_size(ae));
	assertEqualInt(file2_size, archive_read_data(a, buff, file2_size));
	assertEqualMem(buff, file2, file2_size);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify the number of files read. */
	if (posix) {
		assertEqualInt(6, archive_file_count(a));
	} else {
		assertEqualInt(4, archive_file_count(a));
	}

	/* End of archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify the number of files read. */
	if (posix) {
		assertEqualInt(6, archive_file_count(a));
	} else {
		assertEqualInt(4, archive_file_count(a));
	}

	/* Verify encryption status */
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify archive format. */
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_LHA, archive_format(a));

	/* Close the archive. */
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}