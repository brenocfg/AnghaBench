#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cra_flags; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int active_devs ; 
 int /*<<< orphan*/  algs_lock ; 
 int crypto_register_akcipher (TYPE_2__*) ; 
 int crypto_register_kpp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dh ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ rsa ; 

int qat_asym_algs_register(void)
{
	int ret = 0;

	mutex_lock(&algs_lock);
	if (++active_devs == 1) {
		rsa.base.cra_flags = 0;
		ret = crypto_register_akcipher(&rsa);
		if (ret)
			goto unlock;
		ret = crypto_register_kpp(&dh);
	}
unlock:
	mutex_unlock(&algs_lock);
	return ret;
}