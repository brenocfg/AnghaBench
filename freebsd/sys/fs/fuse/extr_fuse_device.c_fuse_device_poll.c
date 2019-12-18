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
struct thread {int dummy; } ;
struct fuse_data {int /*<<< orphan*/  ms_mtx; int /*<<< orphan*/  ks_rsel; int /*<<< orphan*/  ms_head; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int devfs_get_cdevpriv (void**) ; 
 scalar_t__ fdata_get_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

int
fuse_device_poll(struct cdev *dev, int events, struct thread *td)
{
	struct fuse_data *data;
	int error, revents = 0;

	error = devfs_get_cdevpriv((void **)&data);
	if (error != 0)
		return (events &
		    (POLLHUP|POLLIN|POLLRDNORM|POLLOUT|POLLWRNORM));

	if (events & (POLLIN | POLLRDNORM)) {
		fuse_lck_mtx_lock(data->ms_mtx);
		if (fdata_get_dead(data) || STAILQ_FIRST(&data->ms_head))
			revents |= events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &data->ks_rsel);
		fuse_lck_mtx_unlock(data->ms_mtx);
	}
	if (events & (POLLOUT | POLLWRNORM)) {
		revents |= events & (POLLOUT | POLLWRNORM);
	}
	return (revents);
}