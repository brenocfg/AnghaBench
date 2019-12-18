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
struct archive_write_filter {int (* open ) (struct archive_write_filter*) ;} ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int stub1 (struct archive_write_filter*) ; 

int
__archive_write_open_filter(struct archive_write_filter *f)
{
	if (f->open == NULL)
		return (ARCHIVE_OK);
	return (f->open)(f);
}