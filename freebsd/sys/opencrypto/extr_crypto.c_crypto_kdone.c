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
struct cryptocap {scalar_t__ cc_koperations; int cc_flags; } ;
struct crypto_ret_worker {int /*<<< orphan*/  crp_ret_kq; int /*<<< orphan*/  crp_ret_q; } ;
struct cryptkop {scalar_t__ krp_status; size_t krp_hid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs_kerrs; } ;

/* Variables and functions */
 int CRYPTOCAP_F_CLEANUP ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 struct crypto_ret_worker* CRYPTO_RETW (int /*<<< orphan*/ ) ; 
 scalar_t__ CRYPTO_RETW_EMPTY (struct crypto_ret_worker*) ; 
 int /*<<< orphan*/  CRYPTO_RETW_LOCK (struct crypto_ret_worker*) ; 
 int /*<<< orphan*/  CRYPTO_RETW_UNLOCK (struct crypto_ret_worker*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cryptkop*,int /*<<< orphan*/ ) ; 
 struct cryptocap* crypto_drivers ; 
 size_t crypto_drivers_num ; 
 int /*<<< orphan*/  crypto_remove (struct cryptocap*) ; 
 TYPE_1__ cryptostats ; 
 int /*<<< orphan*/  krp_next ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

void
crypto_kdone(struct cryptkop *krp)
{
	struct crypto_ret_worker *ret_worker;
	struct cryptocap *cap;

	if (krp->krp_status != 0)
		cryptostats.cs_kerrs++;
	CRYPTO_DRIVER_LOCK();
	/* XXX: What if driver is loaded in the meantime? */
	if (krp->krp_hid < crypto_drivers_num) {
		cap = &crypto_drivers[krp->krp_hid];
		KASSERT(cap->cc_koperations > 0, ("cc_koperations == 0"));
		cap->cc_koperations--;
		if (cap->cc_flags & CRYPTOCAP_F_CLEANUP)
			crypto_remove(cap);
	}
	CRYPTO_DRIVER_UNLOCK();

	ret_worker = CRYPTO_RETW(0);

	CRYPTO_RETW_LOCK(ret_worker);
	if (CRYPTO_RETW_EMPTY(ret_worker))
		wakeup_one(&ret_worker->crp_ret_q);		/* shared wait channel */
	TAILQ_INSERT_TAIL(&ret_worker->crp_ret_kq, krp, krp_next);
	CRYPTO_RETW_UNLOCK(ret_worker);
}