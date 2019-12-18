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
struct archive_write_filter {int (* close ) (struct archive_write_filter*) ;struct archive_write_filter* next_filter; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int stub1 (struct archive_write_filter*) ; 

int
__archive_write_close_filter(struct archive_write_filter *f)
{
	if (f->close != NULL)
		return (f->close)(f);
	if (f->next_filter != NULL)
		return (__archive_write_close_filter(f->next_filter));
	return (ARCHIVE_OK);
}