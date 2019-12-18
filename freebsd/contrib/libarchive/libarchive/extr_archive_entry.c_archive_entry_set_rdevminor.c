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
struct TYPE_2__ {int aest_rdev_is_broken_down; int /*<<< orphan*/  aest_rdevminor; } ;
struct archive_entry {TYPE_1__ ae_stat; scalar_t__ stat_valid; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */

void
archive_entry_set_rdevminor(struct archive_entry *entry, dev_t m)
{
	entry->stat_valid = 0;
	entry->ae_stat.aest_rdev_is_broken_down = 1;
	entry->ae_stat.aest_rdevminor = m;
}