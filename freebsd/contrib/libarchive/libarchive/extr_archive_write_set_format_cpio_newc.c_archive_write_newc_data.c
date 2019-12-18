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
struct cpio {size_t entry_bytes_remaining; } ;
struct archive_write {scalar_t__ format_data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int __archive_write_output (struct archive_write*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
archive_write_newc_data(struct archive_write *a, const void *buff, size_t s)
{
	struct cpio *cpio;
	int ret;

	cpio = (struct cpio *)a->format_data;
	if (s > cpio->entry_bytes_remaining)
		s = (size_t)cpio->entry_bytes_remaining;

	ret = __archive_write_output(a, buff, s);
	cpio->entry_bytes_remaining -= s;
	if (ret >= 0)
		return (s);
	else
		return (ret);
}