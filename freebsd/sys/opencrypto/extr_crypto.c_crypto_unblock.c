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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cryptocap {scalar_t__ cc_kqblocked; scalar_t__ cc_qblocked; } ;

/* Variables and functions */
 int CRYPTO_ASYMQ ; 
 int /*<<< orphan*/  CRYPTO_Q_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_Q_UNLOCK () ; 
 int CRYPTO_SYMQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  crp_q ; 
 scalar_t__ crp_sleep ; 
 struct cryptocap* crypto_checkdriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

int
crypto_unblock(u_int32_t driverid, int what)
{
	struct cryptocap *cap;
	int err;

	CRYPTO_Q_LOCK();
	cap = crypto_checkdriver(driverid);
	if (cap != NULL) {
		if (what & CRYPTO_SYMQ)
			cap->cc_qblocked = 0;
		if (what & CRYPTO_ASYMQ)
			cap->cc_kqblocked = 0;
		if (crp_sleep)
			wakeup_one(&crp_q);
		err = 0;
	} else
		err = EINVAL;
	CRYPTO_Q_UNLOCK();

	return err;
}