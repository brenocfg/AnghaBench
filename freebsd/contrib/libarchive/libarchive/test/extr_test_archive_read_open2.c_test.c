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
typedef  int /*<<< orphan*/  archive_skip_callback ;
typedef  int /*<<< orphan*/  archive_read_callback ;
typedef  int /*<<< orphan*/  archive_open_callback ;
typedef  int /*<<< orphan*/  archive_close_callback ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_open2 (struct archive*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_format_empty (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(int formatted, archive_open_callback *o, archive_read_callback *r,
    archive_skip_callback *s, archive_close_callback *c,
    int rv, const char *msg)
{
	struct archive* a = archive_read_new();
	if (formatted)
	    assertEqualInt(ARCHIVE_OK,
		archive_read_support_format_empty(a));
	assertEqualInt(rv,
	    archive_read_open2(a, NULL, o, r, s, c));
	assertEqualString(msg, archive_error_string(a));
	archive_read_free(a);
}