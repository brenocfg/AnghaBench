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
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_write_add_filter_gzip (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  should (struct archive*,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void
test(int pristine)
{
	struct archive* a = archive_write_new();

	if (!pristine)
		archive_write_add_filter_gzip(a);

	should(a, ARCHIVE_OK, NULL, NULL, NULL);
	should(a, ARCHIVE_OK, "", "", "");

	should(a, ARCHIVE_FAILED, NULL, "fubar", NULL);
	should(a, ARCHIVE_FAILED, NULL, "fubar", "snafu");
	should(a, ARCHIVE_FAILED, "fubar", "snafu", NULL);
	should(a, ARCHIVE_FAILED, "fubar", "snafu", "betcha");

	archive_write_free(a);
}