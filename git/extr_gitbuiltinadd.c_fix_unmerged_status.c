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
struct update_callback_data {int flags; } ;
struct diff_filepair {scalar_t__ status; TYPE_1__* two; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ADD_CACHE_IGNORE_REMOVAL ; 
 int DIFF_STATUS_DELETED ; 
 int DIFF_STATUS_MODIFIED ; 
 scalar_t__ DIFF_STATUS_UNMERGED ; 

__attribute__((used)) static int fix_unmerged_status(struct diff_filepair *p,
			       struct update_callback_data *data)
{
	if (p->status != DIFF_STATUS_UNMERGED)
		return p->status;
	if (!(data->flags & ADD_CACHE_IGNORE_REMOVAL) && !p->two->mode)
		/*
		 * This is not an explicit add request, and the
		 * path is missing from the working tree (deleted)
		 */
		return DIFF_STATUS_DELETED;
	else
		/*
		 * Either an explicit add request, or path exists
		 * in the working tree.  An attempt to explicitly
		 * add a path that does not exist in the working tree
		 * will be caught as an error by the caller immediately.
		 */
		return DIFF_STATUS_MODIFIED;
}