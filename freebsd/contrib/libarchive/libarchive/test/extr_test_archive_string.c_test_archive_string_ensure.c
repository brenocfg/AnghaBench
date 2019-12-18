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
struct archive_string {int dummy; } ;

/* Variables and functions */
 int EXTENT ; 
 struct archive_string* archive_string_ensure (struct archive_string*,int) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertExactString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct archive_string) ; 
 int /*<<< orphan*/  assertNonNULLString (int /*<<< orphan*/ ,int,struct archive_string) ; 

__attribute__((used)) static void
test_archive_string_ensure(void)
{
	struct archive_string s;

	archive_string_init(&s);
	assertExactString(0, 0, NULL, s);

	/* single-extent allocation */
	assert(&s == archive_string_ensure(&s, 5));
	assertNonNULLString(0, EXTENT, s);

	/* what happens around extent boundaries? */
	assert(&s == archive_string_ensure(&s, EXTENT - 1));
	assertNonNULLString(0, EXTENT, s);

	assert(&s == archive_string_ensure(&s, EXTENT));
	assertNonNULLString(0, EXTENT, s);

	assert(&s == archive_string_ensure(&s, EXTENT + 1));
	assertNonNULLString(0, 2 * EXTENT, s);

	archive_string_free(&s);
}