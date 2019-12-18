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
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int archive_read_support_format_zip_seekable (struct archive*) ; 
 int archive_read_support_format_zip_streamable (struct archive*) ; 

int
archive_read_support_format_zip(struct archive *a)
{
	int r;
	r = archive_read_support_format_zip_streamable(a);
	if (r != ARCHIVE_OK)
		return r;
	return (archive_read_support_format_zip_seekable(a));
}