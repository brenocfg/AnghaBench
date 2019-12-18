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
struct file {struct cdev_privdata* f_cdevpriv; } ;
struct cdev_privdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdevpriv_mtx ; 
 int /*<<< orphan*/  devfs_destroy_cdevpriv (struct cdev_privdata*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devfs_fpdrop(struct file *fp)
{
	struct cdev_privdata *p;

	mtx_lock(&cdevpriv_mtx);
	if ((p = fp->f_cdevpriv) == NULL) {
		mtx_unlock(&cdevpriv_mtx);
		return;
	}
	devfs_destroy_cdevpriv(p);
}