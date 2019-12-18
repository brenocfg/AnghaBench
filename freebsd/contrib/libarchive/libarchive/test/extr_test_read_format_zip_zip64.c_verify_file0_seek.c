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
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_file0_seek(struct archive *a)
{
	struct archive_entry *ae;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualString("-", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG | 0660, archive_entry_mode(ae));
	assertEqualInt(6, archive_entry_size(ae));
#ifdef HAVE_ZLIB_H
	{
		char data[16];
		assertEqualIntA(a, 6, archive_read_data(a, data, 16));
		assertEqualMem(data, "file0\x0a", 6);
	}
#endif
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_free(a));
}