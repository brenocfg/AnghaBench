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
struct stat {int dummy; } ;
struct archive_match {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ la_stat (char const*,struct stat*) ; 
 int set_timefilter_stat (struct archive_match*,int,struct stat*) ; 

__attribute__((used)) static int
set_timefilter_pathname_mbs(struct archive_match *a, int timetype,
    const char *path)
{
	struct stat st;

	if (path == NULL || *path == '\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}
	if (la_stat(path, &st) != 0) {
		archive_set_error(&(a->archive), errno, "Failed to stat()");
		return (ARCHIVE_FAILED);
	}
	return (set_timefilter_stat(a, timetype, &st));
}