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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 long KB2PAGES (int /*<<< orphan*/ ) ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  cmm_dbg (char*) ; 
 long cmm_free_pages (long) ; 
 int /*<<< orphan*/  loaned_pages ; 
 int /*<<< orphan*/  loaned_pages_target ; 
 int /*<<< orphan*/  oom_freed_pages ; 
 int /*<<< orphan*/  oom_kb ; 

__attribute__((used)) static int cmm_oom_notify(struct notifier_block *self,
			  unsigned long dummy, void *parm)
{
	unsigned long *freed = parm;
	long nr = KB2PAGES(oom_kb);

	cmm_dbg("OOM processing started\n");
	nr = cmm_free_pages(nr);
	loaned_pages_target = loaned_pages;
	*freed += KB2PAGES(oom_kb) - nr;
	oom_freed_pages += KB2PAGES(oom_kb) - nr;
	cmm_dbg("OOM processing complete\n");
	return NOTIFY_OK;
}