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
struct TYPE_2__ {long aest_ctime_nsec; } ;
struct archive_entry {TYPE_1__ ae_stat; } ;

/* Variables and functions */

long
archive_entry_ctime_nsec(struct archive_entry *entry)
{
	return (entry->ae_stat.aest_ctime_nsec);
}