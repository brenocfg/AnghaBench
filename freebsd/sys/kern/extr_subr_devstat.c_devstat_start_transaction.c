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
struct bintime {int dummy; } ;
struct devstat {scalar_t__ start_count; scalar_t__ end_count; int /*<<< orphan*/  sequence0; struct bintime busy_from; int /*<<< orphan*/  sequence1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_DEVSTAT_START () ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  atomic_add_acq_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_add_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 
 int /*<<< orphan*/  devstat_mutex ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devstat_start_transaction(struct devstat *ds, const struct bintime *now)
{

	mtx_assert(&devstat_mutex, MA_NOTOWNED);

	/* sanity check */
	if (ds == NULL)
		return;

	atomic_add_acq_int(&ds->sequence1, 1);
	/*
	 * We only want to set the start time when we are going from idle
	 * to busy.  The start time is really the start of the latest busy
	 * period.
	 */
	if (ds->start_count == ds->end_count) {
		if (now != NULL)
			ds->busy_from = *now;
		else
			binuptime(&ds->busy_from);
	}
	ds->start_count++;
	atomic_add_rel_int(&ds->sequence0, 1);
	DTRACE_DEVSTAT_START();
}