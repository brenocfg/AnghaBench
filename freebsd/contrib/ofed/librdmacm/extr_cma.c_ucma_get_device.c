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
struct TYPE_2__ {scalar_t__ pd; int /*<<< orphan*/  verbs; } ;
struct cma_id_private {TYPE_1__ id; struct cma_device* cma_dev; } ;
struct cma_device {scalar_t__ guid; scalar_t__ pd; int /*<<< orphan*/  verbs; int /*<<< orphan*/  refcnt; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 struct cma_device* cma_dev_array ; 
 int cma_dev_cnt ; 
 scalar_t__ ibv_alloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int ucma_init_device (struct cma_device*) ; 

__attribute__((used)) static int ucma_get_device(struct cma_id_private *id_priv, __be64 guid)
{
	struct cma_device *cma_dev;
	int i, ret;

	for (i = 0; i < cma_dev_cnt; i++) {
		cma_dev = &cma_dev_array[i];
		if (cma_dev->guid == guid)
			goto match;
	}

	return ERR(ENODEV);
match:
	pthread_mutex_lock(&mut);
	if ((ret = ucma_init_device(cma_dev)))
		goto out;

	if (!cma_dev->refcnt++) {
		cma_dev->pd = ibv_alloc_pd(cma_dev->verbs);
		if (!cma_dev->pd) {
			cma_dev->refcnt--;
			ret = ERR(ENOMEM);
			goto out;
		}
	}
	id_priv->cma_dev = cma_dev;
	id_priv->id.verbs = cma_dev->verbs;
	id_priv->id.pd = cma_dev->pd;
out:
	pthread_mutex_unlock(&mut);
	return ret;
}