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
struct user_evtchn {int enabled; int /*<<< orphan*/  port; } ;
struct uio {int uio_resid; } ;
struct per_user_data {int /*<<< orphan*/  bind_mutex; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_EVTCHN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PAGE_SIZE ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  evtchn_unmask_port (int /*<<< orphan*/ ) ; 
 struct user_evtchn* find_evtchn (struct per_user_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
evtchn_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	int error, i, count;
	evtchn_port_t *kbuf;
	struct per_user_data *u;

	error = devfs_get_cdevpriv((void **)&u);
	if (error != 0)
		return (EINVAL);

	kbuf = malloc(PAGE_SIZE, M_EVTCHN, M_WAITOK);

	count = uio->uio_resid;
	/* Whole number of ports. */
	count &= ~(sizeof(evtchn_port_t)-1);

	error = 0;
	if (count == 0)
		goto out;

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;

	error = uiomove(kbuf, count, uio);
	if (error != 0)
		goto out;

	mtx_lock(&u->bind_mutex);

	for (i = 0; i < (count/sizeof(evtchn_port_t)); i++) {
		evtchn_port_t port = kbuf[i];
		struct user_evtchn *evtchn;

		evtchn = find_evtchn(u, port);
		if (evtchn && !evtchn->enabled) {
			evtchn->enabled = true;
			evtchn_unmask_port(evtchn->port);
		}
	}

	mtx_unlock(&u->bind_mutex);
	error = 0;

out:
	free(kbuf, M_EVTCHN);
	return (error);
}