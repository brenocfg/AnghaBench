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
 int /*<<< orphan*/  EXTENT ; 
 struct archive_string* archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertExactString (int,int /*<<< orphan*/ ,char*,struct archive_string) ; 

__attribute__((used)) static void
test_archive_strcat(void)
{
	struct archive_string s;

	archive_string_init(&s);
	assertExactString(0, 0, NULL, s);

	/* null target, empty source */
	assert(&s == archive_strcat(&s, ""));
	assertExactString(0, EXTENT, "", s);

	/* empty target, empty source */
	assert(&s == archive_strcat(&s, ""));
	assertExactString(0, EXTENT, "", s);

	/* empty target, non-empty source */
	assert(&s == archive_strcat(&s, "fubar"));
	assertExactString(5, EXTENT, "fubar", s);

	/* non-empty target, non-empty source */
	assert(&s == archive_strcat(&s, "baz"));
	assertExactString(8, EXTENT, "fubarbaz", s);

	archive_string_free(&s);
}