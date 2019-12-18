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
struct stat {int st_mode; int st_size; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int UMASK ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int archive_write_data (struct archive*,char const*,int) ; 
 struct archive* archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*,...) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void create_reg_file3(struct archive_entry *ae, const char *msg)
{
	static const char data[]="abcdefghijklmnopqrstuvwxyz";
	struct archive *ad;
	struct stat st;

	/* Write the entry to disk. */
	assert((ad = archive_write_disk_new()) != NULL);
	failure("%s", msg);
	/* Set the size smaller than the data and verify the truncation. */
	archive_entry_set_size(ae, 5);
	assertEqualIntA(ad, 0, archive_write_header(ad, ae));
	assertEqualInt(5, archive_write_data(ad, data, sizeof(data)));
	assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
	assertEqualInt(0, archive_write_free(ad));

	/* Test the entry on disk. */
	assert(0 == stat(archive_entry_pathname(ae), &st));
	failure("st.st_mode=%o archive_entry_mode(ae)=%o",
	    st.st_mode, archive_entry_mode(ae));
#if !defined(_WIN32) || defined(__CYGWIN__)
	assertEqualInt(st.st_mode, (archive_entry_mode(ae) & ~UMASK));
#endif
	assertEqualInt(st.st_size, 5);
}