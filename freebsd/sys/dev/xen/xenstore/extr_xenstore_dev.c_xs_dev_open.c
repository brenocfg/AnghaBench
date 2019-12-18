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
struct xs_dev_data {int /*<<< orphan*/  watches; int /*<<< orphan*/  transactions; int /*<<< orphan*/  lock; } ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int M_ZERO ; 
 int devfs_set_cdevpriv (struct xs_dev_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xs_dev_data*,int /*<<< orphan*/ ) ; 
 struct xs_dev_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_dev_dtor ; 

__attribute__((used)) static int
xs_dev_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct xs_dev_data *u;
	int error;

	u = malloc(sizeof(*u), M_XENSTORE, M_WAITOK|M_ZERO);
	mtx_init(&u->lock, "xsdev_lock", NULL, MTX_DEF);
	LIST_INIT(&u->transactions);
	LIST_INIT(&u->watches);
	error = devfs_set_cdevpriv(u, xs_dev_dtor);
	if (error != 0)
		free(u, M_XENSTORE);

	return (error);
}