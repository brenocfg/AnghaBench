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
 int S_IFREG ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_birthtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_symlink (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_entry(struct archive *a, const char *fname, const char *sym)
{
	struct archive_entry *ae;

	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_birthtime(ae, 2, 20);
	archive_entry_set_atime(ae, 3, 30);
	archive_entry_set_ctime(ae, 4, 40);
	archive_entry_set_mtime(ae, 5, 50);
	archive_entry_copy_pathname(ae, fname);
	if (sym != NULL)
		archive_entry_set_symlink(ae, sym);
	archive_entry_set_mode(ae, S_IFREG | 0555);
	archive_entry_set_size(ae, 0);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
}