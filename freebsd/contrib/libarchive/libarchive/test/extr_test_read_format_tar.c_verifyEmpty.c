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
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_NONE ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int /*<<< orphan*/  archiveEmpty ; 
 int /*<<< orphan*/  archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_filter_name (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void verifyEmpty(void)
{
	struct archive_entry *ae;
	struct archive *a;

	assert((a = archive_read_new()) != NULL);
	assertA(0 == archive_read_support_filter_all(a));
	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_open_memory(a, archiveEmpty, 512));
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_NONE);
	assertEqualString(archive_filter_name(a, 0), "none");
	failure("512 zero bytes should be recognized as a tar archive.");
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_TAR);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}