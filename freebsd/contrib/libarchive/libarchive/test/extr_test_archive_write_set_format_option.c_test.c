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
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_set_format_iso9660 (struct archive*) ; 
 int /*<<< orphan*/  should (struct archive*,int,char*,char*,char*) ; 

__attribute__((used)) static void
test(int pristine)
{
	struct archive* a = archive_write_new();
	int known_option_rv = pristine ? ARCHIVE_FAILED : ARCHIVE_OK;

	if (!pristine)
		archive_write_set_format_iso9660(a);

	/* NULL and "" denote `no option', so they're ok no matter
	 * what, if any, formats are registered */
	should(a, ARCHIVE_OK, NULL, NULL, NULL);
	should(a, ARCHIVE_OK, "", "", "");

	/* unknown modules and options */
	should(a, ARCHIVE_FAILED, "fubar", "snafu", NULL);
	should(a, ARCHIVE_FAILED, "fubar", "snafu", "betcha");

	/* unknown modules and options */
	should(a, ARCHIVE_FAILED, NULL, "snafu", NULL);
	should(a, ARCHIVE_FAILED, NULL, "snafu", "betcha");

	/* ARCHIVE_OK with iso9660 loaded, ARCHIVE_WARN otherwise */
	should(a, known_option_rv, "iso9660", "joliet", NULL);
	should(a, known_option_rv, "iso9660", "joliet", NULL);
	should(a, known_option_rv, NULL, "joliet", NULL);
	should(a, known_option_rv, NULL, "joliet", NULL);

	archive_write_free(a);
}