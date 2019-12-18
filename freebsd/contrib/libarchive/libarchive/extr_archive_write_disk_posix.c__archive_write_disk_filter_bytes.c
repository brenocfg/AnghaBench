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
struct archive_write_disk {int total_bytes_written; } ;
struct archive {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
_archive_write_disk_filter_bytes(struct archive *_a, int n)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	(void)n; /* UNUSED */
	if (n == -1 || n == 0)
		return (a->total_bytes_written);
	return (-1);
}