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
 int /*<<< orphan*/  crypto_unregister_akcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_kpp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dh ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa ; 

void qat_asym_algs_unregister(void)
{
	mutex_lock(&algs_lock);
	if (--active_devs == 0) {
		crypto_unregister_akcipher(&rsa);
		crypto_unregister_kpp(&dh);
	}
	mutex_unlock(&algs_lock);
}