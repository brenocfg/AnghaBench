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
typedef  int wchar_t ;
typedef  scalar_t__ time_t ;
struct archive_string {int /*<<< orphan*/  s; } ;
struct archive_match {int /*<<< orphan*/  archive; int /*<<< orphan*/  now; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int EINVAL ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ archive_string_append_from_wcs (struct archive_string*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 scalar_t__ errno ; 
 int error_nomem (struct archive_match*) ; 
 scalar_t__ get_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_timefilter (struct archive_match*,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int const*) ; 

__attribute__((used)) static int
set_timefilter_date_w(struct archive_match *a, int timetype,
    const wchar_t *datestr)
{
	struct archive_string as;
	time_t t;

	if (datestr == NULL || *datestr == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "date is empty");
		return (ARCHIVE_FAILED);
	}

	archive_string_init(&as);
	if (archive_string_append_from_wcs(&as, datestr, wcslen(datestr)) < 0) {
		archive_string_free(&as);
		if (errno == ENOMEM)
			return (error_nomem(a));
		archive_set_error(&(a->archive), -1,
		    "Failed to convert WCS to MBS");
		return (ARCHIVE_FAILED);
	}
	t = get_date(a->now, as.s);
	archive_string_free(&as);
	if (t == (time_t)-1) {
		archive_set_error(&(a->archive), EINVAL, "invalid date string");
		return (ARCHIVE_FAILED);
	}
	return set_timefilter(a, timetype, t, 0, t, 0);
}