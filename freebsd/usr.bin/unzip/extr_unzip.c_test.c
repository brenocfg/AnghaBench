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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 scalar_t__ archive_read_data (struct archive*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  info (char*,...) ; 

__attribute__((used)) static int
test(struct archive *a, struct archive_entry *e)
{
	ssize_t len;
	int error_count;

	error_count = 0;
	if (S_ISDIR(archive_entry_filetype(e)))
		return 0;

	info("    testing: %s\t", archive_entry_pathname(e));
	while ((len = archive_read_data(a, buffer, sizeof buffer)) > 0)
		/* nothing */;
	if (len < 0) {
		info(" %s\n", archive_error_string(a));
		++error_count;
	} else {
		info(" OK\n");
	}

	/* shouldn't be necessary, but it doesn't hurt */
	ac(archive_read_data_skip(a));

	return error_count;
}