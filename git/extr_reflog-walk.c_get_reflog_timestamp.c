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
typedef  int /*<<< orphan*/  timestamp_t ;
struct reflog_walk_info {struct commit_reflog* last_commit_reflog; } ;
struct reflog_info {int /*<<< orphan*/  timestamp; } ;
struct commit_reflog {int recno; TYPE_1__* reflogs; } ;
struct TYPE_2__ {struct reflog_info* items; } ;

/* Variables and functions */

timestamp_t get_reflog_timestamp(struct reflog_walk_info *reflog_info)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;

	if (!commit_reflog)
		return 0;

	info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
	return info->timestamp;
}