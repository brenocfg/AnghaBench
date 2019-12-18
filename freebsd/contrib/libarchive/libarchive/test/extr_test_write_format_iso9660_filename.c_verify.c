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
struct fns {int alloc; scalar_t__ maxlen; scalar_t__ longest_len; int /*<<< orphan*/ * names; scalar_t__ cnt; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
#define  ISO9660 130 
#define  JOLIET 129 
#define  ROCKRIDGE 128 
 int S_IFDIR ; 
 int archive_entry_atime (struct archive_entry*) ; 
 int archive_entry_ctime (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_memory (struct archive*,unsigned char*,size_t) ; 
 scalar_t__ archive_read_set_option (struct archive*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify_file (struct archive*,int,struct fns*) ; 

__attribute__((used)) static void
verify(unsigned char *buff, size_t used, enum vtype type, struct fns *fns)
{
	struct archive *a;
	struct archive_entry *ae;
	size_t i;

	/*
	 * Read ISO image.
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, 0, archive_read_support_format_all(a));
	assertEqualIntA(a, 0, archive_read_support_filter_all(a));
	if (type >= 1)
		assertA(0 == archive_read_set_option(a, NULL, "rockridge",
		    NULL));
	if (type >= 2)
		assertA(0 == archive_read_set_option(a, NULL, "joliet",
		    NULL));
	assertEqualIntA(a, 0, archive_read_open_memory(a, buff, used));

	/*
	 * Read Root Directory
	 * Root Directory entry must be in ISO image.
	 */
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assertEqualInt(archive_entry_atime(ae), archive_entry_ctime(ae));
	assertEqualInt(archive_entry_atime(ae), archive_entry_mtime(ae));
	assertEqualString(".", archive_entry_pathname(ae));
	switch (type) {
	case ROCKRIDGE:
		assert((S_IFDIR | 0555) == archive_entry_mode(ae));
		break;
	case JOLIET:
		assert((S_IFDIR | 0700) == archive_entry_mode(ae));
		break;
	case ISO9660:
		assert((S_IFDIR | 0700) == archive_entry_mode(ae));
		break;
	}

	/*
	 * Verify file status.
	 */
	memset(fns->names, 0, sizeof(char *) * fns->alloc);
	fns->cnt = 0;
	for (i = 0; i < fns->alloc; i++)
		verify_file(a, type, fns);
	for (i = 0; i < fns->alloc; i++)
		free(fns->names[i]);
	assertEqualInt((int)fns->longest_len, (int)fns->maxlen);

	/*
	 * Verify the end of the archive.
	 */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_free(a));
}