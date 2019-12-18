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
struct proc {int /*<<< orphan*/  p_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  crypto_drivers_mtx ; 
 int /*<<< orphan*/  msleep (struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (void*) ; 

__attribute__((used)) static void
crypto_terminate(struct proc **pp, void *q)
{
	struct proc *p;

	mtx_assert(&crypto_drivers_mtx, MA_OWNED);
	p = *pp;
	*pp = NULL;
	if (p) {
		wakeup_one(q);
		PROC_LOCK(p);		/* NB: insure we don't miss wakeup */
		CRYPTO_DRIVER_UNLOCK();	/* let crypto_finis progress */
		msleep(p, &p->p_mtx, PWAIT, "crypto_destroy", 0);
		PROC_UNLOCK(p);
		CRYPTO_DRIVER_LOCK();
	}
}