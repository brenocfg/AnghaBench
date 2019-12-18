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
struct TYPE_2__ {int /*<<< orphan*/  aest_dev; scalar_t__ aest_dev_is_broken_down; } ;
struct archive_entry {TYPE_1__ ae_stat; int /*<<< orphan*/  ae_set; scalar_t__ stat_valid; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_SET_DEV ; 

void
archive_entry_set_dev(struct archive_entry *entry, dev_t d)
{
	entry->stat_valid = 0;
	entry->ae_set |= AE_SET_DEV;
	entry->ae_stat.aest_dev_is_broken_down = 0;
	entry->ae_stat.aest_dev = d;
}