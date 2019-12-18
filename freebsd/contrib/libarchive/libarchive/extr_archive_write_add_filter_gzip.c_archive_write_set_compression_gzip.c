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
 int /*<<< orphan*/  __archive_write_filters_free (struct archive*) ; 
 int archive_write_add_filter_gzip (struct archive*) ; 

int
archive_write_set_compression_gzip(struct archive *a)
{
	__archive_write_filters_free(a);
	return (archive_write_add_filter_gzip(a));
}