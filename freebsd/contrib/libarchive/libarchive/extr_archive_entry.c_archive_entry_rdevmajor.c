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
struct TYPE_2__ {int /*<<< orphan*/  aest_rdev; int /*<<< orphan*/  aest_rdevmajor; scalar_t__ aest_rdev_is_broken_down; } ;
struct archive_entry {TYPE_1__ ae_stat; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 

dev_t
archive_entry_rdevmajor(struct archive_entry *entry)
{
	if (entry->ae_stat.aest_rdev_is_broken_down)
		return (entry->ae_stat.aest_rdevmajor);
	else
		return major(entry->ae_stat.aest_rdev);
}