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
struct TYPE_2__ {int /*<<< orphan*/  conflicts; int /*<<< orphan*/  ignores; int /*<<< orphan*/  wt_mods; int /*<<< orphan*/  wt_dels; int /*<<< orphan*/  wt_adds; int /*<<< orphan*/  index_mods; int /*<<< orphan*/  index_dels; int /*<<< orphan*/  index_adds; } ;
typedef  TYPE_1__ index_status_counts ;

/* Variables and functions */
 unsigned int GIT_STATUS_CONFLICTED ; 
 unsigned int GIT_STATUS_IGNORED ; 
 unsigned int GIT_STATUS_INDEX_DELETED ; 
 unsigned int GIT_STATUS_INDEX_MODIFIED ; 
 unsigned int GIT_STATUS_INDEX_NEW ; 
 unsigned int GIT_STATUS_INDEX_TYPECHANGE ; 
 unsigned int GIT_STATUS_WT_DELETED ; 
 unsigned int GIT_STATUS_WT_MODIFIED ; 
 unsigned int GIT_STATUS_WT_NEW ; 
 unsigned int GIT_STATUS_WT_TYPECHANGE ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int index_status_cb(
	const char *path, unsigned int status_flags, void *payload)
{
	index_status_counts *vals = payload;

	/* cb_status__print(path, status_flags, NULL); */

	GIT_UNUSED(path);

	if (status_flags & GIT_STATUS_INDEX_NEW)
		vals->index_adds++;
	if (status_flags & GIT_STATUS_INDEX_MODIFIED)
		vals->index_mods++;
	if (status_flags & GIT_STATUS_INDEX_DELETED)
		vals->index_dels++;
	if (status_flags & GIT_STATUS_INDEX_TYPECHANGE)
		vals->index_mods++;

	if (status_flags & GIT_STATUS_WT_NEW)
		vals->wt_adds++;
	if (status_flags & GIT_STATUS_WT_MODIFIED)
		vals->wt_mods++;
	if (status_flags & GIT_STATUS_WT_DELETED)
		vals->wt_dels++;
	if (status_flags & GIT_STATUS_WT_TYPECHANGE)
		vals->wt_mods++;

	if (status_flags & GIT_STATUS_IGNORED)
		vals->ignores++;
	if (status_flags & GIT_STATUS_CONFLICTED)
		vals->conflicts++;

	return 0;
}