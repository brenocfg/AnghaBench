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
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_write_add_filter_gzip (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_set_format_iso9660 (struct archive*) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  should (struct archive*,int,char*) ; 

__attribute__((used)) static void
test(int pristine)
{
	struct archive* a = archive_write_new();
	int halfempty_options_rv = pristine ? ARCHIVE_FAILED : ARCHIVE_OK;
	int known_option_rv = pristine ? ARCHIVE_FAILED : ARCHIVE_OK;

	if (!pristine) {
		archive_write_add_filter_gzip(a);
		archive_write_set_format_iso9660(a);
	}

	/* NULL and "" denote `no option', so they're ok no matter
	 * what, if any, formats are registered */
	should(a, ARCHIVE_OK, NULL);
	should(a, ARCHIVE_OK, "");

	/* unknown modules and options */
	should(a, ARCHIVE_FAILED, "fubar:snafu");
	assertEqualString("Unknown module name: `fubar'",
	    archive_error_string(a));
	should(a, ARCHIVE_FAILED, "fubar:snafu=betcha");
	assertEqualString("Unknown module name: `fubar'",
	    archive_error_string(a));

	/* unknown modules and options */
	should(a, ARCHIVE_FAILED, "snafu");
	assertEqualString("Undefined option: `snafu'",
	    archive_error_string(a));
	should(a, ARCHIVE_FAILED, "snafu=betcha");
	assertEqualString("Undefined option: `snafu'",
	    archive_error_string(a));

	/* ARCHIVE_OK with iso9660 loaded, ARCHIVE_FAILED otherwise */
	should(a, known_option_rv, "iso9660:joliet");
	if (pristine) {
		assertEqualString("Unknown module name: `iso9660'",
		    archive_error_string(a));
	}
	should(a, known_option_rv, "iso9660:joliet");
	if (pristine) {
		assertEqualString("Unknown module name: `iso9660'",
		    archive_error_string(a));
	}
	should(a, known_option_rv, "joliet");
	if (pristine) {
		assertEqualString("Undefined option: `joliet'",
		    archive_error_string(a));
	}
	should(a, known_option_rv, "!joliet");
	if (pristine) {
		assertEqualString("Undefined option: `joliet'",
		    archive_error_string(a));
	}

	should(a, ARCHIVE_OK, ",");
	should(a, ARCHIVE_OK, ",,");

	should(a, halfempty_options_rv, ",joliet");
	if (pristine) {
		assertEqualString("Undefined option: `joliet'",
		    archive_error_string(a));
	}
	should(a, halfempty_options_rv, "joliet,");
	if (pristine) {
		assertEqualString("Undefined option: `joliet'",
		    archive_error_string(a));
	}

	should(a, ARCHIVE_FAILED, "joliet,snafu");
	if (pristine) {
		assertEqualString("Undefined option: `joliet'",
		    archive_error_string(a));
	} else {
		assertEqualString("Undefined option: `snafu'",
		    archive_error_string(a));
	}

	should(a, ARCHIVE_FAILED, "iso9660:snafu");
	if (pristine) {
		assertEqualString("Unknown module name: `iso9660'",
		    archive_error_string(a));
	} else {
		assertEqualString("Undefined option: `iso9660:snafu'",
		    archive_error_string(a));
	}

	archive_write_free(a);
}