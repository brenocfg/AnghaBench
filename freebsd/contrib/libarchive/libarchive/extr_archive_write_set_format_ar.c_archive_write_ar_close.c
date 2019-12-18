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
struct archive_write {scalar_t__ format_data; } ;
struct ar_w {int wrote_global_header; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int __archive_write_output (struct archive_write*,char*,int) ; 

__attribute__((used)) static int
archive_write_ar_close(struct archive_write *a)
{
	struct ar_w *ar;
	int ret;

	/*
	 * If we haven't written anything yet, we need to write
	 * the ar global header now to make it a valid ar archive.
	 */
	ar = (struct ar_w *)a->format_data;
	if (!ar->wrote_global_header) {
		ar->wrote_global_header = 1;
		ret = __archive_write_output(a, "!<arch>\n", 8);
		return (ret);
	}

	return (ARCHIVE_OK);
}