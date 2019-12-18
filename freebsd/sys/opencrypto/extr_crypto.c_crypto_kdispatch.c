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
struct cryptkop {int /*<<< orphan*/  krp_crid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs_kops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_Q_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_Q_UNLOCK () ; 
 int ERESTART ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cryptkop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crp_kq ; 
 int /*<<< orphan*/  crp_q ; 
 scalar_t__ crp_sleep ; 
 int crypto_kinvoke (struct cryptkop*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cryptostats ; 
 int /*<<< orphan*/  krp_next ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

int
crypto_kdispatch(struct cryptkop *krp)
{
	int error;

	cryptostats.cs_kops++;

	error = crypto_kinvoke(krp, krp->krp_crid);
	if (error == ERESTART) {
		CRYPTO_Q_LOCK();
		TAILQ_INSERT_TAIL(&crp_kq, krp, krp_next);
		if (crp_sleep)
			wakeup_one(&crp_q);
		CRYPTO_Q_UNLOCK();
		error = 0;
	}
	return error;
}