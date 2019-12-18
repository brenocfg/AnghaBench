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
struct archive_write_disk {int flags; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

int
archive_write_disk_set_options(struct archive *_a, int flags)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;

	a->flags = flags;
	return (ARCHIVE_OK);
}