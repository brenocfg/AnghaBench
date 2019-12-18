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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {long aest_mtime_nsec; int /*<<< orphan*/  aest_mtime; } ;
struct archive_entry {TYPE_1__ ae_stat; int /*<<< orphan*/  ae_set; scalar_t__ stat_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_SET_MTIME ; 
 int /*<<< orphan*/  FIX_NS (int /*<<< orphan*/ ,long) ; 

void
archive_entry_set_mtime(struct archive_entry *entry, time_t t, long ns)
{
	FIX_NS(t, ns);
	entry->stat_valid = 0;
	entry->ae_set |= AE_SET_MTIME;
	entry->ae_stat.aest_mtime = t;
	entry->ae_stat.aest_mtime_nsec = ns;
}