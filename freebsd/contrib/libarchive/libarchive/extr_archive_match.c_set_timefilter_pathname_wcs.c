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
struct archive_string {int /*<<< orphan*/  s; } ;
struct archive_match {int /*<<< orphan*/  archive; } ;

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
 int set_timefilter_pathname_mbs (struct archive_match*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int const*) ; 

__attribute__((used)) static int
set_timefilter_pathname_wcs(struct archive_match *a, int timetype,
    const wchar_t *path)
{
	struct archive_string as;
	int r;

	if (path == NULL || *path == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}

	/* Convert WCS filename to MBS filename. */
	archive_string_init(&as);
	if (archive_string_append_from_wcs(&as, path, wcslen(path)) < 0) {
		archive_string_free(&as);
		if (errno == ENOMEM)
			return (error_nomem(a));
		archive_set_error(&(a->archive), -1,
		    "Failed to convert WCS to MBS");
		return (ARCHIVE_FAILED);
	}

	r = set_timefilter_pathname_mbs(a, timetype, as.s);
	archive_string_free(&as);

	return (r);
}