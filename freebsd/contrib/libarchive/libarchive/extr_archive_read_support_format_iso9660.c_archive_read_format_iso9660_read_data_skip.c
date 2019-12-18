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
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
archive_read_format_iso9660_read_data_skip(struct archive_read *a)
{
	/* Because read_next_header always does an explicit skip
	 * to the next entry, we don't need to do anything here. */
	(void)a; /* UNUSED */
	return (ARCHIVE_OK);
}