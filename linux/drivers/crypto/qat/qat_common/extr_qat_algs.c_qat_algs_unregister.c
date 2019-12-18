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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ active_devs ; 
 int /*<<< orphan*/  algs_lock ; 
 int /*<<< orphan*/  crypto_unregister_aeads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_algs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qat_aeads ; 
 int /*<<< orphan*/  qat_algs ; 

void qat_algs_unregister(void)
{
	mutex_lock(&algs_lock);
	if (--active_devs != 0)
		goto unlock;

	crypto_unregister_aeads(qat_aeads, ARRAY_SIZE(qat_aeads));
	crypto_unregister_algs(qat_algs, ARRAY_SIZE(qat_algs));

unlock:
	mutex_unlock(&algs_lock);
}