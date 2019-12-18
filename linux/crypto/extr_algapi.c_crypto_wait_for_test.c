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
struct TYPE_2__ {int /*<<< orphan*/  cra_driver_name; } ;
struct crypto_larval {TYPE_1__ alg; int /*<<< orphan*/  completion; struct crypto_larval* adult; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MSG_ALG_LOADED ; 
 int /*<<< orphan*/  CRYPTO_MSG_ALG_REGISTER ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  crypto_alg_tested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_larval_kill (TYPE_1__*) ; 
 int crypto_probing_notify (int /*<<< orphan*/ ,struct crypto_larval*) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_wait_for_test(struct crypto_larval *larval)
{
	int err;

	err = crypto_probing_notify(CRYPTO_MSG_ALG_REGISTER, larval->adult);
	if (err != NOTIFY_STOP) {
		if (WARN_ON(err != NOTIFY_DONE))
			goto out;
		crypto_alg_tested(larval->alg.cra_driver_name, 0);
	}

	err = wait_for_completion_killable(&larval->completion);
	WARN_ON(err);
	if (!err)
		crypto_probing_notify(CRYPTO_MSG_ALG_LOADED, larval);

out:
	crypto_larval_kill(&larval->alg);
}