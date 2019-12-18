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
struct v7tar {scalar_t__ entry_padding; scalar_t__ entry_bytes_remaining; } ;
struct archive_write {scalar_t__ format_data; } ;

/* Variables and functions */
 int __archive_write_nulls (struct archive_write*,size_t) ; 

__attribute__((used)) static int
archive_write_v7tar_finish_entry(struct archive_write *a)
{
	struct v7tar *v7tar;
	int ret;

	v7tar = (struct v7tar *)a->format_data;
	ret = __archive_write_nulls(a,
	    (size_t)(v7tar->entry_bytes_remaining + v7tar->entry_padding));
	v7tar->entry_bytes_remaining = v7tar->entry_padding = 0;
	return (ret);
}