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
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 struct archive_string* archive_strncat (struct archive_string*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertExactString (int,int /*<<< orphan*/ ,char*,struct archive_string) ; 

__attribute__((used)) static void
test_archive_strncat(void)
{
	struct archive_string s;

	archive_string_init(&s);
	assertExactString(0, 0, NULL, s);

	/* perfect length */
	assert(&s == archive_strncat(&s, "snafu", 5));
	assertExactString(5, EXTENT, "snafu", s);

	/* short read */
	assert(&s == archive_strncat(&s, "barbazqux", 3));
	assertExactString(8, EXTENT, "snafubar", s);

	/* long read is ok too! */
	assert(&s == archive_strncat(&s, "snafu", 8));
	assertExactString(13, EXTENT, "snafubarsnafu", s);

	archive_string_free(&s);
}