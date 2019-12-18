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
struct devstatlist {int dummy; } ;
struct devstat {int unit_number; int /*<<< orphan*/  sequence1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  STAILQ_REMOVE (struct devstatlist*,struct devstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_acq_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_links ; 
 struct devstatlist device_statq ; 
 int /*<<< orphan*/  devstat ; 
 int /*<<< orphan*/  devstat_free (struct devstat*) ; 
 int /*<<< orphan*/  devstat_generation ; 
 int /*<<< orphan*/  devstat_mutex ; 
 int /*<<< orphan*/  devstat_num_devs ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
devstat_remove_entry(struct devstat *ds)
{
	struct devstatlist *devstat_head;

	mtx_assert(&devstat_mutex, MA_NOTOWNED);
	if (ds == NULL)
		return;

	mtx_lock(&devstat_mutex);

	devstat_head = &device_statq;

	/* Remove this entry from the devstat queue */
	atomic_add_acq_int(&ds->sequence1, 1);
	if (ds->unit_number != -1) {
		devstat_num_devs--;
		STAILQ_REMOVE(devstat_head, ds, devstat, dev_links);
	}
	devstat_free(ds);
	devstat_generation++;
	mtx_unlock(&devstat_mutex);
}