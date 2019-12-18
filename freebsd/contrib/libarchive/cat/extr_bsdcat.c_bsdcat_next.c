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

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/ * a ; 
 scalar_t__ archive_read_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_read_new () ; 
 int /*<<< orphan*/  archive_read_support_filter_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_format_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_format_raw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsdcat_print_error () ; 

void
bsdcat_next(void)
{
	if (a != NULL) {
		if (archive_read_close(a) != ARCHIVE_OK)
			bsdcat_print_error();
		archive_read_free(a);
	}

	a = archive_read_new();
	archive_read_support_filter_all(a);
	archive_read_support_format_empty(a);
	archive_read_support_format_raw(a);
}