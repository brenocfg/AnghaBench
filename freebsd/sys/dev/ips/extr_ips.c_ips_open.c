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
struct thread {int dummy; } ;
struct cdev {TYPE_1__* si_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ips_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_DEV_OPEN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ips_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	ips_softc_t *sc = dev->si_drv1;
	mtx_lock(&sc->queue_mtx);
	sc->state |= IPS_DEV_OPEN;
	mtx_unlock(&sc->queue_mtx);
        return 0;
}