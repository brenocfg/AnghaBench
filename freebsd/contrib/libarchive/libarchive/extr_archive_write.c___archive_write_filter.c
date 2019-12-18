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
struct archive_write_filter {int (* write ) (struct archive_write_filter*,void const*,size_t) ;size_t bytes_written; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int stub1 (struct archive_write_filter*,void const*,size_t) ; 

int
__archive_write_filter(struct archive_write_filter *f,
    const void *buff, size_t length)
{
	int r;
	if (length == 0)
		return(ARCHIVE_OK);
	if (f->write == NULL)
		/* If unset, a fatal error has already occurred, so this filter
		 * didn't open. We cannot write anything. */
		return(ARCHIVE_FATAL);
	r = (f->write)(f, buff, length);
	f->bytes_written += length;
	return (r);
}