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
struct archive_read_disk {struct archive_entry* entry; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int _archive_read_next_header2 (struct archive*,struct archive_entry*) ; 

__attribute__((used)) static int
_archive_read_next_header(struct archive *_a, struct archive_entry **entryp)
{
	int ret;
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	*entryp = NULL;
	ret = _archive_read_next_header2(_a, a->entry);
	*entryp = a->entry;
	return ret;
}