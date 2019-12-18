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
struct stat {int st_mode; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 scalar_t__ AE_IFDIR ; 
 int MODE_MASK ; 
 int S_ISGID ; 
 int UMASK ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 struct archive* archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*,char const*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void create(struct archive_entry *ae, const char *msg)
{
	struct archive *ad;
	struct stat st;

	/* Write the entry to disk. */
	assert((ad = archive_write_disk_new()) != NULL);
	failure("%s", msg);
	assertEqualIntA(ad, 0, archive_write_header(ad, ae));
	assertEqualIntA(ad, 0, archive_write_finish_entry(ad));
	assertEqualInt(0, archive_write_free(ad));

	/* Test the entries on disk. */
	assert(0 == stat(archive_entry_pathname(ae), &st));
	failure("%s", msg);

#if !defined(_WIN32) || defined(__CYGWIN__)
	/* When verifying a dir, ignore the S_ISGID bit, as some systems set
	 * that automatically. */
	if (archive_entry_filetype(ae) == AE_IFDIR)
		st.st_mode &= ~S_ISGID;
	assertEqualInt(st.st_mode & MODE_MASK,
	    archive_entry_mode(ae) & ~UMASK & MODE_MASK);
#endif
}