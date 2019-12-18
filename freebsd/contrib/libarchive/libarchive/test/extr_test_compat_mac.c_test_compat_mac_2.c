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
 int ARCHIVE_EOF ; 
 size_t ARCHIVE_FILTER_COMPRESS ; 
 size_t ARCHIVE_FORMAT_TAR_USTAR ; 
 int ARCHIVE_OK ; 
 size_t archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 void* archive_entry_mac_metadata (struct archive_entry*,size_t*) ; 
 size_t archive_entry_mode (struct archive_entry*) ; 
 size_t archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 size_t archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 size_t archive_read_close (struct archive*) ; 
 size_t archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,size_t) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,void const*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char*) ; 

__attribute__((used)) static void
test_compat_mac_2(void)
{
	char name[] = "test_compat_mac-2.tar.Z";
	struct archive_entry *ae;
	struct archive *a;
	const void *attr;
	size_t attrSize;

	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_set_options(a, "mac-ext"));
	extract_reference_file(name);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_filename(a, name, 10240));

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("./", archive_entry_pathname(ae));
	assertEqualInt(1303628303, archive_entry_mtime(ae));
	assertEqualInt(501, archive_entry_uid(ae));
	assertEqualString("tim", archive_entry_uname(ae));
	assertEqualInt(20, archive_entry_gid(ae));
	assertEqualString("staff", archive_entry_gname(ae));
	assertEqualInt(040755, archive_entry_mode(ae));

	attr = archive_entry_mac_metadata(ae, &attrSize);
	assert(attr == NULL);
	assertEqualInt(0, attrSize);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("./mydir/", archive_entry_pathname(ae));
	assertEqualInt(1303628303, archive_entry_mtime(ae));
	assertEqualInt(501, archive_entry_uid(ae));
	assertEqualString("tim", archive_entry_uname(ae));
	assertEqualInt(20, archive_entry_gid(ae));
	assertEqualString("staff", archive_entry_gname(ae));
	assertEqualInt(040755, archive_entry_mode(ae));

	attr = archive_entry_mac_metadata(ae, &attrSize);
	assert(attr != NULL);
	assertEqualInt(267, attrSize);
	assertEqualMem("\x00\x05\x16\x07\x00\x02\x00\x00Mac OS X", attr, 16);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("./myfile", archive_entry_pathname(ae));
	assertEqualInt(1303628303, archive_entry_mtime(ae));
	assertEqualInt(501, archive_entry_uid(ae));
	assertEqualString("tim", archive_entry_uname(ae));
	assertEqualInt(20, archive_entry_gid(ae));
	assertEqualString("staff", archive_entry_gname(ae));
	assertEqualInt(0100644, archive_entry_mode(ae));

	attr = archive_entry_mac_metadata(ae, &attrSize);
	assert(attr != NULL);
	assertEqualInt(267, attrSize);
	assertEqualMem("\x00\x05\x16\x07\x00\x02\x00\x00Mac OS X", attr, 16);

	/* Verify the end-of-archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify that the format detection worked. */
	assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_COMPRESS);
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_TAR_USTAR);

	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}