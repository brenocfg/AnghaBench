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
 scalar_t__ active_devs ; 
 int /*<<< orphan*/  algs_lock ; 
 int /*<<< orphan*/  caam_algapi_exit () ; 
 int /*<<< orphan*/  caam_algapi_hash_exit () ; 
 int /*<<< orphan*/  caam_pkc_exit () ; 
 int /*<<< orphan*/  caam_qi_algapi_exit () ; 
 int /*<<< orphan*/  caam_rng_exit () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unregister_algs(void)
{
	mutex_lock(&algs_lock);

	if (--active_devs != 0)
		goto algs_unlock;

	caam_qi_algapi_exit();

	caam_rng_exit();
	caam_pkc_exit();
	caam_algapi_hash_exit();
	caam_algapi_exit();

algs_unlock:
	mutex_unlock(&algs_lock);
}