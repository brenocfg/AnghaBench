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
struct ustar {scalar_t__ entry_padding; scalar_t__ entry_bytes_remaining; } ;
struct archive_write {scalar_t__ format_data; } ;

/* Variables and functions */
 int __archive_write_nulls (struct archive_write*,size_t) ; 

__attribute__((used)) static int
archive_write_ustar_finish_entry(struct archive_write *a)
{
	struct ustar *ustar;
	int ret;

	ustar = (struct ustar *)a->format_data;
	ret = __archive_write_nulls(a,
	    (size_t)(ustar->entry_bytes_remaining + ustar->entry_padding));
	ustar->entry_bytes_remaining = ustar->entry_padding = 0;
	return (ret);
}