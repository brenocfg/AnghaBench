#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {TYPE_1__* filter; } ;
struct archive_entry {int dummy; } ;
struct TYPE_2__ {int (* read_header ) (TYPE_1__*,struct archive_entry*) ;} ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int stub1 (TYPE_1__*,struct archive_entry*) ; 

int
__archive_read_header(struct archive_read *a, struct archive_entry *entry)
{
	if (a->filter->read_header)
		return a->filter->read_header(a->filter, entry);
	else
		return (ARCHIVE_OK);
}