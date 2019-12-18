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
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_format_empty (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_raw (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_empty_file2(void)
{
	struct archive* a = archive_read_new();
	struct archive_entry* e;

	/* Try opening an empty file with raw and empty handlers. */
	assertEqualInt(ARCHIVE_OK, archive_read_support_format_raw(a));
	assertEqualInt(ARCHIVE_OK, archive_read_support_format_empty(a));
	assertEqualInt(0, archive_errno(a));
	assertEqualString(NULL, archive_error_string(a));

	assertEqualInt(ARCHIVE_OK, archive_read_open_filename(a, "emptyfile", 0));
	assertEqualInt(0, archive_errno(a));
	assertEqualString(NULL, archive_error_string(a));

	assertEqualInt(ARCHIVE_EOF, archive_read_next_header(a, &e));
	assertEqualInt(0, archive_errno(a));
	assertEqualString(NULL, archive_error_string(a));

	archive_read_free(a);
}