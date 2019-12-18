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
 struct archive_string* archive_strcpy (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_concat (struct archive_string*,struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertExactString (int,int /*<<< orphan*/ ,char*,struct archive_string) ; 

__attribute__((used)) static void
test_archive_string_concat(void)
{
	struct archive_string s, t, u, v;

	archive_string_init(&s);
	assertExactString(0, 0, NULL, s);
	archive_string_init(&t);
	assertExactString(0, 0, NULL, t);
	archive_string_init(&u);
	assertExactString(0, 0, NULL, u);
	archive_string_init(&v);
	assertExactString(0, 0, NULL, v);

	/* null target, null source */
	archive_string_concat(&t, &s);
	assertExactString(0, 0, NULL, s);
	assertExactString(0, EXTENT, "", t);

	/* null target, empty source */
	assert(&s == archive_strcpy(&s, ""));
	archive_string_concat(&u, &s);
	assertExactString(0, EXTENT, "", s);
	assertExactString(0, EXTENT, "", u);

	/* null target, non-empty source */
	assert(&s == archive_strcpy(&s, "foo"));
	archive_string_concat(&v, &s);
	assertExactString(3, EXTENT, "foo", s);
	assertExactString(3, EXTENT, "foo", v);

	/* empty target, empty source */
	assert(&s == archive_strcpy(&s, ""));
	assert(&t == archive_strcpy(&t, ""));
	archive_string_concat(&t, &s);
	assertExactString(0, EXTENT, "", s);
	assertExactString(0, EXTENT, "", t);

	/* empty target, non-empty source */
	assert(&s == archive_strcpy(&s, "snafu"));
	assert(&t == archive_strcpy(&t, ""));
	archive_string_concat(&t, &s);
	assertExactString(5, EXTENT, "snafu", s);
	assertExactString(5, EXTENT, "snafu", t);

	archive_string_free(&v);
	archive_string_free(&u);
	archive_string_free(&t);
	archive_string_free(&s);
}