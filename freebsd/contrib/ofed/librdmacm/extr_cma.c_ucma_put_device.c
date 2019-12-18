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
struct cma_device {scalar_t__ xrcd; int /*<<< orphan*/  pd; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_close_xrcd (scalar_t__) ; 
 int /*<<< orphan*/  ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucma_put_device(struct cma_device *cma_dev)
{
	pthread_mutex_lock(&mut);
	if (!--cma_dev->refcnt) {
		ibv_dealloc_pd(cma_dev->pd);
		if (cma_dev->xrcd)
			ibv_close_xrcd(cma_dev->xrcd);
	}
	pthread_mutex_unlock(&mut);
}