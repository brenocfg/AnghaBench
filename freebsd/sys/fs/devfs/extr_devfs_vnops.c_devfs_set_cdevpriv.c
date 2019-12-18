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
struct file {struct cdev_privdata* f_cdevpriv; scalar_t__ f_data; } ;
struct cdev_privdata {struct file* cdpd_fp; int /*<<< orphan*/ * cdpd_dtr; void* cdpd_data; } ;
struct cdev_priv {int /*<<< orphan*/  cdp_fdpriv; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  d_priv_dtor_t ;
struct TYPE_2__ {struct file* td_fpop; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct cdev_privdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CDEVPDATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  cdevpriv_mtx ; 
 int /*<<< orphan*/  cdpd_list ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free (struct cdev_privdata*,int /*<<< orphan*/ ) ; 
 struct cdev_privdata* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
devfs_set_cdevpriv(void *priv, d_priv_dtor_t *priv_dtr)
{
	struct file *fp;
	struct cdev_priv *cdp;
	struct cdev_privdata *p;
	int error;

	fp = curthread->td_fpop;
	if (fp == NULL)
		return (ENOENT);
	cdp = cdev2priv((struct cdev *)fp->f_data);
	p = malloc(sizeof(struct cdev_privdata), M_CDEVPDATA, M_WAITOK);
	p->cdpd_data = priv;
	p->cdpd_dtr = priv_dtr;
	p->cdpd_fp = fp;
	mtx_lock(&cdevpriv_mtx);
	if (fp->f_cdevpriv == NULL) {
		LIST_INSERT_HEAD(&cdp->cdp_fdpriv, p, cdpd_list);
		fp->f_cdevpriv = p;
		mtx_unlock(&cdevpriv_mtx);
		error = 0;
	} else {
		mtx_unlock(&cdevpriv_mtx);
		free(p, M_CDEVPDATA);
		error = EBUSY;
	}
	return (error);
}