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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/ * archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_format_raw (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_empty_file1(void)
{
	struct archive* a = archive_read_new();

	/* Try opening an empty file with the raw handler. */
	assertEqualInt(ARCHIVE_OK, archive_read_support_format_raw(a));
	assertEqualInt(0, archive_errno(a));
	assertEqualString(NULL, archive_error_string(a));

	/* Raw handler doesn't support empty files. */
	assertEqualInt(ARCHIVE_FATAL, archive_read_open_filename(a, "emptyfile", 0));
	assert(NULL != archive_error_string(a));

	archive_read_free(a);
}