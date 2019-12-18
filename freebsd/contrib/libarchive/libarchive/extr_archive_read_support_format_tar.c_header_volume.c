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
struct tar {int dummy; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int tar_read_header (struct archive_read*,struct tar*,struct archive_entry*,size_t*) ; 

__attribute__((used)) static int
header_volume(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h, size_t *unconsumed)
{
	(void)h;

	/* Just skip this and read the next header. */
	return (tar_read_header(a, tar, entry, unconsumed));
}